#include "doom.h"
#include "libft.h"
#include "menus.h"
#include "inputs.h"
#include <fcntl.h>
#include <unistd.h>


static int	check_sound_settings(t_doom *data)
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
 		{
			if (data->lib.event.key.keysym.sym == SDLK_RETURN)
				switch_state(data, SETTINGS_SOUND, SETTINGS);
		}
	}
	return (0);
}

int			state_sound_settings(t_doom *data)
{
	t_button	buttons[3];

	ft_memset(data->lib.image, 0, WIDTH * HEIGHT * 4);
	ft_memcpy(data->lib.image, data->lib.menu_texture[4]->pixels, (WIDTH * HEIGHT) << 2);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	put_sound_bars(data);
	if (check_sound_settings(data) != 0)
		return (1);
	SDL_RenderPresent(data->lib.renderer);
	return (0);
}
