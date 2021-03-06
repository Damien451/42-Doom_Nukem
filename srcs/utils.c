/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 16:37:41 by dacuvill          #+#    #+#             */
/*   Updated: 2020/02/26 15:20:47 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "menus.h"
#include "graphic_lib.h"

t_label		label(char *str, SDL_Color color)
{
	t_label		newlabel;

	newlabel.str = str;
	newlabel.color = color;
	return (newlabel);
}

t_button	button(t_point pos, t_point dim, long state, char *title)
{
	t_button	newbutton;

	newbutton.pos = pos;
	newbutton.dim = dim;
	newbutton.state = state;
	newbutton.title = title;
	return (newbutton);
}

t_point		point(int width, int height)
{
	t_point		newpoint;

	newpoint.x = width;
	newpoint.y = height;
	return (newpoint);
}

void		switch_button(t_doom *data, long actual_button, long new_button)
{
	data->button &= ~actual_button;
	data->button |= new_button;
}
