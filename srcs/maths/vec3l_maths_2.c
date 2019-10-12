#include "vec3.h"

t_vec3l	vec3l_mul(t_vec3l vec_a, t_vec3l vec_b)
{
	return (vec3l(vec_a.x * vec_b.x, vec_a.y * vec_b.y, vec_a.z * vec_b.z));
}

t_vec3l	vec3l_cross(t_vec3l vec_a, t_vec3l vec_b)
{
	return (vec3l(vec_a.y * vec_b.z - vec_a.z * vec_b.y
				, vec_a.z * vec_b.x - vec_a.x * vec_b.z
				, vec_a.x * vec_b.y - vec_a.y * vec_b.x));
}

t_vec3l	vec3l_scalar(t_vec3l vec, long scalar)
{
	return (vec3l(vec.x * scalar, vec.y * scalar, vec.z * scalar));
}

long	vec3l_dot(t_vec3l vec_a, t_vec3l vec_b)
{
	return (vec_a.x * vec_b.x + vec_a.y * vec_b.y + vec_a.z * vec_b.z);
}
