/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_buttons_on_img.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:43:56 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/21 17:00:57 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "menus.h"

int		put_buttons_on_img(t_doom *data, t_button *btab, int nbuttons)
{
	while (nbuttons > 0)
	{
		draw_rectangle(&data->lib, btab[nbuttons - 1].pos,
			btab[nbuttons - 1].dim, 0xff0001);
		if (!(btab[nbuttons - 1].state == -1))
			draw_rectangle(&data->lib,
				point(btab[nbuttons - 1].pos.x + 5,
				btab[nbuttons - 1].pos.y + 5),
				point(btab[nbuttons - 1].dim.x - 10,
				btab[nbuttons - 1].dim.y - 10),
				(nbuttons - 1 == data->button ? 0xffffff : 0xff0000));
		else
			draw_rectangle(&data->lib,
				point(btab[nbuttons - 1].pos.x + 5, btab[nbuttons - 1].pos.y
				+ 5), point(btab[nbuttons - 1].dim.x - 10,
				btab[nbuttons - 1].dim.y - 10),
				(nbuttons - 1 == data->button ? 0xe6e600 : 0xff0000));
		draw_rectangle(&data->lib,
			point(btab[nbuttons - 1].pos.x + 10,
			btab[nbuttons - 1].pos.y + 10),
			point(btab[nbuttons - 1].dim.x - 20,
			btab[nbuttons - 1].dim.y - 20), 0xff0001);
		--nbuttons;
	}
	return (0);
}
