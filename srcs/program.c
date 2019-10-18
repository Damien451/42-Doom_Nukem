#include "doom.h"
#include "libft.h"

static int	game_state(t_doom *data)
{
	if (data->state & START)
		state_start(data);
	else if (data->state & MAIN_MENU)
		state_main_menu(data);
	else if (data->state & EDITOR)
		state_editor(data);
	else if (data->state & SCORES)
		state_scoreboard(data);
	else if (data->state & SETTINGS)
		state_settings_menu(data);
	else if (data->state & LEAVING)
		data->state &= ~RUNNING;
	else if (data->state & PLAYING)
		state_game(data);
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
			game_state(data);
			if ((pitch = frame_calculator()))
			{
				ft_putnbr(pitch);
				ft_putchar('\n');
			}
		}
	}
	return (0);
}
