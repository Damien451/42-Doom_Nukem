/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event_loop.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 17:35:48 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/07 13:34:00 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "player.h"

static void		inventory_selection(t_doom *data, SDL_Event *event)
{
	int		max;

	max = (data->state == PLAYING ? 5 : NBR_TEXTURES_EDITOR - 2);
	if (event->wheel.y > 0)
	{
		data->player.inventory.selected =
		(data->player.inventory.selected + event->wheel.y > max ?
		max : data->player.inventory.selected + event->wheel.y);
	}
	else if (event->wheel.y < 0)
	{
		data->player.inventory.selected =
		(data->player.inventory.selected + event->wheel.y < 0 ?
		0 : data->player.inventory.selected + event->wheel.y);
	}
}

static void		event_loop2(t_doom *data, t_graphic_lib *lib)
{
	if (lib->event.type == SDL_MOUSEWHEEL && lib->event.wheel.y != 0)
		inventory_selection(data, &lib->event);
	if (lib->event.type == SDL_MOUSEBUTTONDOWN
		&& lib->event.button.button == SDL_BUTTON_RIGHT)
		lib->cam_keys |= RIGHT_CLICK;
	else if (lib->event.type == SDL_MOUSEBUTTONUP
		&& lib->event.button.button == SDL_BUTTON_RIGHT)
		lib->cam_keys &= ~RIGHT_CLICK;
	if (lib->event.type == SDL_MOUSEBUTTONDOWN
		&& lib->event.button.button == SDL_BUTTON_LEFT)
		lib->cam_keys |= LEFT_CLICK;
	else if (lib->event.type == SDL_MOUSEBUTTONUP
		&& lib->event.button.button == SDL_BUTTON_LEFT)
		lib->cam_keys &= ~LEFT_CLICK;
	camera_press_key(&lib->event, &data->tabinputs, data);
}

void			event_loop(t_doom *data, t_graphic_lib *lib)
{
	data->player.physics.camera.direction = data->player.camera.direction;
	data->player.physics.camera.right = data->player.camera.right;
	data->player.physics.camera.up = data->player.camera.up;
	while (SDL_PollEvent(&lib->event))
	{
		if (lib->event.type == SDL_KEYDOWN
			&& lib->event.key.keysym.sym == SDLK_ESCAPE
			&& data->state == PLAYING)
			switch_state(data, PLAYING, PAUSE);
		else if (lib->event.type == SDL_KEYDOWN
			&& lib->event.key.keysym.sym == SDLK_ESCAPE)
		{
			leave_game(data, &data->player);
			switch_state(data, EDITION_MODE, EDITOR);
		}
		if (lib->event.type == SDL_MOUSEMOTION)
			camera_mouse_motion(&data->player.physics.camera,
			&lib->event.motion.xrel, &lib->event.motion.yrel,
			&data->player.sensitivity);
		event_loop2(data, lib);
	}
}
