
#include "doom.h"
#include "libft.h"
#include "menus.h"
#include "inputs.h"

#include <stdio.h>

static void	check_inputs_menu2(t_doom *data, int nbmaps)
{
	if ((data->lib.event.key.keysym.sym == SDLK_LEFT ||
		(unsigned int)data->lib.event.key.keysym.sym ==
		data->tabinputs.keycode[1]) && data->map_to_show > 0 &&
		data->button == 0)
		data->map_to_show--;
	else if ((data->lib.event.key.keysym.sym == SDLK_RIGHT ||
		(unsigned int)data->lib.event.key.keysym.sym ==
		data->tabinputs.keycode[3]) && data->map_to_show < nbmaps - 1 &&
		data->button == 0)
		data->map_to_show++;
}

/*
**	tab[0] -> nbuttons, tab[1] -> nbmaps
*/

static void	check_inputs_menu(t_doom *data, t_button *btab,
	int *first, int tab[2])
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
 		{
			if (data->lib.event.key.keysym.sym == SDLK_UP ||
				(unsigned int)data->lib.event.key.keysym.sym ==
				data->tabinputs.keycode[0])
				data->button = data->button == 0 ? tab[0] - 1 : data->button - 1;
			else if (data->lib.event.key.keysym.sym == SDLK_DOWN ||
				(unsigned int)data->lib.event.key.keysym.sym ==
				data->tabinputs.keycode[2])
				data->button = (data->button == tab[0] - 1)
				? 0 : data->button + 1;
			else if (data->lib.event.key.keysym.sym == SDLK_RETURN)
			{
				*first = 0;
				if (data->button == 0)
					data->map_name = get_map_name(data->map_to_show);
				switch_state(data, EDITOR_MENU, btab[data->button].state);
			}
			else
				check_inputs_menu2(data, tab[1]);
		}
	}
}

static void	state_editor_menu2(t_doom *data, t_button *btab,
	int *first, int nbmaps)
{
	int			tab[2];

	tab[0] = 3;
	tab[1] = nbmaps;
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	put_buttons_on_img(data, btab, 3);
	put_string_on_renderer(data, point(WIDTH / 2, HEIGHT / 13),
		label("EDITOR", RED), data->lib.ptrfont[1]);
	put_buttons_names(data, btab, BLACK, 3);
	check_inputs_menu(data, btab, first, tab);
	SDL_RenderPresent(data->lib.renderer);
}

int			state_editor_menu(t_doom *data)
{
	t_button	buttons[3];
	static int	first = 0;
	static int	nbmaps = 0;
	char		*map_name;

	ft_memset(data->lib.image, 0, WIDTH * HEIGHT * 4);
	ft_memcpy(data->lib.image, data->lib.menu_texture[4]->pixels,
		(WIDTH * HEIGHT) << 2);
	if (!first)
		nbmaps = count_maps(&first);
	map_name = get_map_name(data->map_to_show);
	printf("data->map_to_show = %d, data->map_name = %s\n", data->map_to_show, data->map_name);
	buttons[0] = button(point(WIDTH_CENTER - (DEF_BUTTON_W * 3 / 2),
		HEIGHT_CENTER - (DEF_BUTTON_H + BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 3, DEF_BUTTON_H), EDITOR, map_name);
	buttons[1] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), GET_MAP_NAME, "NEW MAP");
	buttons[2] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER + (DEF_BUTTON_H + BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), MAIN_MENU, "RETURN");
	state_editor_menu2(data, buttons, &first, nbmaps);
	return (0);
}
