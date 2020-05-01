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

void		init_camera(t_doom *data)
{
	data->player.camera.direction = vec3d(0, 0, 1);
	data->player.sensitivity = M_PI / 90.0 / data->sensitivity;
	data->player.camera.right = vec3d(1, 0, 0);
	data->player.camera.up = vec3d(0, 1, 0);
	data->player.camera.origin.x = -1;
	data->player.camera.origin.y = -1;
	data->player.camera.origin.z = -1;
	data->sampling = 4;
	data->futur_sampling = 4;
}

static int	init_fonts(t_doom *data)
{
	if (TTF_Init() < 0)
		return (1);
	if (!(data->lib.ptrfont[0] = TTF_OpenFont(
					"./font/coalition/Coalition_v2.ttf", 150)))
		return (1);
	if (!(data->lib.ptrfont[1] = TTF_OpenFont(
					"./font/CGF_Locust_Resistance.ttf", 150)))
		return (1);
	if (!(data->lib.ptrfont[2] = TTF_OpenFont("./font/8th_Cargo.ttf", 35)))
		return (1);
	if (!(data->lib.ptrfont[3] = TTF_OpenFont("./font/8th_Cargo.ttf", 45)))
		return (1);
	if (!(data->lib.ptrfont[4] = TTF_OpenFont(
					"./font/xolonium/Xolonium-Regular.ttf", 25)))
		return (1);
	init_anim_state_start(data);
	return (0);
}

static int	init_texture(t_doom *data)
{
	if (!(data->lib.texture = SDL_CreateTexture(data->lib.renderer
					, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING
					, WIDTH, HEIGHT)))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture: %s"
				, SDL_GetError());
		return (1);
	}
	if (SDL_ShowCursor(SDL_DISABLE) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't hide cursor: %s"
				, SDL_GetError());
		return (1);
	}
	return (init_fonts(data));
}

static void	init_program2(t_doom *data)
{
	data->state = START;
	data->button = 0;
	data->load_page[0] = 0;
	data->load_page[1] = 0;
	data->player.health = 1000;
	data->sensitivity = 10;
	data->player.speed = 0;
	parse_input_file(data, "./files/inputs");
	data->lib.cam_keys = 0;
	data->lib.editor.mode = 0;
	data->lib.editor.alpha = 10;
	data->map_to_show = 0;
	data->map_name = "\0";
	init_map_colors(&data->lib);
	init_camera(data);
	pthread_mutex_init(&data->mutex, NULL);
}

int			init_program(t_doom *data)
{
	data->oriented[0] = 1;
	data->oriented[1] = 1;
	data->oriented[2] = 0;
	data->oriented[3] = 0;
	load_textures(data);
	data->actual_obj = -1;
	while (++data->actual_obj < NBR_OBJ)
		create_octree_model(data);
	init_program2(data);
	init_func_pointer(data);
	if (init_sdl(data))
		return (1);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	data->running = 1;
	init_normals(data);
	init_lights(data);
	return (init_texture(data));
}
