/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_get_map_name.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 00:02:44 by dacuvill          #+#    #+#             */
/*   Updated: 2020/04/19 18:17:01 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include "menus.h"
#include "inputs.h"
#include <stdio.h>

/*
**	between 97 and 122 -> all letters
**	between 0x30 and 0x39 -> all numbers
*/

static int		check_if_authorised_input(int input)
{
	if (input >= 97 && input <= 122)
		return (0);
	else if (input >= 0x30 && input <= 0x39)
		return (0);
	else if (input == SDLK_MINUS || input == SDLK_PERIOD ||
		input == SDLK_COMMA)
		return (0);
	return (1);
}

static void		check_inputs_map_name2(t_doom *data, char *map_name,
	int *nbinputs, int *first)
{
	if (data->lib.event.key.keysym.sym == SDLK_ESCAPE)
	{
		*nbinputs = 0;
		*first = 0;
		switch_state(data, GET_MAP_NAME, EDITOR_MENU);
		return ;
	}
	else if (check_if_authorised_input(data->lib.event.key.keysym.sym) == 0
		&& *nbinputs < 24)
	{
		(*nbinputs)++;
		ft_strcat(map_name, SDL_GetKeyName(data->lib.event.key.keysym.sym));
	}
}

static void		check_inputs_map_name(t_doom *data, char *map_name,
	int *nbinputs, int *first)
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
		{
			if (data->lib.event.key.keysym.sym == SDLK_RETURN &&
				*nbinputs > 0)
			{
				*first = 0;
				*nbinputs = 0;
				switch_state(data, GET_MAP_NAME, EDITOR);
				return ;
			}
			else if (data->lib.event.key.keysym.sym == SDLK_BACKSPACE
				&& *nbinputs >= 0)
			{
				map_name[*nbinputs] = '\0';
				(*nbinputs)--;
			}
			check_inputs_map_name2(data, map_name, nbinputs, first);
		}
	}
}

int				state_get_map_name(t_doom *data)
{
	t_button	input_field;
	static int	nbinputs = 0;
	static char	map_name[LENGTH_MAPNAME];
	static int	first = 0;

	if (first == 0)
	{
		ft_bzero(map_name, LENGTH_MAPNAME);
		first = 1;
	}
	ft_memset(data->lib.image, 0, WIDTH * HEIGHT * 4);
	ft_memcpy(data->lib.image, data->lib.bg_menu[0],
		(WIDTH * HEIGHT) << 2);
	check_inputs_map_name(data, map_name, &nbinputs, &first);
	input_field = button(point(960 - (274 * 3 / 2), 540),
		point(274 * 3, 90), EDITOR,
		(map_name[0] == '\0' ? "Enter new map name" : map_name));
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	put_buttons_on_img(data, &input_field, 1);
	put_string_with_shadow(data, point(WIDTH / 2, HEIGHT / 6),
		label("EDITOR", (SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[1]);
	put_buttons_names(data, &input_field, (SDL_Color){255, 0, 0, 0}, 1);
	SDL_RenderPresent(data->lib.renderer);
	data->map_name = map_name;
	return (0);
}
