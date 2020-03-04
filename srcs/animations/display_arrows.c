/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_arrows.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:50:40 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/02 12:14:15 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "menus.h"
#include <unistd.h>

static void	print_arrow(t_doom *data, const unsigned int arrow[64 * 64],
	t_point pos, int frame)
{
	int			i;
	int			j;

	i = -1;
	while (++i < 64)
	{
		j = -1;
		while (++j < 64)
		{
			if ((arrow[i * 64 + j] < 14588888) && data->button != 0)
				data->lib.image[(i + pos.y) * WIDTH + j + frame + pos.x] =
					0xff0000;
			else if ((arrow[i * 64 + j] < 14588888) && data->button == 0)
				data->lib.image[(i + pos.y) * WIDTH + j + frame + pos.x] =
					0xffffff;
		}
	}
}

void		display_arrows(t_doom *data, t_button *button)
{
	static int				frame = -60;
	static int				frame2 = 60;
	static int				ok = 0;

	print_arrow(data, data->lib.arrows_menu[0],
		point(button->pos.x + (button->pos.x / 5 - 32),
		button->pos.y + button->dim.y / 2 - 32), frame / 2);
	print_arrow(data, data->lib.arrows_menu[1],
		point(button->pos.x + (button->dim.x / 1.2),
		button->pos.y + button->dim.y / 2 - 32), frame2 / 2);
	if (ok == 0 && frame2 > -60)
	{
		frame += 2;
		frame2 -= 2;
	}
	else if (ok == 0 && frame2 == -60)
		ok = 1;
	else if (ok == 1 && frame2 < 60)
	{
		frame -= 2;
		frame2 += 2;
	}
	else if (ok == 1 && frame2 == 60)
		ok = 0;
}
