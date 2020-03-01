/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterization.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 14:01:14 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/01 17:47:41 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mesh.h"
#include "matrix.h"
#include "doom.h"

t_vec3d			perspective_proj(t_vec3d *vertex, double matrix[4][4])
{
	t_vec3d	projected;
	t_vec3d	new;

	matrix44_vec3d_mul(matrix, *vertex, &new);
//	printf("new : x = %.2f, y = %.2f, z = %.2f\n", new.x, new.y, new.z);
	projected.x = new.x / new.z * 1080 * FOV;
	projected.y = new.y / new.z * 1920 * POV;
	projected.z = new.z;
	return (projected);
}

int			create_bounding_box(t_vec3d vertices[3], t_vec3d bbox[2])
{
	int			i;

	bbox[0].x = INFINITY;
	bbox[0].y = INFINITY;
	bbox[1].x = -INFINITY;
	bbox[1].y = -INFINITY;
	i = 0;
	while (i < 3)
	{
	//	printf("%.2f || %.2f\n", vertices[i].x, vertices[i].y);
		if (vertices[i].x < bbox[0].x)
			bbox[0].x = vertices[i].x;
		if (vertices[i].x > bbox[1].x)
			bbox[1].x = vertices[i].x;
		if (vertices[i].y < bbox[0].y)
			bbox[0].y = vertices[i].y;
		if (vertices[i].y > bbox[1].y)
			bbox[1].y = vertices[i].y;
		i++;
	}
	return (0);
}

double		edge_function(t_vec3d a, t_vec3d b, t_vec3d c)
{
	return ((c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x - a.x));
}

int			is_inside_triangle(t_vec3d *bary, t_vec3d vertices[3])
{
	double		tmp[3];
	double		area;

	tmp[0] = edge_function(vertices[1], vertices[2], *bary);
	if (tmp[0] >= 0)
	{
		tmp[1] = edge_function(vertices[2], vertices[0], *bary);
		if (tmp[1] >= 0)
		{
			tmp[2] = edge_function(vertices[0], vertices[1], *bary);
			if (tmp[2] >= 0)
			{
				area = edge_function(vertices[0], vertices[1], vertices[2]);
				bary->x = tmp[0] / area;
				bary->y = tmp[1] / area;
				bary->z = tmp[2] / area;
				return (0);
			}
		}
	}
	return (1);
}

int			loop_over_bounding_box(t_vec3d vertices[3], t_vec3d bbox[2]
	, double *z_buffer, unsigned int *image, t_tri tri, unsigned int *png)
{
	t_vec3l		min;
	t_vec3l		max;
	double		distance;
	double		tmp;
	t_vec3d		bary;
	double		pl[50];

	min.x = bbox[0].x;
	if (min.x < 0)
		min.x = 0;
	max.x = (bbox[1].x + 1.0);
	max.y = (bbox[1].y + 1.0);
	if (max.x >= WIDTH)
		max.x = WIDTH - 1;
	if (max.y >= HEIGHT)
		max.y = HEIGHT - 1;
	while (min.x <= max.x)
	{
		min.y = bbox[0].y;
		if (min.y < 0)
			min.y = 0;
		while (min.y <= max.y)
		{
			bary.x = min.x;
			bary.y = min.y;
			if (!is_inside_triangle(&bary, vertices))
			{
				tmp = vertices[0].z * bary.x + vertices[1].z * bary.y
					+ vertices[2].z * bary.z;
				distance = 1 / tmp;
				if (distance > 0 && distance < z_buffer[min.x + min.y * WIDTH])
				{
					z_buffer[min.x + min.y * WIDTH] = distance;
					pl[0] = bary.x * tri.textures[0].x + bary.y * tri.textures[1].x + bary.z * tri.textures[2].x;
					pl[1] = bary.x * tri.textures[0].y + bary.y * tri.textures[1].y + bary.z * tri.textures[2].y;
					image[min.x + min.y * WIDTH] = png[(int)(pl[0] * 4096) + (int)(pl[1] * 4096 * 4096)];
				}
			}
			min.y++;
		}
		min.x++;
	}
	return (0);
}

int			convert_camera_to_matrix44(t_doom *data, double matrix[4][4])
{
	matrix[2][0] = -data->player.camera.direction.x;
	matrix[2][1] = -data->player.camera.direction.y;
	matrix[2][2] = -data->player.camera.direction.z;
	matrix[1][0] = data->player.camera.up.x;
	matrix[1][1] = data->player.camera.up.y;
	matrix[1][2] = data->player.camera.up.z;
	matrix[0][0] = data->player.camera.right.x;
	matrix[0][1] = data->player.camera.right.y;
	matrix[0][2] = data->player.camera.right.z;
	matrix[3][0] = data->player.camera.origin.x;
	matrix[3][1] = data->player.camera.origin.y;
	matrix[3][2] = data->player.camera.origin.z;
	matrix[0][3] = 0;
	matrix[1][3] = 0;
	matrix[2][3] = 0;
	matrix[3][3] = 1;
	return (0);
}

int			set_z_buffer(double *z_buffer)
{
	int				i;

	i = 0;
	while (i < WIDTH * HEIGHT)
		z_buffer[i++] = INFINITY;
	return (0);
}

int			rasterization(t_doom *data, t_mesh *meshes)
{
	int				i;
	t_vec3d			vertices[3];
	t_vec3d			bbox[2];
	t_tri			*obj;
	t_triangle		*triangle;
	double			world_to_camera[4][4];
	double			camera_to_world[4][4];
	int				j;

//	convert_camera_to_matrix44(data, camera_to_world);
//	matrix44_inverse(camera_to_world, world_to_camera);
	matrix44_identity(world_to_camera);
	set_z_buffer(data->z_buffer);
	obj = data->tri;
	i = 0;
	while (i < 4224)
	{
		vertices[0] = perspective_proj(&obj[i].vertices[0], world_to_camera);
		vertices[1] = perspective_proj(&obj[i].vertices[1], world_to_camera);
		vertices[2] = perspective_proj(&obj[i].vertices[2], world_to_camera);
//		printf("projected1: x = %.2f, y = %.2f\n", vertices[0].x, vertices[0].y);
//		printf("projected2: x = %.2f, y = %.2f\n", vertices[1].x, vertices[1].y);
//		printf("projected3: x = %.2f, y = %.2f\n", vertices[2].x, vertices[2].y);
		create_bounding_box(vertices, bbox);
		loop_over_bounding_box(vertices, bbox, data->z_buffer, data->frame_buffer, obj[i], (unsigned int*)data->png);
		i++;
	}
}
