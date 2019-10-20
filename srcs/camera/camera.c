/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 19:03:56 by roduquen          #+#    #+#             */
/*   Updated: 2019/10/20 11:03:26 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "quaternion.h"
#include "doom.h"

void	rotate_camera(t_camera *camera, t_vec3d rot_vec, double angle)
{
	t_vec3d	dir;
	t_vec3d	right;
	t_vec3d	up;

	dir = quat_rot(camera->direction, rot_vec, angle);
	right = quat_rot(camera->right, rot_vec, angle);
	up = quat_rot(camera->up, rot_vec, angle);
	camera->direction = vec3d_unit(dir);
	camera->right = vec3d_unit(right);
	camera->up = vec3d_unit(up);
}
