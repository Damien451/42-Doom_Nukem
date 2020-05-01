/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_new_highscore.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 16:22:33 by dacuvill          #+#    #+#             */
/*   Updated: 2020/04/19 18:33:56 by damien           ###   ########.fr       */
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

static void		check_inputs_new_highscore2(t_doom *data, char *nametag,
	int *nbinputs, int *first)
{
	if (data->lib.event.key.keysym.sym == SDLK_ESCAPE)
	{
		*first = 0;
		*nbinputs = 0;
		switch_state(data, NEW_HIGHSCORE, PLAY_MENU);
		return ;
	}
	else if (check_if_authorised_input(data->lib.event.key.keysym.sym) == 0
		&& *nbinputs < LENGTH_NAMETAG)
	{
		(*nbinputs)++;
		ft_strcat(nametag, SDL_GetKeyName(data->lib.event.key.keysym.sym));
	}
}

static void		check_inputs_new_highscore(t_doom *data, char *nametag,
	int *nbinputs, int *first)
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
		{
			if (data->lib.event.key.keysym.sym == SDLK_RETURN &&
				*nbinputs > 0)
			{
				add_new_highscore(&data->scoreboard,
					&data->player, nametag);
				*first = 0;
				*nbinputs = 0;
				switch_state(data, NEW_HIGHSCORE, PLAY_MENU);
				return ;
			}
			else if (data->lib.event.key.keysym.sym == SDLK_BACKSPACE
				&& *nbinputs >= 0)
			{
				nametag[*nbinputs] = '\0';
				(*nbinputs)--;
			}
			check_inputs_new_highscore2(data, nametag, nbinputs, first);
		}
	}
}

int				state_new_highscore(t_doom *data)
{
	t_button	input_field;
	static int	nbinputs = 0;
	static char	nametag[LENGTH_NAMETAG];
	static int	first = 0;

	if (first == 0)
	{
		ft_bzero(nametag, LENGTH_NAMETAG);
		first = 1;
	}
	ft_memset(data->lib.image, 0, WIDTH * HEIGHT * 4);
	ft_memcpy(data->lib.image, data->lib.bg_menu[1],
		(WIDTH * HEIGHT) << 2);
	check_inputs_new_highscore(data, nametag, &nbinputs, &first);
	input_field = button(point(WIDTH_CENTER - (274 * 3 / 2), 540),
		point(274 * 3 / 2, DEF_BUTTON_H), NEW_HIGHSCORE,
		(nametag[0] == '\0' ? "Enter your nametag" : nametag));
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	put_buttons_on_img(data, &input_field, 1);
	put_string_with_shadow(data, point(WIDTH / 2, HEIGHT / 6),
		label("NEW HIGHSCORE", (SDL_Color){255, 0, 0, 0}),
		data->lib.ptrfont[1]);
	put_buttons_names(data, &input_field, (SDL_Color){255, 0, 0, 0}, 1);
	SDL_RenderPresent(data->lib.renderer);
	return (0);
}
