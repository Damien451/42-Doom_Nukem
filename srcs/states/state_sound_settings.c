#include "doom.h"
#include "libft.h"
#include "menus.h"
#include "inputs.h"
#include <fcntl.h>
#include <unistd.h>

static void mouse_sound_commands(t_doom *data, int **tab)
{
	if (data->lib.event.button.y >= BAR_HEIGHT_START && data->lib.event.button.x>= BAR_WIDTH_START
		&& data->lib.event.button.y <= BAR_HEIGHT_START + BAR_HEIGHT  && data->lib.event.button.x<= BAR_WIDTH_START + BAR_WIDTH)
	{
		(*tab)[0] = (int)((data->lib.event.button.x - BAR_WIDTH_START) * 100.0 / BAR_WIDTH + 0.5);
		set_master_volume(data->mix, data->lib.event.button.x - (double)BAR_WIDTH_START / (double)BAR_WIDTH);
	}
	else if (data->lib.event.button.y >= BAR_HEIGHT_START + BAR_GAP && data->lib.event.button.x>= BAR_WIDTH_START
		&& data->lib.event.button.y <= BAR_HEIGHT_START +  BAR_HEIGHT + BAR_GAP && data->lib.event.button.x<= BAR_WIDTH_START + BAR_WIDTH)
	{
		(*tab)[1] = (int)((data->lib.event.button.x - BAR_WIDTH_START) * 100.0 / BAR_WIDTH + 0.5);
		set_music_volume(data->mix, data->lib.event.button.x - (double)BAR_WIDTH_START / (double)BAR_WIDTH);
	}
	else if (data->lib.event.button.y >= BAR_HEIGHT_START + 2 * BAR_GAP && data->lib.event.button.x>= BAR_WIDTH_START
		&& data->lib.event.button.y <= BAR_HEIGHT_START + BAR_HEIGHT + 2 * BAR_GAP && data->lib.event.button.x<= BAR_WIDTH_START + BAR_WIDTH)
	{
		(*tab)[2] = (int)((data->lib.event.button.x - BAR_WIDTH_START) * 100.0 / BAR_WIDTH + 0.5);
		set_sound_effects_volume(data->mix, data->lib.event.button.x - (double)BAR_WIDTH_START / (double)BAR_WIDTH);
	}
}

static int	check_sound_settings(t_doom *data, int *tab[3])
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
 		{
			if (data->lib.event.key.keysym.sym == SDLK_RETURN)
				switch_state(data, SETTINGS_SOUND, SETTINGS);
		}
		if (data->lib.event.type == SDL_MOUSEBUTTONDOWN)
			mouse_sound_commands(data, tab);
	}
	return (0);
}

int			state_sound_settings(t_doom *data)
{
	static int first = 1;
	static int *tab;

	if (first)
	{
		tab = malloc( 3 * sizeof(int));
		tab[0] = 80;
		tab[1] = 80;
		tab[2] = 80;
		first = 0;
	}
	ft_memset(data->lib.image, 0, WIDTH * HEIGHT * 4);
	ft_memcpy(data->lib.image, data->lib.menu_texture[4]->pixels, (WIDTH * HEIGHT) << 2);
	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_ShowCursor(SDL_TRUE);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	if (check_sound_settings(data, &tab) != 0)
		return (1);
	put_sound_bars(data);
	put_filled_bars(data, tab);
	SDL_RenderPresent(data->lib.renderer);
	return (0);
}
