/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 19:03:56 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/10 21:46:31 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "quaternion.h"
#include "doom.h"

void	rotate_camera(t_camera *camera, t_vec3d rot_vec, double angle)
{
	camera->direction = vec3d_unit(quat_rot(camera->direction, rot_vec, angle));
	camera->right = vec3d_unit(quat_rot(camera->right, rot_vec, angle));
	camera->up = vec3d_unit(quat_rot(camera->up, rot_vec, angle));
}
