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

int			init_light(t_doom *data)
{
	t_light		*tmp;
	int			i;

	data->sun_light = malloc(sizeof(t_light));
	data->sun_light->type = SUN;
	data->power[SUN] = 5000;
	data->player_light = malloc(sizeof(t_light));
	data->player_light->type = PLAYER;
	data->power[PLAYER] = 25;
	data->light = malloc(sizeof(t_light));
	data->light->type = TORCH;
	data->light->position = vec3d(19.5, 40.5, 2.5);
	tmp = data->light;
	tmp->next = NULL;
	i = 10;
	while (i < 64)
	{
		tmp->next = malloc(sizeof(t_light));
		tmp->next->type = TORCH;
		tmp->next->position = vec3d(19.5, 40.5, i + 0.5);
		i += 8;
		tmp = tmp->next;
	}
	i = 2;
	while (i < 64)
	{
		tmp->next = malloc(sizeof(t_light));
		tmp->next->type = TORCH;
		tmp->next->position = vec3d(35.5, 40.5, i + 0.5);
		i += 8;
		tmp = tmp->next;
	}
	tmp->next = malloc(sizeof(t_light));
	tmp->next->type = TORCH;
	tmp->next->position = vec3d(27.5, 44.5, 32.5);
	tmp = tmp->next;
	tmp->next = malloc(sizeof(t_light));
	tmp->next->type = SUN;
	tmp->next->next = NULL;
	return (0);
}

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
	data->player.camera.direction = Z_AXIS;
	data->player.sensitivity = SENSITIVITY;
	data->player.camera.right = X_AXIS;
	data->player.camera.up = Y_AXIS;
	data->player.camera.origin.x = -1;
	data->player.camera.origin.y = -1;
	data->player.camera.origin.z = -1;
	data->sampling = 4;
	init_light(data);
	load_skybox(data);
}

static void	init_tab(t_doom *data)
{
	int			i;
	SDL_Surface	*surface;
	t_bubble	*tmp;
	t_bubble	*tmp2;

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
		if (((int*)surface->pixels)[i] != -1 && ((unsigned int*)surface->pixels)[i] % 0x1000000 <= 0x888888)
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
		else if (((int*)surface->pixels)[i] != -1 && ((unsigned int*)surface->pixels)[i] % 0x1000000 <= 0x999999)
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
	if (!(data->lib.ptrfont[0] = TTF_OpenFont("./font/coalition/Coalition_v2.ttf", 200)))
		return (1);
	if (!(data->lib.ptrfont[1] = TTF_OpenFont("./font/xolonium/Xolonium-Regular.ttf", 200)))
		return (1);
	if (!(data->lib.ptrfont[2] = TTF_OpenFont("./font/8th_Cargo.ttf", 35)))
		return (1);
	if (!(data->lib.ptrfont[3] = TTF_OpenFont("./font/After_the_Goldrush.ttf", 200)))
		return (1);
	if (!(data->lib.ptrfont[4] = TTF_OpenFont("./font/8th_Cargo.ttf", 37)))
		return (1);
	if (!(data->lib.ptrfont[5] = TTF_OpenFont("./font/xolonium/Xolonium-Regular.ttf", 25)))
		return (1);
	/*if (!(data->lib.ptrfont[5] = TTF_OpenFont("./font/SciFi_Movies.ttf", 20)))
	  return (1);*/
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
	data->state |= RUNNING;
	data->state |= START;
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
	init_zbuf(&(data->zbuf));
	init_camera(data);
	pthread_mutex_init(&data->mutex, NULL);
}

static void	init_func_pointer(t_doom *data)
{
	data->check_intersect[0] = &check_x_intersect_pos;
	data->check_intersect[1] = &check_y_intersect_pos;
	data->check_intersect[2] = &check_z_intersect_pos;
	data->check_intersect[3] = &check_x_intersect_neg;
	data->check_intersect[4] = &check_y_intersect_neg;
	data->check_intersect[5] = &check_z_intersect_neg;
	data->add_texture[0] = &add_x_neg;
	data->add_texture[1] = &add_x_pos;
	data->add_texture[2] = &add_y_neg;
	data->add_texture[3] = &add_y_pos;
	data->add_texture[4] = &add_z_neg;
	data->add_texture[5] = &add_z_pos;
	data->check_light_view[0] = &check_light_view_x_neg;
	data->check_light_view[1] = &check_light_view_x_pos;
	data->check_light_view[2] = &check_light_view_y_neg;
	data->check_light_view[3] = &check_light_view_y_pos;
	data->check_light_view[4] = &check_light_view_z_neg;
	data->check_light_view[5] = &check_light_view_z_pos;
	data->normal[0] = vec3d(1, 0, 0);
	data->normal[1] = vec3d(-1, 0, 0);
	data->normal[2] = vec3d(0, 1, 0);
	data->normal[3] = vec3d(0, -1, 0);
	data->normal[4] = vec3d(0, 0, 1);
	data->normal[5] = vec3d(0, 0, -1);
}

#include <fcntl.h>
#include <unistd.h>

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
	fd = open("sampling2.binary", O_RDONLY);
	read(fd, sizec, 4);
	size = *((int*)sizec);
	data->samplingt[1] = malloc(sizeof(int) * (size * 2 + 1));
	data->samplingt[1][0] = size;
	read(fd, &data->samplingt[1][1], size * 8);
	close(fd);
	fd = open("sampling3.binary", O_RDONLY);
	read(fd, sizec, 4);
	size = *((int*)sizec);
	data->samplingt[2] = malloc(sizeof(int) * (size * 2 + 1));
	data->samplingt[2][0] = size;
	read(fd, &data->samplingt[2][1], size * 8);
	close(fd);
	fd = open("sampling4.binary", O_RDONLY);
	read(fd, sizec, 4);
	size = *((int*)sizec);
	data->samplingt[3] = malloc(sizeof(int) * (size * 2 + 1));
	data->samplingt[3][0] = size;
	read(fd, &data->samplingt[3][1], size * 8);
	close(fd);
	fd = open("sampling5.binary", O_RDONLY);
	read(fd, sizec, 4);
	size = *((int*)sizec);
	data->samplingt[4] = malloc(sizeof(int) * (size * 2 + 1));
	data->samplingt[4][0] = size;
	read(fd, &data->samplingt[4][1], size * 8);
	close(fd);
	fd = open("sampling6.binary", O_RDONLY);
	read(fd, sizec, 4);
	size = *((int*)sizec);
	data->samplingt[5] = malloc(sizeof(int) * (size * 2 + 1));
	data->samplingt[5][0] = size;
	read(fd, &data->samplingt[5][1], size * 8);
	close(fd);
	return (0);
}

int			init_program(t_doom *data)
{
	load_sampling(data);
	init_program2(data);
	init_func_pointer(data);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s"
				, SDL_GetError());
		return (1);
	}
	if (!(data->lib.window = SDL_CreateWindow("Doom Nukem"
					, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, /*0, 0,*/ WIDTH
					, HEIGHT, SDL_WINDOW_SHOWN)))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s"
				, SDL_GetError());
		return (1);
	}
	if (init_mixer(data))
		return (1);
	if (!(data->lib.renderer = SDL_CreateRenderer(data->lib.window, -1
					, SDL_RENDERER_PRESENTVSYNC)))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION
				, "Couldn't create renderer: %s", SDL_GetError());
		return (1);
	}
	SDL_SetRelativeMouseMode(SDL_TRUE);
	return (init_texture(data));
}
