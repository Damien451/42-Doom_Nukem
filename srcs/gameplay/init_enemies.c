/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:57:32 by dacuvill          #+#    #+#             */
/*   Updated: 2020/04/18 17:03:00 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "gameplay.h"

static void	init_enemy(t_enemies *enemies, int *nbenemies, t_vec3d c)
{
	enemies->enemy[*nbenemies].hitbox = hitbox(vec3d(c.x, c.y, c.z),
		vec3d(c.x + 1, c.y + 2, c.z + 1));
	enemies->enemy[*nbenemies].way = NULL;
	enemies->enemy[*nbenemies].state = ALIVE;
	*nbenemies += 1;
}

int		init_enemies(t_doom *data, t_enemies *enemies,
	char map[64][64][64])
{
	int	i;
	int	j;
	int	k;
	int	nbenemies;

	nbenemies = 0;
	i = -1;
	while (++i < SIZE_MAP)
	{
		j = -1;
		while (++j < SIZE_MAP)
		{
			k = -1;
			while (++k < SIZE_MAP)
			{
				if (map[i][j][k] == 63)
				{
					init_enemy(enemies, &nbenemies, vec3d(i, j, k));
					data->map_to_save[i][j][k] = 0;
				}
			}
		}
	}
	enemies->nb = nbenemies;
	return (nbenemies < 20 ? 0 : 1);
}
