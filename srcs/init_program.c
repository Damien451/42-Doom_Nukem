#include "graphic_lib.h"
#include "doom.h"
#include "inputs.h"
#include <time.h>

static void	init_tab(t_doom *data)
{
	int			i;
	SDL_Surface	*surface;
	t_bubble	*tmp;

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
	surface = SDL_LoadBMP("Untitled.bmp");
	data->lib.start_bg = SDL_LoadBMP("start_bg.bmp");
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
	parse_input_dict(data, "./files/tmp_dictionnary");
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
					, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH
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
