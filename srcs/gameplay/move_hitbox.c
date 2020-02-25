/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hitbox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:34:02 by dacuvill          #+#    #+#             */
/*   Updated: 2020/02/26 00:23:11 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "player.h"
#include "vec3.h"

static t_vec3d	get_diff_between_minmax(t_hitbox hitbox)
{
	t_vec3d		diff;

	diff.x = hitbox.max.x - hitbox.min.x;
	diff.y = hitbox.max.y - hitbox.min.y;
	diff.z = hitbox.max.z - hitbox.min.z;
	return (diff);
}

static double	maxd(double x, double y, double z)
{
	if (x > y && x > z)
		return (x);
	if (y > x && y > z)
		return (y);
	return (z);
}

void			move_hitbox(t_vec3d direction, t_hitbox hitbox,
	char map[64][64][64])
{
	double		x;
	double		y;
	double		z;
	double		max;
	t_vec3d		diff;

	max = maxd(direction.x, direction.y, direction.z);
	diff = get_diff_between_minmax(hitbox);
	x = 0;
	y = 0;
	z = 0;
	while (x < direction.x)
	{
		y = 0;
		while (y < direction.y)
		{
			z = 0;
			while (z < direction.z)
			{
				check_if_not_in_map((t_hitbox){(t_vec3d){x, y, z},
					(t_vec3d){x + diff.x, y + diff.y, z + diff.z}},
					map);
				z += direction.z / max;
			}
			y += direction.y / max;
		}
		x += direction.x / max;
	}
}
