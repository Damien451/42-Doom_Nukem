#include "doom.h"
#include "libft.h"
#include "menus.h"

static void	check_inputs(t_doom *data)
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
		{
			if (data->lib.event.key.keysym.sym == SDLK_RETURN)
				switch_state(data, SCORES, MAIN_MENU);
		}
	}
}

/*static int	put_scores_on_renderer(t_doom *data)
{
	int			fd;
	int			i;

	i = -1;
	if ((fd = open("./files/scores")) == -1)
		return (1);
	while (++i < 10)
	{
		
	}
	return (0);
}*/

int			state_scoreboard(t_doom *data)
{
	t_button	buttons[1];

	buttons[0] = button(point(WIDTH_CENTER - (DEF_BUTTON_W / 2), HEIGHT - (DEF_BUTTON_H + BUTTON_GAP_Y)),
		point(DEF_BUTTON_W, DEF_BUTTON_H), 0, "Return");
	ft_memset(data->lib.image, 0, WIDTH * HEIGHT * 4);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	put_buttons_on_img(data, buttons, 1);
	//put_scores_on_renderer(data);
	put_string_on_renderer(data, point(WIDTH / 2, HEIGHT / 13), label("SCOREBOARD", RED), data->lib.ptrfont[1]);
	put_buttons_names(data, buttons, BLACK, 1);
	check_inputs(data);
	SDL_RenderPresent(data->lib.renderer);
	return (0);
}
