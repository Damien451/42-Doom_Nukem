#include "doom.h"
#include "libft.h"

static int	game_state(t_doom *data)
{
	if (data->state & START)
		game_start(data);
	else if (data->state & MAIN_MENU)
		game_main_menu(data);
	else if (data->state & SETTINGS)
		settings_menu(data);
	else if (data->state & LEAVING)
		data->state &= ~RUNNING;
	return (0);
}

int			program(t_doom *data)
{
	int				pitch;

	while (data->state & RUNNING)
	{
		if (!SDL_LockTexture(data->lib.texture, NULL, (void**)&data->lib.image
				, &pitch))
		{
			SDL_UnlockTexture(data->lib.texture);
			while (SDL_PollEvent(&data->lib.event))
			{
				if (data->lib.event.type == SDL_KEYDOWN)
					if (data->lib.event.key.keysym.sym == SDLK_ESCAPE)
						data->state &= ~RUNNING;
				game_state(data);
			}
			SDL_RenderPresent(data->lib.renderer);
			if ((pitch = frame_calculator()))
			{
				ft_putnbr(pitch);
				ft_putchar('\n');
			}
		}
	}
	return (0);
}
