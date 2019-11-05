/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 12:35:54 by roduquen          #+#    #+#             */
/*   Updated: 2019/11/01 20:08:27 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "doom.h"
#include "vec3.h"
#include <math.h>

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

	new_pos = vec3d_add(data->player.position, data->player.acceleration);
	check_if_inside_map(data, &new_pos);
	if (data->map_to_save[(int)(new_pos.x)][(int)data->player.position.y][(int)data->player.position.z])
	{
		if (new_pos.x < data->player.position.x)
			new_pos.x = floor(new_pos.x) + 1.001;
		else
			new_pos.x = floor(new_pos.x) - 0.001;
			data->player.acceleration.x = 0;
	}
	else if (data->map_to_save[(int)(new_pos.x)][(int)data->player.position.y + 1][(int)data->player.position.z])
	{
		if (new_pos.x < data->player.position.x)
			new_pos.x = floor(new_pos.x) + 1.001;
		else
			new_pos.x = floor(new_pos.x) - 0.001;
			data->player.acceleration.x = 0;
	}
	if (data->map_to_save[(int)new_pos.x][(int)(new_pos.y)][(int)data->player.position.z])
	{
		if (new_pos.y < data->player.position.y)
			new_pos.y = floor(new_pos.y) + 1.001;
		else
			new_pos.y = floor(new_pos.y) - 0.001;
			data->player.acceleration.y = 0;
	}
	else if (data->map_to_save[(int)new_pos.x][(int)(new_pos.y + 1.0)][(int)data->player.position.z])
	{
		if (new_pos.y < data->player.position.y)
			new_pos.y = floor(new_pos.y) + 1.001;
		else
			new_pos.y = floor(new_pos.y) - 0.001;
			data->player.acceleration.y = 0;
	}
	if (data->map_to_save[(int)new_pos.x][(int)(new_pos.y)][(int)new_pos.z])
	{
		if (new_pos.z < data->player.position.z)
			new_pos.z = floor(new_pos.z) + 1.001;
		else
			new_pos.z = floor(new_pos.z) - 0.001;
			data->player.acceleration.z = 0;
	}
	if (data->map_to_save[(int)new_pos.x][(int)(new_pos.y + 1)][(int)new_pos.z])
	{
		if (new_pos.z < data->player.position.z)
			new_pos.z = floor(new_pos.z) + 1.001;
		else
			new_pos.z = floor(new_pos.z) - 0.001;
			data->player.acceleration.z = 0;
	}
	data->player.position = new_pos;
	new_pos.y += 1;
	data->player.camera.origin = new_pos;

}

void			camera_mouse_motion(t_camera *camera, int *x, int *y
	, double *sensitivity)
{
	double	x_angle;
	double	move;

	if (*x)
		rotate_camera(camera, Y_AXIS, *sensitivity * (double)*x);
	if (*y)
	{
		move = *sensitivity * (double)*y;
		x_angle = camera->x_angle + move;
		if (x_angle > -1 && x_angle < 1)
		{
			camera->x_angle = x_angle;
			rotate_camera(camera, camera->right, move);
		}
	}
}

void		clamp_acceleration(t_vec3d *vec)
{
	if (vec->x > 0.5)
		vec->x = 0.5;
	else if (vec->x < -0.5)
		vec->x = -0.5;
	if (vec->y > 0.5)
		vec->y = 0.5;
	if (vec->z > 0.5)
		vec->z = 0.5;
	else if (vec->z < -0.5)
		vec->z = -0.5;
}

void		camera_event_translate(t_doom *data)
{
	t_vec3d		tmp;

	tmp = vec3d_scalar(data->player.acceleration, 0.8);
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
		tmp.y = data->player.acceleration.y - 0.0225;
	clamp_acceleration(&tmp);
	data->player.acceleration = tmp;
	apply_motion(data);
}

static void	camera_release_key(SDL_Event *event, t_doom *data)
{
	if (event->key.type == SDL_KEYUP)
	{
		if (event->key.keysym.sym == SDLK_a)
			data->lib.cam_keys &= ~CAMERA_TR_LEFT;
		else if (event->key.keysym.sym == SDLK_d)
			data->lib.cam_keys &= ~CAMERA_TR_RIGHT;
		else if (event->key.keysym.sym == SDLK_w)
			data->lib.cam_keys &= ~CAMERA_TR_FRONT;
		else if (event->key.keysym.sym == SDLK_s)
			data->lib.cam_keys &= ~CAMERA_TR_BACK;
		else if (event->key.keysym.sym == SDLK_LSHIFT)
			data->lib.cam_keys &= ~COURSE;
		else if (event->key.keysym.sym == SDLK_LCTRL)
			data->lib.cam_keys &= ~SQUAT;
	}
}

void		camera_press_key(SDL_Event *event, t_doom *data)
{
	data->player.speed = 0.05;
	if (event->key.type == SDL_KEYDOWN)
	{
		if (event->key.keysym.sym == SDLK_a)
			data->lib.cam_keys |= CAMERA_TR_LEFT;
		else if (event->key.keysym.sym == SDLK_d)
			data->lib.cam_keys |= CAMERA_TR_RIGHT;
		else if (event->key.keysym.sym == SDLK_w)
			data->lib.cam_keys |= CAMERA_TR_FRONT;
		else if (event->key.keysym.sym == SDLK_s)
			data->lib.cam_keys |= CAMERA_TR_BACK;
		else if (event->key.keysym.sym == SDLK_LSHIFT)
			data->lib.cam_keys |= COURSE;
		else if (event->key.keysym.sym == SDLK_SPACE && data->player.acceleration.y == 0 && !(data->lib.cam_keys & WATER))
			data->player.acceleration.y = 0.28;
		else if (event->key.keysym.sym == SDLK_p)
		{
			if (WATER & data->lib.cam_keys)
				data->lib.cam_keys &= ~WATER;
			else
				data->lib.cam_keys |= WATER;
		}
		else if (event->key.keysym.sym == SDLK_LCTRL)
			data->lib.cam_keys |= SQUAT;
		data->sampling = 4;
	}
	camera_release_key(event, data);
}
