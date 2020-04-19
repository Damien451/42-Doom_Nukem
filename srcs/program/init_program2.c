/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 14:48:26 by roduquen          #+#    #+#             */
/*   Updated: 2020/04/17 19:57:48 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic_lib.h"
#include "doom.h"
#include "inputs.h"
#include "player.h"
#include <time.h>
#include <SDL.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>

void		init_normals(t_doom *data)
{
	data->normal[X_MIN] = vec3d(1, 0, 0);
	data->normal[X_MAX] = vec3d(-1, 0, 0);
	data->normal[Y_MIN] = vec3d(0, 1, 0);
	data->normal[Y_MAX] = vec3d(0, -1, 0);
	data->normal[Z_MIN] = vec3d(0, 0, 1);
	data->normal[Z_MAX] = vec3d(0, 0, -1);
}

void		init_lights(t_doom *data)
{
	data->sun_light.type = SUN;
	data->power[SUN] = 7500;
	data->player_light.type = PLAYER;
	data->power[PLAYER] = 100;
}

int			init_icon(t_doom *data)
{
	SDL_Surface		*tmp_surface;

	tmp_surface = NULL;
	tmp_surface = SDL_CreateRGBSurfaceFrom((void *)data->lib.game_icon, 400,
			400, 32, 4 * 400, 0, 0, 0, 0);
	SDL_SetWindowIcon(data->lib.window, tmp_surface);
	SDL_FreeSurface(tmp_surface);
	return (0);
}

int			init_sdl(t_doom *data)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION,
				"Couldn't initialize SDL: %s", SDL_GetError());
		return (1);
	}
	if (!(data->lib.window = SDL_CreateWindow("DoomCraft", 0, 0, 960,
		540, SDL_WINDOW_SHOWN)))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s"
				, SDL_GetError());
		return (1);
	}
	init_icon(data);
	if (!(data->lib.renderer = SDL_CreateRenderer(data->lib.window, -1,
					SDL_RENDERER_ACCELERATED)))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION
				, "Couldn't create renderer: %s", SDL_GetError());
		return (1);
	}
	return (0);
}
