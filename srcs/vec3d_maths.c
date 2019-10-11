#include "vec3.h"
#include <math.h>

t_vec3d	vec3d(double x, double y, double z)
{
	t_vec3d	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

double	vec3d_length2(t_vec3d vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

t_vec3d	vec3d_unit(t_vec3d vec)
{
	double	length;

	length = sqrt(vec3d_length2(vec));
	return (vec3d(vec.x / length, vec.y / length, vec.z / length));
}

t_vec3d	vec3d_add(t_vec3d vec_a, t_vec3d vec_b)
{
	return (vec3d(vec_a.x + vec_b.x, vec_a.y + vec_b.y, vec_a.z + vec_b.z));
}

t_vec3d	vec3d_sub(t_vec3d vec_a, t_vec3d vec_b)
{
	return (vec3d(vec_a.x - vec_b.x, vec_a.y - vec_b.y, vec_a.z - vec_b.z));
}
