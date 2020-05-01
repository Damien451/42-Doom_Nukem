/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_player_spawn.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 19:32:19 by dacuvill          #+#    #+#             */
/*   Updated: 2020/02/26 00:20:10 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"

void		set_player_spawn(char map[64][64][64], t_vec3d *position)
{
	int		x;
	int		y;
	int		z;

	z = -1;
	while (++z < 64)
	{
		y = -1;
		while (++y < 64)
		{
			x = -1;
			while (++x < 64)
			{
				if (map[z][y][x] == ID_START_BLOCK + 1)
				{
					position->x = z + 0.5;
					position->y = y + 2.7;
					position->z = x + 0.5;
				}
			}
		}
	}
}
