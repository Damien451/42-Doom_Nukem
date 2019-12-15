#include "doom.h"
#include "libft.h"
#include "menus.h"

static void	check_inputs(t_doom *data)
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
		{
			switch_state(data, SCORES, MAIN_MENU);
		}
	}
}

int			state_scoreboard(t_doom *data)
{
	ft_memset(data->lib.image, 0, WIDTH * HEIGHT * 4);
	ft_memcpy(data->lib.image, data->lib.menu_texture[4]->pixels, (WIDTH * HEIGHT) << 2);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	//put_scores_on_renderer(data);
	put_string_on_renderer(data, point(WIDTH / 2, HEIGHT / 13), label("SCOREBOARD", (SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[1]);
	check_inputs(data);
	SDL_RenderPresent(data->lib.renderer);
	return (0);
}
