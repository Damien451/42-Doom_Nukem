/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_arrows.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/19 16:50:40 by dacuvill          #+#    #+#             */
/*   Updated: 2020/02/24 20:49:43 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "menus.h"
#include <unistd.h>

static void	print_arrow(t_doom *data, SDL_Surface *texture, t_point pos, int frame)
{
	int			i;
	int			j;

	i = -1;
	while (++i < 64)
	{
		j = -1;
		while (++j < 64)
		{
			if (!(((unsigned int*)texture->pixels)
				[i * 64 + j] > 4278190080) && data->button != 0)
				data->lib.image[(i + pos.y) * WIDTH + j + frame + pos.x] =
					0xff0000;
			else if (!(((unsigned int*)texture->pixels)
				[i * 64 + j] > 4278190080) && data -> button == 0)
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

	print_arrow(data, data->lib.menu_texture[7],
		point(button->pos.x + (button->pos.x / 5 - 32),
		button->pos.y + button->dim.y / 2 - 32), frame / 4);
	print_arrow(data, data->lib.menu_texture[8],
		point(button->pos.x + (button->dim.x / 1.2),
		button->pos.y + button->dim.y / 2 - 32), frame2 / 4);
	if (ok == 0 && frame2 > -60)
	{
		++frame;
		--frame2;
	}
	else if (ok == 0 && frame2 == -60)
		ok = 1;
	else if (ok == 1 && frame2 < 60)
	{
		--frame;
		++frame2;
	}
	else if (ok == 1 && frame2 == 60)
		ok = 0;
}
