/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_numero_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/22 16:06:17 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/22 17:06:53 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

typedef struct	s_vec2d
{
	double	x;
	double	y;
}				t_vec2d;

t_vec2d		vec2d_add(t_vec2d a, t_vec2d b)
{
	return ((t_vec2d){a.x + b.x, a.y + b.y});
}

t_vec2d		vec2d_divide(t_vec2d vec, double constant)
{
	return ((t_vec2d){vec.x / constant, vec.y / constant});
}

t_vec2d		vec2d_scalar(t_vec2d vec, double constant)
{
	return ((t_vec2d){vec.x * constant, vec.y * constant});
}

t_vec2d		vec2d_divide(t_vec2d vec, double constant)
{
	return ((t_vec2d){vec.x / constant, vec.y / constant});
}

#define inchToMm 25.4f
enum FitResolutionGate { kFill = 0, kOverscan };


void computeScreenCoordinates(
		double filmApertureWidth,
		double filmApertureHeight,
		int imageWidth,
		int imageHeight,
		const FitResolutionGate &fitFilm,
		double nearClippingPLane,
		double focalLength,
		double *top, double *bottom, double *left, double *right
		)
{
	double filmAspectRatio = filmApertureWidth / filmApertureHeight;
	double deviceAspectRatio = imageWidth / (double)imageHeight;

	*top = ((filmApertureHeight * inchToMm / 2) / focalLength) * nearClippingPLane;
	*right = ((filmApertureWidth * inchToMm / 2) / focalLength) * nearClippingPLane;

	// field of view (horizontal)
	double fov = 2 * 180 / M_PI * atan((filmApertureWidth * inchToMm / 2) / focalLength);

	double xscale = 1;
	double yscale = 1;

	switch (fitFilm) {
	    default:
	    case kFill:
	        if (filmAspectRatio > deviceAspectRatio) {
	            xscale = deviceAspectRatio / filmAspectRatio;
	        }
	        else {
	            yscale = filmAspectRatio / deviceAspectRatio;
	        }
	        break;
	    case kOverscan:
	        if (filmAspectRatio > deviceAspectRatio) {
	            yscale = filmAspectRatio / deviceAspectRatio;
	        }
	        else {
	            xscale = deviceAspectRatio / filmAspectRatio;
	        }
	        break;
	}

	*right *= xscale;
	*top *= yscale;

	*bottom = -*top;
	*left = -*right;
}

void convertToRaster(
		t_vec3d vertexWorld,
		double worldToCamera[4][4],
		double left,
		double right,
		double top,
		double bottom,
		double near,
		int imageWidth,
		int imageHeight,
		t_vec3d *vertexRaster
		)
{
	t_vec3d vertexCamera;

	matrix44_vec3d_mul(worldToCamera, vertexWorld, &vertexCamera);

	// convert to screen space
	t_vec3d vertexScreen;
	vertexScreen.x = near * vertexCamera.x / -vertexCamera.z;
	vertexScreen.y = near * vertexCamera.y / -vertexCamera.z;

	// now convert point from screen space to NDC space (in range [-1,1])
	t_vec3d vertexNDC;
	vertexNDC.x = 2 * vertexScreen.x / (right - left) - (right + left) / (right - left);
	vertexNDC.y = 2 * vertexScreen.y / (top - bottom) - (top + bottom) / (top - bottom);

	// convert to raster space
	vertexRaster->x = (vertexNDC.x + 1) / 2 * imageWidth;
	// in raster space y is down so invert direction
	vertexRaster->y = (1 - vertexNDC.y) / 2 * imageHeight;
	vertexRaster->z = -vertexCamera.z;
}

double min3(double a, double b, double c)
{
	if (a <= b && a <= c)
		return (a);
	if (b <= a && b <= c)
		return (b);
	return (c);
}

double max3(double a, double b, double c)
{
	if (a >= b && a >= c)
		return (a);
	if (b >= a && b >= c)
		return (b);
	return (c);
}

double		edge_function(t_vec3d a, t_vec3d b, t_vec3d c)
{
	return ((c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x));
}

int imageWidth = 640;
int imageHeight = 480;
double worldToCamera = {0.707107, -0.331295, 0.624695, 0, 0, 0.883452, 0.468521, 0, -0.707107, -0.331295, 0.624695, 0, -1.63871, -5.747777, -40.400412, 1};

const uint32_t ntris = 3156;
const double nearClippingPLane = 1;
const double farClippingPLane = 1000;
double focalLength = 20; // in mm
// 35mm Full Aperture in inches
double filmApertureWidth = 0.980;
double filmApertureHeight = 0.735;

int main(int argc, char **argv)
{
	double cameraToWorld[4][4] = worldToCamera;

	// compute screen coordinates
	double t, b, l, r;

	computeScreenCoordinates(
			filmApertureWidth, filmApertureHeight,
			imageWidth, imageHeight,
			kOverscan,
			nearClippingPLane,
			focalLength,
			t, b, l, r);

	// define the frame-buffer and the depth-buffer. Initialize depth buffer
	// to far clipping plane.
	Vec3<unsigned char> *frameBuffer = new Vec3<unsigned char>[imageWidth * imageHeight];
	for (uint32_t i = 0; i < imageWidth * imageHeight; ++i) frameBuffer[i] = Vec3<unsigned char>(255);
	double *depthBuffer = new double[imageWidth * imageHeight];
	for (uint32_t i = 0; i < imageWidth * imageHeight; ++i) depthBuffer[i] = farClippingPLane;

	auto t_start = std::chrono::high_resolution_clock::now();

	for (uint32_t i = 0; i < ntris; ++i) {
	    const Vec3f &v0 = vertices[nvertices[i * 3]];
	    const Vec3f &v1 = vertices[nvertices[i * 3 + 1]];
	    const Vec3f &v2 = vertices[nvertices[i * 3 + 2]];

	    Vec3f v0Raster, v1Raster, v2Raster;
	    convertToRaster(v0, worldToCamera, l, r, t, b, nearClippingPLane, imageWidth, imageHeight, v0Raster);
	    convertToRaster(v1, worldToCamera, l, r, t, b, nearClippingPLane, imageWidth, imageHeight, v1Raster);
	    convertToRaster(v2, worldToCamera, l, r, t, b, nearClippingPLane, imageWidth, imageHeight, v2Raster);

	    v0Raster.z = 1 / v0Raster.z,
			v1Raster.z = 1 / v1Raster.z,
			v2Raster.z = 1 / v2Raster.z;


	    Vec2f st0 = st[stindices[i * 3]];
	    Vec2f st1 = st[stindices[i * 3 + 1]];
	    Vec2f st2 = st[stindices[i * 3 + 2]];

	    st0 *= v0Raster.z, st1 *= v1Raster.z, st2 *= v2Raster.z;

	    double xmin = min3(v0Raster.x, v1Raster.x, v2Raster.x);
	    double ymin = min3(v0Raster.y, v1Raster.y, v2Raster.y);
	    double xmax = max3(v0Raster.x, v1Raster.x, v2Raster.x);
	    double ymax = max3(v0Raster.y, v1Raster.y, v2Raster.y);

	    // the triangle is out of screen
	    if (xmin > imageWidth - 1 || xmax < 0 || ymin > imageHeight - 1 || ymax < 0) continue;

	    // be careful xmin/xmax/ymin/ymax can be negative. Don't cast to uint32_t
	    uint32_t x0 = std::max(int32_t(0), (int32_t)(std::floor(xmin)));
	    uint32_t x1 = std::min(int32_t(imageWidth) - 1, (int32_t)(std::floor(xmax)));
	    uint32_t y0 = std::max(int32_t(0), (int32_t)(std::floor(ymin)));
	    uint32_t y1 = std::min(int32_t(imageHeight) - 1, (int32_t)(std::floor(ymax)));

	    double area = edgeFunction(v0Raster, v1Raster, v2Raster);

	    for (uint32_t y = y0; y <= y1; ++y) {
	        for (uint32_t x = x0; x <= x1; ++x) {
	            Vec3f pixelSample(x + 0.5, y + 0.5, 0);
	            double w0 = edgeFunction(v1Raster, v2Raster, pixelSample);
	            double w1 = edgeFunction(v2Raster, v0Raster, pixelSample);
	            double w2 = edgeFunction(v0Raster, v1Raster, pixelSample);
	            if (w0 >= 0 && w1 >= 0 && w2 >= 0) {
	                w0 /= area;
	                w1 /= area;
	                w2 /= area;
	                double oneOverZ = v0Raster.z * w0 + v1Raster.z * w1 + v2Raster.z * w2;
	                double z = 1 / oneOverZ;
	                if (z < depthBuffer[y * imageWidth + x]) {
	                    depthBuffer[y * imageWidth + x] = z;

	                    Vec2f st = st0 * w0 + st1 * w1 + st2 * w2;

	                    st *= z;

	                    Vec3f v0Cam, v1Cam, v2Cam;
	                    worldToCamera.multVecMatrix(v0, v0Cam);
	                    worldToCamera.multVecMatrix(v1, v1Cam);
	                    worldToCamera.multVecMatrix(v2, v2Cam);

	                    double px = (v0Cam.x/-v0Cam.z) * w0 + (v1Cam.x/-v1Cam.z) * w1 + (v2Cam.x/-v2Cam.z) * w2;
	                    double py = (v0Cam.y/-v0Cam.z) * w0 + (v1Cam.y/-v1Cam.z) * w1 + (v2Cam.y/-v2Cam.z) * w2;

	                    Vec3f pt(px * z, py * z, -z); // pt is in camera space

	                    Vec3f n = (v1Cam - v0Cam).crossProduct(v2Cam - v0Cam);
	                    n.normalize();
	                    Vec3f viewDirection = -pt;
	                    viewDirection.normalize();

	                    double nDotView =  std::max(0.f, n.dotProduct(viewDirection));

	                    const int M = 10;
	                    double checker = (fmod(st.x * M, 1.0) > 0.5) ^ (fmod(st.y * M, 1.0) < 0.5);
	                    double c = 0.3 * (1 - checker) + 0.7 * checker;
	                    nDotView *= c;
	                    frameBuffer[y * imageWidth + x].x = nDotView * 255;
	                    frameBuffer[y * imageWidth + x].y = nDotView * 255;
	                    frameBuffer[y * imageWidth + x].z = nDotView * 255;
	                }
	            }
	        }
	    }
	}

	auto t_end = std::chrono::high_resolution_clock::now();
	auto passedTime = std::chrono::duration<double, std::milli>(t_end - t_start).count();
	std::cerr << "Wall passed time:  " << passedTime << " ms" << std::endl;

	std::ofstream ofs;
	ofs.open("./output.ppm");
	ofs << "P6\n" << imageWidth << " " << imageHeight << "\n255\n";
	ofs.write((char*)frameBuffer, imageWidth * imageWidth * 3);
	ofs.close();

	delete [] frameBuffer;
	delete [] depthBuffer;

	return 0;
}
