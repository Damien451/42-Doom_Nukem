#include "doom.h"

static void	check_pause_inputs(t_doom *data)
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
		{
			if (data->lib.event.key.keysym.sym == SDLK_RETURN)
				switch_state(data, PAUSE, PLAYING);
			else if (data->lib.event.key.keysym.sym == SDLK_ESCAPE)
			{
				leave_game(data, &data->player);
				switch_state(data, PAUSE, MAIN_MENU);
			}
		}
	}
}

int			state_pause(t_doom *data)
{
	/*static int	ok = 1;

	if (ok == 1)
	{
		put_string_on_renderer(data, point(WIDTH / 2, HEIGHT / 13),
			label("PAUSE", (SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[1]);
		SDL_RenderPresent(data->lib.renderer);
		ok--;
	}*/
	check_pause_inputs(data);
	return (0);
}