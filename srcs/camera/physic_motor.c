/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physic_motor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 17:17:41 by roduquen          #+#    #+#             */
/*   Updated: 2019/10/28 21:24:00 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "doom.h"
#include "player.h"

void		clamp_acceleration(t_vec3d *vec)
{
	if (vec->x > 1.0)
		vec->x = 1.0;
	else if (vec->x < -1.0)
		vec->x = -1.0;
	if (vec->y > 1.0)
		vec.y = 1.0;
	else if (vec->y < -2.0)
		vec->y = -2.0;
	if (vec->z > 1.0)
		vec->z = 1.0;
	else if (vec->z < -1.0)
		vec->z = -1.0;
}

void		camera_event_translate(t_doom *data)
{
	t_vec3d		tmp;

	tmp = data->player.acceleration;
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
		tmp.y = data->player.acceleration.y - 0.00098;
	clamp_acceleration(&tmp);
}

void		check_if_inside_map(t_doom *data, t_vec3d *position)
{
	if (position->x > 63.7)
	{
		data->player.acceleration.x = 0;
		position->x = 63.7;
	}
	else if (position->x < 0.3)
	{
		data->player.acceleration.x = 0;
		position->x = 0.3;
	}
	if (position->y > 63.7)
	{
		data->player.acceleration.y = 0;
		position->y = 63.7;
	}
	else if (position->y < 0.3)
	{
		data->player.acceleration.y = 0;
		position->y = 0.3;
	}
	if (position->z > 63.7)
	{
		data->player.acceleration.z = 0;
		position->z = 63.7;
	}
	else if (position->z < 0.3)
	{
		data->player.acceleration.z = 0;
		position->z = 0.3;
	}
}

void		apply_motion(t_doom *data)
{
	t_vec3d		new_pos;

	new_pos = vec3d_add(data->player.camera.origin, data->player.acceleration);
	check_if_inside_map(data, &new_pos);
	if (data->map_to_save[new_pos.x][data->player.camera.origin.y][data->player.camera.origin.z])
	{
		if (new_pos.x < data->player.camera.origin.x)
			new_pos.x = floor(new_pos.x) + 1.0;
		else
			new_pos.x = floor(new_pos.x) - 1.0;
		data->player.acceleration.x = 0;
	}
	if (data->map_to_save[new_pos.x][new_pos.y][data->player.camera.origin.z])
	{
		if (new_pos.y < data->player.camera.origin.y)
			new_pos.y = floor(new_pos.y) + 1.0;
		else
			new_pos.y = floor(new_pos.y) - 1.0;
		data->player.acceleration.y = 0;
	}
	if (data->map_to_save[new_pos.x][new_pos.y][new_pos.z])
	{
		if (new_pos.z < data->player.camera.origin.z)
			new_pos.z = floor(new_pos.z) + 1.0;
		else
			new_pos.z = floor(new_pos.z) - 1.0;
		data->player.acceleration.z = 0;
	}
	data->player.camera.origin = new_pos;
}
