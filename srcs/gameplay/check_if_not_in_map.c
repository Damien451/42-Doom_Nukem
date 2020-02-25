/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_if_not_in_map.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 20:49:59 by dacuvill          #+#    #+#             */
/*   Updated: 2020/02/25 22:04:41 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "player.h"

int		check_if_not_in_map(t_hitbox hitbox, char map[64][64][64])
{
	int		x;
	int		y;
	int		z;

	x = (int)hitbox.min.x - 1;
	while (++x <= (int)hitbox.max.x)
	{
		y = (int)hitbox.min.y - 1;
		while (++y <= (int)hitbox.max.y)
		{
			z = (int)hitbox.min.z - 1;
			while (++z <= (int)hitbox.max.z)
			{
				if (z > 64 || y > 64 || x > 64 || map[x][y][z])
					return (1);
			}
		}
	}
	return (0);
}
