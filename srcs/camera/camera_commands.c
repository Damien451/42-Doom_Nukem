/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 12:35:54 by roduquen          #+#    #+#             */
/*   Updated: 2019/11/03 23:26:06 by roduquen         ###   ########.fr       */
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
	double		squat;
	t_vec3d		course;
	static int	frame_s = 0;
	static int	frame_r = 0;

	if (data->lib.cam_keys & SQUAT)
	{
		if (frame_s != 10)
			frame_s++;
	}
	else if (frame_s)
	{
		frame_s -= 2;
		if (frame_s < 0)
			frame_s = 0;
	}
	squat = 0.03 * (data->lib.cam_keys & SQUAT ? 0.10 : 1.0);
	if ((data->lib.cam_keys & COURSE || data->lib.cam_keys & SQUAT) && (data->player.acceleration.x >= squat || data->player.acceleration.x <= -squat || data->player.acceleration.z >= squat || data->player.acceleration.z <= -squat))
	{
		if (frame_r / 12 == 0)
		{
			course = vec3d_scalar(data->player.camera.right, frame_r / 12.0);
			course = vec3d_scalar(course, 0.1);
			course.y = frame_r * 0.005;
			frame_r++;
		}
		else if (frame_r / 12 == 1)
		{
			course = vec3d_scalar(data->player.camera.right, 1.0 - (frame_r - 12) / 12.0);
			course = vec3d_scalar(course, 0.1);
			course.y = 12.0 * 0.005 - (frame_r - 12) * 0.005;
			frame_r++;
		}
		else if (frame_r / 12 == 2)
		{
			course = vec3d_scalar(data->player.camera.right, 0.0 - (frame_r - 24) / 12.0);
			course = vec3d_scalar(course, 0.1);
			course.y = 0.0 - (frame_r - 24) * 0.005;
			frame_r++;
		}
		else
		{
			if (frame_r / 12 == 3)
			{
				course = vec3d_scalar(data->player.camera.right, -1.0 + (frame_r - 36) / 12.0);
				course = vec3d_scalar(course, 0.1);
				course.y = -12.0 * 0.005 + (frame_r - 36) * 0.005;
				frame_r++;
			}
			if (frame_r / 12 == 4)
			{
				course.x = 0;
				course.z = 0;
				course.y = 0;
				frame_r = 0;
			}
		}
	}
	else
	{
		frame_r = 0;
		course.y = 0;
	}
	new_pos = vec3d_add(data->player.position, data->player.acceleration);
	check_if_inside_map(data, &new_pos);
	course = vec3d_add(new_pos, course);
	course.y += 1.0 - ((double)frame_s * 0.8 / 10.0);
	check_player_clipping(&data->player.acceleration, &new_pos, data->map_to_save, data->player.position);
	check_camera_clipping(&data->player.acceleration, &course, data->map_to_save, data->player.position);
/*	if (data->map_to_save[(int)(new_pos.x + course.x)][(int)(data->player.position.y)][(int)data->player.position.z])
	{
		if (new_pos.x < data->player.position.x)
			new_pos.x = floor(new_pos.x) + 1.001;
		else
			new_pos.x = floor(new_pos.x) - 0.001;
		data->player.acceleration.x = 0;
	}*/
/*	if (data->map_to_save[(int)(new_pos.x + course.x)][(int)(new_pos.y+ course.y)][(int)data->player.position.z])
	{
		if (new_pos.y < data->player.position.y)
			new_pos.y = floor(new_pos.y) + 1.001;
		else
			new_pos.y = floor(new_pos.y) - 0.001;
		data->player.acceleration.y = 0;
	}*/
/*	if (data->map_to_save[(int)new_pos.x][(int)(new_pos.y + squat + course.y)][(int)new_pos.z])
	{
		if (new_pos.z < data->player.position.z)
			new_pos.z = floor(new_pos.z) + 1.001;
		else
			new_pos.z = floor(new_pos.z) - 0.001;
		data->player.acceleration.z = 0;
	}*/
	data->player.camera.origin = course;
	data->player.position = new_pos;
	//printf("data->player.camera.origin = (%.2f|%.2f|%.2f) || player = (%.2f|%.2f|%.2f)\n", course.x, course.y, course.z, new_pos.x, new_pos.y, new_pos.z);
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
		if (x_angle > -1.2 && x_angle < 1.2)
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
	clamp_acceleration(&tmp, data->lib.cam_keys & COURSE ? 0.5 : 0);
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
	data->player.speed = 0.025 * (data->lib.cam_keys & COURSE ? 1.5 : 1) * (data->lib.cam_keys & SQUAT ? 0.2 : 1);
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
