#include "vec3.h"
#include <math.h>

t_vec3l	vec3l(long x, long y, long z)
{
	t_vec3l	vec;

	vec.x = x;
	vec.y = y;
	vec.z = z;
	return (vec);
}

long	vec3l_length2(t_vec3l vec)
{
	return (vec.x * vec.x + vec.y * vec.y + vec.z * vec.z);
}

t_vec3l	vec3l_unit(t_vec3l vec)
{
	long	length;

	length = sqrt(vec3l_length2(vec));
	return (vec3l(vec.x / length, vec.y / length, vec.z / length));
}

t_vec3l	vec3l_add(t_vec3l vec_a, t_vec3l vec_b)
{
	return (vec3l(vec_a.x + vec_b.x, vec_a.y + vec_b.y, vec_a.z + vec_b.z));
}

t_vec3l	vec3l_sub(t_vec3l vec_a, t_vec3l vec_b)
{
	return (vec3l(vec_a.x - vec_b.x, vec_a.y - vec_b.y, vec_a.z - vec_b.z));
}
