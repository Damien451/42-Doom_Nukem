/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 12:35:54 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/15 13:24:44 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "doom.h"
#include "vec3.h"
#include <math.h>

/*void		apply_motion(t_doom *data)
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
	}*/
//	course = vec3d_add(new_pos, course);
//	course.y += 1.0 - ((double)frame_s * 0.8 / 10.0);
//	check_player_clipping(&data->player.acceleration, &new_pos, data->map_to_save, data->player.position);
//	check_camera_clipping(&data->player.acceleration, &course, data->map_to_save, data->player.position);
//	data->player.camera.origin = course;
//	data->player.position = new_pos;
//}

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
		else if (event->key.keysym.sym == SDLK_k && !event->key.repeat)
			data->photo = 1;
		data->sampling = 4;
	}
	camera_release_key(event, data);
}
