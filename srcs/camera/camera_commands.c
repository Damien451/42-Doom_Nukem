/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/19 12:35:54 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/16 16:01:38 by dacuvill         ###   ########.fr       */
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

static void	camera_release_key(SDL_Event *event, t_tabinputs *inputs, t_doom *data)
{
	if (event->key.type == SDL_KEYUP)
	{
		if ((unsigned int)event->key.keysym.sym == inputs->keycode[1])
			data->lib.cam_keys &= ~CAMERA_TR_LEFT;
		else if ((unsigned int)event->key.keysym.sym == inputs->keycode[3])
			data->lib.cam_keys &= ~CAMERA_TR_RIGHT;
		else if ((unsigned int)event->key.keysym.sym == inputs->keycode[0])
			data->lib.cam_keys &= ~CAMERA_TR_FRONT;
		else if ((unsigned int)event->key.keysym.sym == inputs->keycode[2])
			data->lib.cam_keys &= ~CAMERA_TR_BACK;
		else if ((unsigned int)event->key.keysym.sym == inputs->keycode[6])
			data->lib.cam_keys &= ~COURSE;
		else if (event->key.keysym.sym == SDLK_LCTRL)
		{
			data->lib.cam_keys |= SQUAT;
			data->lib.cam_keys &= ~CRAWL;
		}
		else if (event->key.keysym.sym == SDLK_h)
				data->lib.cam_keys &= ~BEST_SAMPLING;
	}
}

void		camera_press_key(SDL_Event *event, t_tabinputs *inputs, t_doom *data)
{
	data->player.speed = 0.0375 * (data->lib.cam_keys & COURSE ? 2 : 1) * (data->lib.cam_keys & CRAWL ? 0.25 : 1);
	if (event->key.type == SDL_KEYDOWN)
	{
		if ((unsigned int)event->key.keysym.sym == inputs->keycode[1])
			data->lib.cam_keys |= CAMERA_TR_LEFT;
		else if ((unsigned int)event->key.keysym.sym == inputs->keycode[3])
			data->lib.cam_keys |= CAMERA_TR_RIGHT;
		else if ((unsigned int)event->key.keysym.sym == inputs->keycode[0])
			data->lib.cam_keys |= CAMERA_TR_FRONT;
		else if ((unsigned int)event->key.keysym.sym == inputs->keycode[2])
			data->lib.cam_keys |= CAMERA_TR_BACK;
		else if ((unsigned int)event->key.keysym.sym == inputs->keycode[6])
			data->lib.cam_keys |= COURSE;
		else if ((unsigned int)event->key.keysym.sym == inputs->keycode[9])
		{
			if (data->player.acceleration.y == 0 && !(data->lib.cam_keys & WATER) && !(data->lib.cam_keys & SQUAT) && !(data->lib.cam_keys & CRAWL))
			{
				Mix_PlayChannel(CHANNEL_PLAYER_SOUNDS, data->mix.sounds[10], 0);
				data->player.acceleration.y = 0.4;
			}
		}
		else if (event->key.keysym.sym == SDLK_p)
		{
			if (WATER & data->lib.cam_keys)
				data->lib.cam_keys &= ~WATER;
			else
				data->lib.cam_keys |= WATER;
		}
		else if (event->key.keysym.sym == SDLK_LCTRL && data->player.acceleration.y == 0 && !(data->lib.cam_keys & WATER))
			data->lib.cam_keys |= CRAWL;
		else if (event->key.keysym.sym == SDLK_k && !event->key.repeat)
			data->photo = 1;
		else if (event->key.keysym.sym == SDLK_KP_PLUS)
		{
			if (data->player.inventory.selected_block < NBR_TEXTURES_EDITOR)
				data->player.inventory.selected_block++;
			else
				data->player.inventory.selected_block = 1;
		}
		else if (event->key.keysym.sym == SDLK_KP_MINUS)
		{
			if (data->player.inventory.selected_block > 1)
				data->player.inventory.selected_block--;
			else
				data->player.inventory.selected_block = NBR_TEXTURES_EDITOR;
		}
		else if (event->key.keysym.sym == SDLK_h)
				data->lib.cam_keys |= BEST_SAMPLING;
	}
	camera_release_key(event, inputs, data);
}
