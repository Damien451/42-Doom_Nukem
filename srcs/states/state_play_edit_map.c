/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_play_edit_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 02:12:24 by dacuvill          #+#    #+#             */
/*   Updated: 2020/04/19 19:07:10 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include "menus.h"
#include <fcntl.h>
#include <unistd.h>

static void	check_inputs2(t_doom *data, int nbmaps, int *first)
{
	if (data->lib.event.key.keysym.sym == SDLK_RETURN)
	{
		if (load_map(data, data->map_name) == 0)
			switch_state(data, PLAY_EDIT_MAP, PLAYING);
	}
	else if ((data->lib.event.key.keysym.sym == SDLK_LEFT ||
		(unsigned int)data->lib.event.key.keysym.sym ==
		data->tabinputs.keycode[1]) && data->button == 0)
	{
		*first = 0;
		data->map_to_show = (data->map_to_show == 0
			? nbmaps - 1 : data->map_to_show - 1);
	}
	else if ((data->lib.event.key.keysym.sym == SDLK_RIGHT ||
		(unsigned int)data->lib.event.key.keysym.sym ==
		data->tabinputs.keycode[3]) && data->button == 0)
	{
		*first = 0;
		data->map_to_show = (data->map_to_show == nbmaps - 1
			? 0 : data->map_to_show + 1);
	}
}

/*
**	tab[0] -> nbuttons, tab[1] -> nbmaps
*/

static void	check_inputs(t_doom *data, t_button *btab, int *first,
	int tab[2])
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
		{
			if (data->lib.event.key.keysym.sym == SDLK_UP ||
				(unsigned int)data->lib.event.key.keysym.sym ==
				data->tabinputs.keycode[0])
				data->button = data->button ? data->button - 1 : tab[0] - 1;
			else if (data->lib.event.key.keysym.sym == SDLK_DOWN ||
				(unsigned int)data->lib.event.key.keysym.sym ==
				data->tabinputs.keycode[2])
				data->button = data->button == tab[0] - 1
					? 0 : data->button + 1;
			else if (data->lib.event.key.keysym.sym == SDLK_RETURN
				&& data->button == 1)
				switch_state(data, PLAY_EDIT_MAP, btab[data->button].state);
			else if (data->lib.event.key.keysym.sym == SDLK_ESCAPE)
				switch_state(data, PLAY_EDIT_MAP, PLAY_MENU);
			else
				check_inputs2(data, tab[1], first);
		}
	}
}

static void	buttons_play_edit_map(t_button buttons[2], char map_name[25])
{
	buttons[0] = button(point(WIDTH_CENTER - (274 * 3 / 2),
		HEIGHT_CENTER - (DEF_BUTTON_H + BUTTON_GAP_Y)),
		point(274 * 3, DEF_BUTTON_H), PLAYING, map_name);
	buttons[1] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER),
		point(274 * 2, DEF_BUTTON_H), PLAY_MENU, "RETURN");
}

int			state_play_edit_map(t_doom *data)
{
	t_button	buttons[2];
	static int	first = 0;
	static int	nbmaps = 0;
	static char	map_name[LENGTH_MAPNAME];

	ft_memset(data->lib.image, 0, WIDTH * HEIGHT * 4);
	ft_memcpy(data->lib.image, data->lib.bg_menu[0],
		(WIDTH * HEIGHT) << 2);
	if (!first)
	{
		ft_bzero(map_name, LENGTH_MAPNAME);
		nbmaps = count_maps(&first, "maps");
		ft_strcpy(map_name, get_map_name(data->map_to_show, "maps"));
		data->map_name = map_name;
	}
	buttons_play_edit_map(buttons, map_name);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	put_buttons_on_img(data, buttons, 2);
	display_arrows(data, &buttons[0]);
	put_string_on_renderer(data, point(WIDTH / 2, HEIGHT / 6),
		label("DOOMCRAFT", (SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[0]);
	put_buttons_names(data, buttons, (SDL_Color){255, 0, 0, 0}, 2);
	check_inputs(data, buttons, &first, (int[2]){2, nbmaps});
	SDL_RenderPresent(data->lib.renderer);
	return (0);
}
