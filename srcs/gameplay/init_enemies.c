/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_enemies.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 12:57:32 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/05 18:06:30 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "gameplay.h"

static void	init_enemy(t_enemy *enemy, int i, int j, int k)
{
	enemy->hitbox = hitbox(vec3d(i, j, k), vec3d(i + 1, j + 2, k + 1));
	enemy->way = NULL;
	enemy->state = ALIVE;
	printf("enemy->hitbox.min.x = %f, enemy->hitbox.min.y = %f, enemy->hitbox.min.z = %f\n",
		enemy->hitbox.min.x, enemy->hitbox.min.y, enemy->hitbox.min.z);
}

int         init_enemies(t_doom *data, t_enemies *enemies,
	char map[64][64][64])
{
	int		i;
	int		j;
	int		k;
	int		nbenemies;

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