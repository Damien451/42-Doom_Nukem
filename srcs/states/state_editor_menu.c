/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_editor_menu.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 15:10:04 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/02 12:30:35 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include "menus.h"
#include "inputs.h"
#include "graphic_lib.h"

static void	check_inputs_menu2(t_doom *data, int nbmaps, int *first)
{
	if ((data->lib.event.key.keysym.sym == SDLK_LEFT ||
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
	else if (data->lib.event.key.keysym.sym == SDLK_ESCAPE)
		switch_state(data, EDITOR_MENU, MAIN_MENU);
}

/*
**	tab[0] -> nbuttons, tab[1] -> nbmaps
*/

static void	check_inputs_menu(t_doom *data, t_button *btab
	, int *first, int tab[2])
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
		{
			if (data->lib.event.key.keysym.sym == SDLK_UP ||
				(unsigned int)data->lib.event.key.keysym.sym ==
				data->tabinputs.keycode[0])
				data->button = data->button == 0 ?
					tab[0] - 1 : data->button - 1;
			else if (data->lib.event.key.keysym.sym == SDLK_DOWN ||
				(unsigned int)data->lib.event.key.keysym.sym ==
				data->tabinputs.keycode[2])
				data->button = (data->button == tab[0] - 1)
				? 0 : data->button + 1;
			else if (data->lib.event.key.keysym.sym == SDLK_RETURN &&
				!(tab[1] == 0 && data->button == 0))
			{
				*first = 0;
				switch_state(data, EDITOR_MENU, btab[data->button].state);
			}
			else
				check_inputs_menu2(data, tab[1], first);
		}
	}
}

static void	buttons_editor_menu(t_button buttons[4], char map_name[25])
{
	buttons[0] = button(point(WIDTH_CENTER - (DEF_BUTTON_W * 3 / 2),
		HEIGHT_CENTER - (DEF_BUTTON_H + BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 3, DEF_BUTTON_H), EDITOR, map_name);
	buttons[1] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), GET_MAP_NAME, "NEW MAP");
	buttons[2] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER + (DEF_BUTTON_H + BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), DELETE_MAP, "DELETE MAP");
	buttons[3] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER + (DEF_BUTTON_H * 2 + BUTTON_GAP_Y * 2)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), MAIN_MENU, "RETURN");
}

int			state_editor_menu(t_doom *data)
{
	t_button	buttons[4];
	static int	first = 0;
	static int	nbmaps = 0;
	static char	map_name[25];

	ft_memset(data->lib.image, 0, WIDTH * HEIGHT * 4);
	ft_memcpy(data->lib.image, data->lib.bg_menu[0],
		(WIDTH * HEIGHT) << 2);
	if (!first)
	{
		ft_bzero(map_name, 25);
		if ((nbmaps = count_maps(&first, "maps")) == -1)
			switch_state(data, EDITOR_MENU, MAIN_MENU);
		ft_strcpy(map_name, get_map_name(data->map_to_show, "maps"));
		data->map_name = map_name;
	}
	buttons_editor_menu(buttons, map_name);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	put_buttons_on_img(data, buttons, 4);
	display_arrows(data, &buttons[0]);
	put_string_with_shadow(data, point(WIDTH / 2, HEIGHT / 6),
		label("EDITOR", (SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[1]);
	put_buttons_names(data, buttons, (SDL_Color){255, 0, 0, 0}, 4);
	check_inputs_menu(data, buttons, &first, (int[2]){4, nbmaps});
	SDL_RenderPresent(data->lib.renderer);
	return (0);
}
