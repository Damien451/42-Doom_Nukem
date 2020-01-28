/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 22:03:07 by dacuvill          #+#    #+#             */
/*   Updated: 2020/01/27 20:03:49 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "player.h"

static void	set_player_spawn(char map[64][64][64], t_vec3d *position)
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
				if (map[z][y][x] == SPAWNBLOCK)
				{
					position->x = z + 0.5;
					position->y = y + 2.7;
					position->z = x + 0.5;
				}
			}
		}
	}
}

void	init_game(t_doom *data, t_player *player)
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
	set_player_spawn(data->map_to_save, &data->player.camera.origin);
	player->score = 0;
	if (player->gamemode == CLASSIC_MODE)
		player->lifes = 3;
	else
		player->lifes = -1;
}
