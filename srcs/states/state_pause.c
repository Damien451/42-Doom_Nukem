#include "doom.h"

static void	check_pause_inputs(t_doom *data, int *ok)
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
		{
			if (data->lib.event.key.keysym.sym == SDLK_ESCAPE)
			{
				*ok = 1;
				switch_state(data, PAUSE, PLAYING);
			}
			else if (data->lib.event.key.keysym.sym == SDLK_q)
			{
				*ok = 1;
				leave_game(data, &data->player);
				switch_state(data, PAUSE, MAIN_MENU);
			}
		}
	}
}

int			state_pause(t_doom *data)
{
	static int	ok = 1;

	if (ok == 1)
	{
		SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
		put_string_with_shadow(data, point(WIDTH / 2, HEIGHT / 8),
			label("PAUSE", (SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[1]);
		put_string_with_shadow(data, point(WIDTH / 2, HEIGHT / 3),
			label("Press Escape to continue or Q to quit the game.",
			(SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[2]);
		SDL_RenderPresent(data->lib.renderer);
		SDL_RenderClear(data->lib.renderer);
		ok--;
	}
	check_pause_inputs(data, &ok);
	return (0);
}
