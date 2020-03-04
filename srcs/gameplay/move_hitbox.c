/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_hitbox.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 21:34:02 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/03 21:42:54 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "player.h"
#include "vec3.h"
#include "gameplay.h"

int				move_hitbox(t_vec3d direction, t_hitbox hitbox,
	char map[64][64][64])
{
	hitbox.min.x += direction.x;
	hitbox.min.y += direction.y;
	hitbox.min.z += direction.z;
	hitbox.max.x += direction.x;
	hitbox.max.y += direction.y;
	hitbox.max.z += direction.z;
	if (check_if_not_in_map(hitbox, map))
		return (1);
	return (0);
}
