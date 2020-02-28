/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_buttons_inputs.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:41:28 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/27 18:02:19 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "menus.h"
#include "libft.h"
#include "inputs.h"

static void	init_desc(t_doom *data,
	char titles[NB_MODIF_INPUTS][40], int *first)
{
	int			i;

	i = -1;
	while (++i < NB_MODIF_INPUTS)
		ft_bzero(titles[i], 40);
	ft_strcpy(titles[0], "Move forward - ");
	ft_strcpy(titles[1], "Move left - ");
	ft_strcpy(titles[2], "Move backward - ");
	ft_strcpy(titles[3], "Move right - ");
	ft_strcpy(titles[4], "Pick obj - ");
	ft_strcpy(titles[5], "Reload - ");
	ft_strcpy(titles[6], "Sprint - ");
	ft_strcpy(titles[7], "Zoom - ");
	ft_strcpy(titles[8], "Couch - ");
	ft_strcpy(titles[9], "Jump - ");
	ft_strcpy(titles[10], "Inventory - ");
	ft_strcpy(titles[11], "Screenshot - ");
	i = -1;
	while (++i < NB_MODIF_INPUTS)
		ft_strcat(titles[i], SDL_GetKeyName(data->tabinputs.keycode[i]));
	*first = 1;
}

static void	create_buttons_inputs2(t_doom *data, t_button *btab,
	int coords[NB_MODIF_INPUTS + 2][2], int *first)
{
	int			i;
	static char	titles[NB_MODIF_INPUTS][40];

	i = -1;
	if (*first == 0)
		init_desc(data, titles, first);
	while (++i < NB_MODIF_INPUTS + 2)
	{
		if (i != 8 && i != 13)
			btab[i] = button(point(coords[i][0], coords[i][1]),
				point(SET_BUTTON_W, SET_BUTTON_H), 0,
				titles[(i > 8 ? i - 1 : i)]);
		else if (i == 8)
			btab[8] = button(point(coords[i][0], coords[i][1]),
			point(SET_BUTTON_W, SET_BUTTON_H), 0, "Save and quit");
		else
			btab[13] = button(point(coords[i][0], coords[i][1]),
			point(SET_BUTTON_W, SET_BUTTON_H), 0, "Reset");
	}
}

void		create_buttons_inputs(t_doom *data, t_button *btab, int *first)
{
	int			posy[5];
	int			coords[NB_MODIF_INPUTS + 2][2];
	int			i;
	int			j;

	i = -1;
	j = 0;
	posy[0] = HEIGHT_CENTER - (BUTTON_GAP_Y + (SET_BUTTON_H << 1));
	while (++j < 5)
		posy[j] = posy[j - 1] + SET_BUTTON_H + BUTTON_GAP_Y;
	while (++i < NB_MODIF_INPUTS + 2)
	{
		if (i < 4)
			coords[i][0] = WIDTH_CENTER - (SET_BUTTON_W +
				(SET_BUTTON_W >> 1) + BUTTON_GAP_X);
		else if (i < 9)
			coords[i][0] = WIDTH_CENTER - (SET_BUTTON_W >> 1);
		else
			coords[i][0] = coords[8][0] + BUTTON_GAP_X + SET_BUTTON_W;
		coords[i][1] = (i < 4 ? posy[i] : posy[(i + 1) % 5]);
	}
	create_buttons_inputs2(data, btab, coords, first);
}
