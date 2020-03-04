/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:57:32 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/04 19:42:29 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "gameplay.h"

static void	init_enemy(t_enemy *enemy, int i, int j, int k)
{
	enemy->hitbox.min.x = (double)k;
	enemy->hitbox.min.y = (double)i;
	enemy->hitbox.min.z = (double)j;
	enemy->hitbox.max.x = (double)k + 1;
	enemy->hitbox.max.y = (double)i + 2;
	enemy->hitbox.max.z = (double)j + 1;
	enemy->way = NULL;
	enemy->state = ALIVE;
}

int         init_enemies(t_doom *data, t_enemies *enemies,
	char map[64][64][64])
{
	int		i;
	int		j;
	int		k;
	int		nbenemies;

	nbenemies = 0;
	k = -1;
	while (++k < SIZE_MAP)
	{
		i = -1;
		while (++i < SIZE_MAP)
		{
			j = -1;
			while (++j < SIZE_MAP)
			{
				if (map[k][i][j] == 63)
				{
					init_enemy(&enemies->enemy[nbenemies], i, j, k);
					++nbenemies;
					data->map_to_save[k][i][j] = 0;
				}
			}
		}
	}
	printf("INIT ENEMY\n");
	printf("ENEMY NUMBERS = %d\n", nbenemies);
	enemies->nb = nbenemies;
	return (nbenemies < 20 ? 0 : 1);
}