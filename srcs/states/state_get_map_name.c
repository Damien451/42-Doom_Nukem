
#include "doom.h"
#include "libft.h"
#include "menus.h"
#include "inputs.h"

#include <stdio.h>

static void		check_inputs_map_name(t_doom *data, char *map_name, int *nbinputs)
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
 		{
			if (data->lib.event.key.keysym.sym == SDLK_RETURN)
			{
				(*nbinputs) = 50;
				return ;
			}
			else if (data->lib.event.key.keysym.sym == SDLK_BACKSPACE
				&& *nbinputs >= 0)
			{
				map_name[*nbinputs] = '\0';
				(*nbinputs)--;
			}
			else if (data->lib.event.key.keysym.sym >= 0 &&
				data->lib.event.key.keysym.sym < 127 &&
				data->lib.event.key.keysym.sym != SDLK_BACKSPACE &&
				*nbinputs < 24)
			{
				(*nbinputs)++;
				ft_strcat(map_name,
					SDL_GetKeyName(data->lib.event.key.keysym.sym));
			}
		}
	}
}

int				state_get_map_name(t_doom *data)
{
	t_button	input_field;
	static int	nbinputs = -1;
	static char	map_name[25] = "\0";

	ft_memset(data->lib.image, 0, WIDTH * HEIGHT * 4);
	ft_memcpy(data->lib.image, data->lib.menu_texture[4]->pixels,
		(WIDTH * HEIGHT) << 2);
	check_inputs_map_name(data, map_name, &nbinputs);
	input_field = button(point(WIDTH_CENTER - (DEF_BUTTON_W * 3 / 2),
		HEIGHT_CENTER),
		point(DEF_BUTTON_W * 3, DEF_BUTTON_H), EDITOR, 
		(map_name[0] == '\0' ? "Enter new map name" : map_name));
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	put_buttons_on_img(data, &input_field, 1);
	put_string_on_renderer(data, point(WIDTH / 2, HEIGHT / 13),
		label("EDITOR", RED), data->lib.ptrfont[1]);
	put_buttons_names(data, &input_field, BLACK, 1);
	SDL_RenderPresent(data->lib.renderer);
	if (nbinputs == 50)
	{
		data->map_name = map_name;
		switch_state(data, GET_MAP_NAME, EDITOR);
	}
	return (0);
}
