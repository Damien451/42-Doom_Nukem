#include "doom.h"

static void		add_textures_path(t_doom *data)
{
	data->lib.texture_path[0] = "./ressources/images/Untitled.bmp";
	data->lib.texture_path[1] = "ressources/images/start_bg.bmp";
}

int				load_textures(t_doom *data)
{
	int			i;

	i = -1;
	add_textures_path(data);
	while (++i < NB_IMG)
	{
		if (!(data->lib.surfaces[i] = SDL_LoadBMP(data->lib.texture_path[i])))
		{
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION
				, "Couldn't load texture: %s, %d", SDL_GetError(), i);
			return (1);
		}
	}
	return (0);
}