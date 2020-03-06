/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_keys.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 14:47:38 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/06 18:03:55 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "doom.h"
#include "graphic_lib.h"
#include "inputs.h"
#include "vec3.h"
#include <math.h>
#include "mixer.h"

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

static void camera_press_key3(SDL_Event *event, t_tabinputs *inputs,
	t_doom *data)
{
	if (event->key.keysym.sym == SDLK_h)
		data->lib.cam_keys |= BEST_SAMPLING;
	else if (event->key.keysym.sym == SDLK_RETURN && data->map_to_save[
		(int)data->player.camera.origin.x]
		[(int)data->player.camera.origin.y - 2]
		[(int)data->player.camera.origin.z] == ID_FINISH_BLOCK + 1 &&
		data->state == PLAYING)
	{
		leave_game(data, &data->player);
		switch_state(data, PLAYING, FINISHED);
	}
}

static void camera_press_key2(SDL_Event *event, t_tabinputs *inputs,
	t_doom *data)
{
	if ((unsigned int)event->key.keysym.sym == inputs->keycode[9])
	{
		if (data->player.acceleration.y == 0 && !(data->lib.cam_keys & FLY)
			&& !(data->lib.cam_keys & SQUAT) && !(data->lib.cam_keys & CRAWL))
		{
			Mix_PlayChannel(CHANNEL_PLAYER_SOUNDS, data->mix.sounds[10], 0);
			data->player.acceleration.y = 0.4;
		}
	}
	else if (event->key.keysym.sym == SDLK_LCTRL
		&& data->player.acceleration.y == 0 && !(data->lib.cam_keys & FLY))
		data->lib.cam_keys |= CRAWL;
	else if (event->key.keysym.sym == SDLK_k && !event->key.repeat)
		data->photo = 1;
	else if (event->key.keysym.sym == SDLK_p)
	{
		if (FLY & data->lib.cam_keys)
			data->lib.cam_keys &= ~FLY;
		else
			data->lib.cam_keys |= FLY;
	}
	else
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
		else if ((unsigned int)event->key.keysym.sym == inputs->keycode[6])
			data->lib.cam_keys |= COURSE;
		else
            camera_press_key2(event, inputs, data);
    }
	camera_release_key(event, inputs, data);
}
