/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_rectangle.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 15:01:33 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/21 16:58:54 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <graphic_lib.h>
#include <menus.h>

static int	draw_stylish_rectangle(t_graphic_lib *lib, t_point pos,
	t_point dim)
{
	t_point	end;
	int		i;
	int		x;

	end = add_points(pos, dim);
	i = 0;
	while (pos.y + i < end.y)
	{
		x = 0;
		while (pos.x + x < end.x)
		{
			lib->image[(pos.y + i) * WIDTH + pos.x + x] = ((unsigned int*)lib->menu_texture[5]->pixels)[(WIDTH * (i + 200)) + x + 20];
			++x;
		}
		++i;
	}
	return (0);
}

int			draw_rectangle(t_graphic_lib *lib, t_point pos,
	t_point dim, int color)
{
	t_point	end;
	int		i;
	int		x;

	end = add_points(pos, dim);
	i = 0;
	x = 0;
	if (color == 0xff0001)
		return (draw_stylish_rectangle(lib, pos, dim));
	while (pos.y + i < end.y)
	{
		x = 0;
		while (pos.x + x < end.x)
		{
			lib->image[(pos.y + i) * WIDTH + pos.x + x] = color;
			++x;
		}
		++i;
	}
	return (0);
}
