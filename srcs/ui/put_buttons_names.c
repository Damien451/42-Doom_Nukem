/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_buttons_names.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:43:40 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/26 19:06:35 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "menus.h"

void		put_buttons_names(t_doom *data, t_button *btab, SDL_Color color
	, int nbuttons)
{
	while (nbuttons > 0)
	{
		put_string_on_renderer(data,
		point(btab[nbuttons - 1].pos.x + (btab[nbuttons - 1].dim.x / 2),
		btab[nbuttons - 1].pos.y + ((btab[nbuttons - 1].dim.y / 2))),
		label(btab[nbuttons - 1].title, nbuttons - 1 == data->button
			? (SDL_Color){255, 255, 255, 0} : color),
		data->lib.ptrfont[2]);
		--nbuttons;
	}
}
