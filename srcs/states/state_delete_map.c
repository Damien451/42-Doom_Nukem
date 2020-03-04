/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_delete_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 15:08:27 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/02 12:29:26 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include "menus.h"
#include "inputs.h"
#include <stdio.h>

static void	check_inputs_delmap2(t_doom *data, int nbmaps, int *first)
{
	char	full_path[35];

	full_path[0] = '\0';
	if (data->lib.event.key.keysym.sym == SDLK_RETURN &&
		data->button == 1 && nbmaps > 0)
	{
		*first = 0;
		remove(ft_strcat(ft_strcat(full_path, "maps/"), data->map_name));
	}
	else if ((data->lib.event.key.keysym.sym == SDLK_LEFT ||
		(unsigned int)data->lib.event.key.keysym.sym ==
		data->tabinputs.keycode[1]) && data->map_to_show > 0 &&
		data->button == 1)
	{
		*first = 0;
		data->map_to_show--;
	}
	else if ((data->lib.event.key.keysym.sym == SDLK_RIGHT ||
		(unsigned int)data->lib.event.key.keysym.sym ==
		data->tabinputs.keycode[3]) && data->map_to_show < nbmaps - 1 &&
		data->button == 1)
	{
		*first = 0;
		data->map_to_show++;
	}
}

static void	check_inputs_delmap(t_doom *data, int nbmaps, int *first)
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
		{
			if (data->lib.event.key.keysym.sym == SDLK_UP ||
				(unsigned int)data->lib.event.key.keysym.sym ==
				data->tabinputs.keycode[0])
				data->button = data->button == 0 ? 1 : 0;
			else if (data->lib.event.key.keysym.sym == SDLK_DOWN ||
				(unsigned int)data->lib.event.key.keysym.sym ==
				data->tabinputs.keycode[2])
				data->button = (data->button == 1) ? 0 : 1;
			else if (data->lib.event.key.keysym.sym == SDLK_RETURN &&
				data->button == 0)
			{
				*first = 0;
				switch_state(data, DELETE_MAP, EDITOR_MENU);
			}
			else if (data->lib.event.key.keysym.sym == SDLK_ESCAPE)
				switch_state(data, DELETE_MAP, EDITOR_MENU);
			else
				check_inputs_delmap2(data, nbmaps, first);
		}
	}
}

void		buttons_delmap(t_button buttons[2], char map_name[25])
{
	buttons[0] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER - (DEF_BUTTON_H + BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), EDITOR_MENU, "CANCEL");
	buttons[1] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), 0, map_name);
}

void		put_delmap_strings(t_doom *data)
{
	put_string_with_shadow(data, point(WIDTH / 2, HEIGHT / 3),
		label("Be careful, the deletion is definitive !", (SDL_Color){255, 0, 0
		, 0}), data->lib.ptrfont[2]);
	put_string_with_shadow(data, point(WIDTH / 2, HEIGHT / 6),
		label("EDITOR", (SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[1]);
}

int			state_delete_map(t_doom *data)
{
	t_button	buttons[2];
	static int	first = 0;
	static char	map_name[25];
	static int	nbmaps = 0;

	if (!first)
	{
		nbmaps = count_maps(&first, "maps");
		ft_strcpy(map_name, get_map_name(data->map_to_show, "maps"));
	}
	ft_memset(data->lib.image, 0, WIDTH * HEIGHT * 4);
	ft_memcpy(data->lib.image, data->lib.bg_menu[0],
		(WIDTH * HEIGHT) << 2);
	buttons_delmap(buttons, map_name);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	put_buttons_on_img(data, buttons, 2);
	put_delmap_strings(data);
	put_buttons_names(data, buttons, (SDL_Color){255, 0, 0, 0}, 2);
	data->map_name = map_name;
	check_inputs_delmap(data, nbmaps, &first);
	SDL_RenderPresent(data->lib.renderer);
	return (0);
}
