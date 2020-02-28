/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_sound_bars.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:44:59 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/28 17:20:53 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "menus.h"
#include "libft.h"

static void	put_sound_bars_strings(t_doom *data, int coordy, int nbsoundbar)
{
	char	string[35];

	ft_bzero(string, 35);
	if (nbsoundbar == 0)
		ft_strcat(string, "Master volume");
	else if (nbsoundbar == 1)
		ft_strcat(string, "Music volume");
	else if (nbsoundbar == 2)
		ft_strcat(string, "Sound effects volume");
	put_string_on_renderer(data, point(WIDTH_CENTER * 1.005,
		coordy - BUTTON_GAP_Y * 1.5),
		label(string, (SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[2]);
	put_string_on_renderer(data, point(WIDTH_CENTER,
		coordy - BUTTON_GAP_Y * 1.5),
		label(string, (SDL_Color){255, 255, 255, 0}), data->lib.ptrfont[2]);
}

static void	put_filled_bars(t_doom *data, int *tab)
{
	int		i;
	int		coordy;

	i = -1;
	while (++i < 3)
	{
		coordy = BAR_HEIGHT_START + 2 + i * BAR_GAP;
		draw_rectangle(&(data->lib), point(BAR_WIDTH_START + 2, coordy),
			point((int)((tab[i] / 100.0) * BAR_WIDTH - 4),
			BAR_HEIGHT - 4), 0xff0000);
	}
	i = -1;
	while (++i < 3)
	{
		coordy = BAR_HEIGHT_START + 2 + i * BAR_GAP;
		put_sound_bars_strings(data, coordy, i);
	}
}

void		put_sound_bars(t_doom *data, int *tab)
{
	int i;

	i = -1;
	while (++i < 3)
	{
		draw_rectangle(&(data->lib), point(BAR_WIDTH_START - 2
			, BAR_HEIGHT_START + i * BAR_GAP - 2),
			point(BAR_WIDTH + 4, BAR_HEIGHT + 4), 0xff0000);
		draw_rectangle(&(data->lib), point(BAR_WIDTH_START
			, BAR_HEIGHT_START + i * BAR_GAP),
			point(BAR_WIDTH, BAR_HEIGHT), 0xff0001);
	}
	put_filled_bars(data, tab);
}
