/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_program.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 14:48:26 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/05 19:12:29 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "graphic_lib.h"
#include "doom.h"
#include "inputs.h"
#include "player.h"
#include <time.h>
#include <SDL_image.h>
#include <SDL.h>
#include <pthread.h>
#include <fcntl.h>
#include <unistd.h>
#include "mesh.h"

void		load_skybox(t_doom *data)
{
	int		fd;

	fd = 0;
	data->skybox = malloc(sizeof(int*) * 6);
	while (fd < 6)
		data->skybox[fd++] = malloc(sizeof(int) * 512 * 512);
	fd = open("test.binary", O_RDONLY);
	read(fd, data->skybox[0], 512 * 512 * 4);
	close(fd);
	fd = open("test2.binary", O_RDONLY);
	read(fd, data->skybox[1], 512 * 512 * 4);
	close(fd);
	fd = open("test3.binary", O_RDONLY);
	read(fd, data->skybox[2], 512 * 512 * 4);
	close(fd);
	fd = open("test4.binary", O_RDONLY);
	read(fd, data->skybox[3], 512 * 512 * 4);
	close(fd);
	fd = open("test5.binary", O_RDONLY);
	read(fd, data->skybox[4], 512 * 512 * 4);
	close(fd);
	fd = open("test6.binary", O_RDONLY);
	read(fd, data->skybox[5], 512 * 512 * 4);
	close(fd);
}

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
	load_skybox(data);
}

void		init_bubbles(t_doom *data)
{
	int			i;

	i = 0;
	while (i < NB_BUBBLE)
	{
		data->tab[i].pos = rand() % WIDTH * HEIGHT;
		if (rand() % 2)
			rand();
		data->tab[i].speed = rand() % 10 + 1;
		if (rand() % 3)
			rand();
		data->tab[i].size = rand() % 10 + 4;
		if (rand() % 4)
			rand();
		data->tab[i++].color = (rand() % 256) << 16;
	}
}

static void	init_tab(t_doom *data)
{
	int			i;
	SDL_Surface	*surface;
	t_bubble	*tmp;
	t_bubble	*tmp2;

	init_bubbles(data);
	surface = IMG_Load("textures/Untitled.bmp");
	data->lib.start_bg = IMG_Load("textures/start_bg.bmp");
	i = 0;
	tmp = NULL;
	while (i < WIDTH * HEIGHT)
	{
		if (((int*)surface->pixels)[i] != -1)
		{
			if (!tmp)
			{
				tmp = malloc(sizeof(t_bubble));
				tmp->pos = i;
				tmp->next = NULL;
				data->bubble_list = tmp;
			}
			else
			{
				tmp->next = malloc(sizeof(t_bubble));
				tmp->next->pos = i;
				tmp->next->next = NULL;
				tmp = tmp->next;
			}
		}
		i++;
	}
	tmp = NULL;
	SDL_FreeSurface(surface);
	surface = IMG_Load("textures/eclair.bmp");
	i = 0;
	tmp2 = NULL;
	while (i < WIDTH * HEIGHT)
	{
		if (((int*)surface->pixels)[i] != -1 && ((unsigned int*)
				surface->pixels)[i] % 0x1000000 <= 0x888888)
		{
			if (!tmp)
			{
				tmp = malloc(sizeof(t_bubble));
				tmp->pos = i;
				tmp->next = NULL;
				data->lightning_list = tmp;
			}
			else
			{
				tmp->next = malloc(sizeof(t_bubble));
				tmp->next->pos = i;
				tmp->next->next = NULL;
				tmp = tmp->next;
			}
		}
		else if (((int*)surface->pixels)[i] != -1 && ((unsigned int*)
				surface->pixels)[i] % 0x1000000 <= 0x999999)
		{
			if (!tmp2)
			{
				tmp2 = malloc(sizeof(t_bubble));
				tmp2->pos = i;
				tmp2->next = NULL;
				data->lightning_list2 = tmp2;
			}
			else
			{
				tmp2->next = malloc(sizeof(t_bubble));
				tmp2->next->pos = i;
				tmp2->next->next = NULL;
				tmp2 = tmp2->next;
			}
		}
		i++;
	}
	SDL_FreeSurface(surface);
	load_textures(data);
}

static int	init_fonts(t_doom *data)
{
	if (TTF_Init() < 0)
		return (1);
	if (!(data->lib.ptrfont[0] = TTF_OpenFont(
				"./font/coalition/Coalition_v2.ttf", 200)))
		return (1);
	if (!(data->lib.ptrfont[1] = TTF_OpenFont(
				"./font/xolonium/Xolonium-Regular.ttf", 200)))
		return (1);
	if (!(data->lib.ptrfont[2] = TTF_OpenFont("./font/8th_Cargo.ttf", 35)))
		return (1);
	if (!(data->lib.ptrfont[3] = TTF_OpenFont(
				"./font/After_the_Goldrush.ttf", 200)))
		return (1);
	if (!(data->lib.ptrfont[4] = TTF_OpenFont("./font/8th_Cargo.ttf", 37)))
		return (1);
	if (!(data->lib.ptrfont[5] = TTF_OpenFont(
				"./font/xolonium/Xolonium-Regular.ttf", 25)))
		return (1);
	init_tab(data);
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
	int			fd;

	data->state = START;
	data->button = 0;
	data->load_page[0] = 0;
	data->load_page[1] = 0;
	data->player.health = 1000;
	data->sensitivity = 100;
	data->player.speed = 0;
	parse_input_file(data, "./files/inputs");
	data->lib.cam_keys = 0;
	data->lib.editor.mode = 0;
	data->lib.editor.alpha = 10;
	data->map_to_show = 0;
	data->map_name = "\0";
	init_map_colors(&data->lib);
	create_entity(&(data->entities), (t_vec3d){10.5, 2.5, 10.5}, IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/iron.bmp"));
	data->player.inventory.selected_block = 1;
	init_zbuf(&(data->zbuf));
	init_camera(data);
	pthread_mutex_init(&data->mutex, NULL);
	fd = open("test_new_subdivision.binary", O_RDONLY);
	read(fd, data->fire_model, 1048576);
	close(fd);
}

int			load_sampling(t_doom *data)
{
	int		size;
	int		fd;
	char	sizec[4];

	fd = open("sampling1.binary", O_RDONLY);
	read(fd, sizec, 4);
	size = *((int*)sizec);
	data->samplingt[0] = malloc(sizeof(int) * (size * 2 + 1));
	data->samplingt[0][0] = size;
	read(fd, &data->samplingt[0][1], size * 8);
	close(fd);
	fd = open("sampling4.binary", O_RDONLY);
	read(fd, sizec, 4);
	size = *((int*)sizec);
	data->samplingt[3] = malloc(sizeof(int) * (size * 2 + 1));
	data->samplingt[3][0] = size;
	read(fd, &data->samplingt[3][1], size * 8);
	close(fd);
	fd = open("hud.binary", O_RDONLY);
	read(fd, sizec, 4);
	size = *((int*)sizec);
	data->samplingt[6] = malloc(sizeof(int) * (size * 2 + 1));
	data->samplingt[6][0] = size;
	read(fd, &data->samplingt[6][1], size * 8);
	close(fd);
	return (0);
}

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
	data->sun_light = malloc(sizeof(t_light));
	data->sun_light->type = SUN;
	data->power[SUN] = 5000;
	data->player_light = malloc(sizeof(t_light));
	data->player_light->type = PLAYER;
	data->power[PLAYER] = 25;
}

int			init_sdl(t_doom *data)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s"
				, SDL_GetError());
		return (1);
	}
	if (!(data->lib.window = SDL_CreateWindow("Doom Nukem"
					, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH
					, HEIGHT, SDL_WINDOW_SHOWN)))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s"
				, SDL_GetError());
		return (1);
	}
	if (!(data->lib.renderer = SDL_CreateRenderer(data->lib.window, -1
					, SDL_RENDERER_ACCELERATED)))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION
				, "Couldn't create renderer: %s", SDL_GetError());
		return (1);
	}
	return (0);
}

int			init_z_buffer(t_doom *data)
{
	data->z_buffer = (double*)malloc(sizeof(double) * WIDTH * HEIGHT);
	if (data->z_buffer == NULL)
		return (1);
	data->frame_buffer = (unsigned int*)malloc(sizeof(unsigned int) * WIDTH * HEIGHT);
	if (data->frame_buffer == NULL)
		return (1);
	return (0);
}

int			init_meshes(t_doom *data)
{
	data->meshes = (t_mesh*)malloc(sizeof(t_mesh));
	data->meshes->next = NULL;
	data->meshes->triangle = (t_triangle*)malloc(sizeof(t_triangle));
	data->meshes->triangle->vertices[0].x = 10;
	data->meshes->triangle->vertices[0].y = 0;
	data->meshes->triangle->vertices[0].z = 0;
	data->meshes->triangle->vertices[1].x = 10;
	data->meshes->triangle->vertices[1].y = 10;
	data->meshes->triangle->vertices[1].z = 0;
	data->meshes->triangle->vertices[2].x = 10;
	data->meshes->triangle->vertices[2].y = 0;
	data->meshes->triangle->vertices[2].z = 10;
	data->meshes->triangle->next = NULL;
}

int			init_program(t_doom *data)
{
	load_sampling(data);
	init_program2(data);
	init_func_pointer(data);
	init_z_buffer(data);
	init_meshes(data);
	if (init_sdl(data))
		return (1);
	if (init_mixer(data))
		return (1);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	data->running = 1;
	init_normals(data);
	init_lights(data);
	return (init_texture(data));
}
