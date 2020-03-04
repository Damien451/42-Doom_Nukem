/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 12:35:54 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/04 14:49:17 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "doom.h"
#include "graphic_lib.h"
#include "inputs.h"
#include "vec3.h"
#include <math.h>
#include "mixer.h"

void			camera_mouse_motion(t_camera *camera, int *x, int *y
		, double *sensitivity)
{
	double	x_angle;
	double	move;

	if (*x)
		rotate_camera(camera, vec3d(0, 1, 0), *sensitivity * (double)*x);
	if (*y)
	{
		move = *sensitivity * (double)*y;
		x_angle = camera->x_angle + move;
		if (x_angle > -M_PI_2 + 0.1 && x_angle < M_PI_2 - 0.1)
		{
			camera->x_angle = x_angle;
			rotate_camera(camera, camera->right, move);
		}
	}
}

void		clamp_acceleration(t_vec3d *vec, double course)
{
	if (vec->x > 0.5 + course)
		vec->x = 0.5;
	else if (vec->x < -0.5 - course)
		vec->x = -0.5 - course;
	if (vec->y > 1.0 + course)
		vec->y = 1.0 + course;
	if (vec->z > 0.5 + course)
		vec->z = 0.5 + course;
	else if (vec->z < -0.5 - course)
		vec->z = -0.5 - course;
}

void		camera_event_translate(t_doom *data)
{
	t_vec3d		tmp;

	tmp = vec3d_scalar(data->player.acceleration, 0.7);
	if (data->lib.cam_keys & CAMERA_TR_LEFT)
	{
		tmp = vec3d_sub(tmp, vec3d_scalar(data->player.camera.right
					, data->player.speed));
	}
	if (data->lib.cam_keys & CAMERA_TR_RIGHT)
	{
		tmp = vec3d_add(tmp, vec3d_scalar(data->player.camera.right
					, data->player.speed));
	}
	if (data->lib.cam_keys & CAMERA_TR_FRONT)
	{
		tmp = vec3d_add(tmp, vec3d_scalar(data->player.camera.direction
					, data->player.speed));
	}
	if (data->lib.cam_keys & CAMERA_TR_BACK)
	{
		tmp = vec3d_sub(tmp, vec3d_scalar(data->player.camera.direction
					, data->player.speed));
	}
	if (!(data->lib.cam_keys & WATER))
		tmp.y = data->player.acceleration.y - 0.0450;
	clamp_acceleration(&tmp, data->lib.cam_keys & COURSE ? 0.5 : 0);
	data->player.acceleration = tmp;
}
