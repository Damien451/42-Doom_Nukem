/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quaternion_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 19:06:33 by roduquen          #+#    #+#             */
/*   Updated: 2019/10/20 10:39:27 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "quaternion.h"
#include "vec3.h"

t_vec3d			quat_rot_with_quat(t_vec3d vec, t_quaternion quat_rot_vec)
{
	t_quaternion	quat_vec_dir;
	t_quaternion	quat_result;

	quat_vec_dir.x = vec.x;
	quat_vec_dir.y = vec.y;
	quat_vec_dir.z = vec.z;
	quat_vec_dir.w = 0;
	quat_result = quaternion_mul(quat_rot_vec, quat_vec_dir);
	quat_result = quaternion_mul(quat_result, quaternion_conj(quat_rot_vec));
	vec.x = quat_result.x;
	vec.y = quat_result.y;
	vec.z = quat_result.z;
	return (vec);
}

t_vec3d			quat_rot(t_vec3d vec, t_vec3d rot_vec, double angle)
{
	t_quaternion	quat_rot_vec;

	quat_rot_vec = vec3d_to_rotate_quaternion(rot_vec, angle);
	return (quat_rot_with_quat(vec, quat_rot_vec));
}

t_quaternion	xyz_rot_to_quat(t_vec3d rotation)
{
	double			cosinus[3];
	double			sinus[3];
	t_quaternion	quat;

	cosinus[0] = cos(rotation.x / 2);
	cosinus[1] = cos(rotation.y / 2);
	cosinus[2] = cos(rotation.z / 2);
	sinus[0] = sin(rotation.x / 2);
	sinus[1] = sin(rotation.y / 2);
	sinus[2] = sin(rotation.z / 2);
	quat.x = sinus[0] * cosinus[1] * cosinus[2] - cosinus[0] * sinus[1]
		* sinus[2];
	quat.y = cosinus[0] * sinus[1] * cosinus[2] + sinus[0] * cosinus[1]
		* sinus[2];
	quat.z = cosinus[0] * cosinus[1] * sinus[2] - sinus[0] * sinus[1]
		* cosinus[2];
	quat.w = cosinus[0] * cosinus[1] * cosinus[2] + sinus[0] * sinus[1]
		* sinus[2];
	return (quat);
}
