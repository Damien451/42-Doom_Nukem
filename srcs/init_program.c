#include "graphic_lib.h"
#include "doom.h"
#include "inputs.h"
#include "player.h"
#include <time.h>
#include <SDL_image.h>
#include <SDL.h>

void		init_camera(t_doom *data)
{
	data->player.camera.direction = Z_AXIS;
	data->player.sensitivity = SENSITIVITY;
	data->player.camera.right = X_AXIS;
	data->player.camera.up = Y_AXIS;
	data->player.camera.origin.x = 32;
	data->player.camera.origin.y = 32;
	data->player.camera.origin.z = 32;
	data->sampling = 4;
}

static void	ROBIN_init_texture(t_doom *data)
{
	int			i;

	data->lib.character = IMG_Load("textures/character.bmp");
	data->lib.menu_texture[0] = IMG_Load("textures/gstvine1.bmp");
	data->lib.menu_texture[1] = IMG_Load("textures/gstvine2.bmp");
	data->lib.menu_texture[2] = IMG_Load("enemy_menu.bmp");
	data->lib.menu_texture[3] = IMG_Load("energy_orb.bmp");
	data->lib.editor_texture = IMG_Load("textures/editor.bmp");
	data->lib.hud_texture = IMG_Load("textures/hud.bmp");
	data->lib.skybox[0] = IMG_Load("textures/hell_rt.tga");
	data->lib.skybox[1] = IMG_Load("textures/hell_ft.tga");
	data->lib.skybox[2] = IMG_Load("textures/hell_lf.tga");
	data->lib.skybox[3] = IMG_Load("textures/hell_bk.tga");
	data->lib.skybox[4] = IMG_Load("textures/hell_up.tga");
	data->lib.skybox[5] = IMG_Load("textures/hell_dn.tga");
	i = 0;
	while (i < 6)
	{
		data->lib.skybox_t[i] = SDL_CreateTextureFromSurface(data->lib.renderer, data->lib.skybox[i]);
		i++;
	}
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
	ROBIN_init_texture(data);
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
	if (!(data->lib.ptrfont[4] = TTF_OpenFont("./font/DEPLETED_URANIUM.ttf", 200)))
		return (1);
	if (!(data->lib.ptrfont[5] = TTF_OpenFont("./font/SciFi_Movies.ttf", 200)))
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
	data->state |= RUNNING;
	data->state |= START;
	data->button = 0;
	data->load_page[0] = 0;
	data->load_page[1] = 0;
	data->sensitivity = 100;
	data->player.speed = 0;
	parse_input_file(data, "./files/inputs");
	data->lib.cam_keys = 0;
	init_camera(data);
}

int			init_program(t_doom *data)
{
	init_program2(data);
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s"
				, SDL_GetError());
		return (1);
	}
	if (!(data->lib.window = SDL_CreateWindow("Doom Nukem"
					, /*SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED*/ 0, 0, WIDTH
					, HEIGHT, SDL_WINDOW_SHOWN)))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s"
				, SDL_GetError());
		return (1);
	}
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
