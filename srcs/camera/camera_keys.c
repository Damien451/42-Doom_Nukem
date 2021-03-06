/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:47:38 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/10 16:47:11 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "doom.h"
#include "graphic_lib.h"
#include "gameplay.h"
#include "inputs.h"
#include "vec3.h"
#include <math.h>
#include "mixer.h"

static void	camera_release_key(SDL_Event *event, t_tabinputs *inputs
	, t_doom *data)
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
		else if ((unsigned int)event->key.keysym.sym == inputs->keycode[5])
			data->lib.cam_keys &= ~COURSE;
		else if ((unsigned int)event->key.keysym.sym == inputs->keycode[6])
		{
			data->lib.cam_keys |= SQUAT;
			data->lib.cam_keys &= ~CRAWL;
		}
	}
}

static void	camera_press_key3(SDL_Event *event, t_tabinputs *inputs,
	t_doom *data)
{
	if ((unsigned int)event->key.keysym.sym == inputs->keycode[9])
	{
		data->futur_sampling++;
		if (data->futur_sampling > 6)
			data->futur_sampling = 2;
	}
	else if (event->key.keysym.sym == SDLK_RETURN &&
		data->map_to_save[(int)data->player.camera.origin.x]
		[(int)data->player.camera.origin.y - 2]
		[(int)data->player.camera.origin.z] == ID_FINISH_BLOCK + 1 &&
		data->state == PLAYING)
	{
		leave_game(data, &data->player);
		switch_state(data, PLAYING, FINISHED);
	}
	else if ((unsigned int)event->key.keysym.sym == inputs->keycode[4]
		&& !data->player.inventory.lag && data->player.inventory.ammo < 8
		&& data->player.inventory.ammo_stock)
	{
		reload(&data->player);
		data->player.inventory.weapon_state = WEAPON_RELOAD;
		Mix_PlayChannel(CHANNEL_SOUNDS, data->mix.sounds[12], 0);
		data->player.inventory.lag = 30;
	}
}

static void	camera_press_key2(SDL_Event *event, t_tabinputs *inputs,
	t_doom *data)
{
	if ((unsigned int)event->key.keysym.sym == inputs->keycode[7])
	{
		if (data->player.acceleration.y == 0 && !(data->lib.cam_keys & FLY)
			&& !(data->lib.cam_keys & SQUAT) && !(data->lib.cam_keys & CRAWL))
		{
			Mix_PlayChannel(CHANNEL_PLAYER_SOUNDS, data->mix.sounds[10], 0);
			data->player.acceleration.y = 0.4;
		}
	}
	else if ((unsigned int)event->key.keysym.sym == inputs->keycode[6]
		&& data->player.acceleration.y == 0 && !(data->lib.cam_keys & FLY))
		data->lib.cam_keys |= CRAWL;
	else if ((unsigned int)event->key.keysym.sym == inputs->keycode[8]
		&& !event->key.repeat)
		data->photo = 1;
	else if ((unsigned int)event->key.keysym.sym == inputs->keycode[10])
	{
		if (!(data->lib.cam_keys & BEST_SAMPLING))
			data->lib.cam_keys |= BEST_SAMPLING;
		else
			data->lib.cam_keys &= ~BEST_SAMPLING;
	}
	camera_press_key3(event, inputs, data);
}

void		camera_press_key(SDL_Event *event, t_tabinputs *inputs,
	t_doom *data)
{
	data->player.speed = 0.0375 * (data->lib.cam_keys & COURSE ? 2 : 1)
		* (data->lib.cam_keys & CRAWL ? 0.25 : 1);
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
		else if ((unsigned int)event->key.keysym.sym == inputs->keycode[5])
			data->lib.cam_keys |= COURSE;
		camera_press_key2(event, inputs, data);
	}
	camera_release_key(event, inputs, data);
}
