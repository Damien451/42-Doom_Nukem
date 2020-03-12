/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_item.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/11 17:13:08 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/11 21:41:23 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "player.h"
#include "gameplay.h"
#include <time.h>

static inline void	remove_item_from_map(t_doom *data, char *map[64][64][64],
	t_vec3d posbloc)
{
	*map[(int)posbloc.x][(int)posbloc.y][(int)posbloc.z] = 0;
	free_octree(data->octree);
	create_octree(data);
}

static void			get_item4(t_doom *data, t_player *player,
	char *map[64][64][64], t_vec3d posbloc)
{
	char	bloc;

	bloc = *map[(int)posbloc.x][(int)posbloc.y][(int)posbloc.z];
	if (bloc == 59)
	{
		remove_item_from_map(data, map, posbloc);
		player->score = (player->score + 50 > 2000000000
			? 2000000000 : player->score + 50);
	}
	else if (bloc == 60)
	{
		remove_item_from_map(data, map, posbloc);
		player->score = (player->score + 75 > 2000000000
			? 2000000000 : player->score + 75);
	}
	else if (bloc == 62)
	{
		remove_item_from_map(data, map, posbloc);
		player->score = (player->score + 2000 > 2000000000
			? 2000000000 : player->score + 2000);
	}
}

static void			get_item3(t_doom *data, t_player *player,
	char *map[64][64][64], t_vec3d posbloc)
{
	char	bloc;

	bloc = *map[(int)posbloc.x][(int)posbloc.y][(int)posbloc.z];
	if (bloc == 50)
	{
		remove_item_from_map(data, map, posbloc);
		player->score = (player->score + 4500 > 2000000000
			? 2000000000 : player->score + 4500);
	}
	else if (bloc == 55)
	{
		remove_item_from_map(data,map, posbloc);
		return ;//add item heal
	}
	else if (bloc == 56)
	{
		remove_item_from_map(data, map, posbloc);
		player->score = (player->score + 2500 > 2000000000
			? 2000000000 : player->score + 2500);
	}
	get_item4(data, player, map, posbloc);	
}

static void			get_item2(t_doom *data, t_player *player,
	char *map[64][64][64], t_vec3d posbloc)
{
	int		randn;
	int		scorebonus;
	int		ammobonus;
	char	bloc;

	randn = rand() % 3;
	scorebonus = 0;
	ammobonus = 0;
	bloc = *map[(int)posbloc.x][(int)posbloc.y][(int)posbloc.z];
	if (bloc == 51 || bloc == 54)
	{
		scorebonus = (bloc == 51 ? 75 : 1000);
		ammobonus = (bloc == 51 ? 8 : 16);
		remove_item_from_map(data, map, posbloc);
		if (randn == 0)
			player->score = (player->score + scorebonus > 2000000000
			? 2000000000 : player->score + scorebonus);
		else if (randn == 1)
			player->inventory.ammo_stock = (player->inventory.ammo_stock
				+ ammobonus > 99 ? 99
				: player->inventory.ammo_stock + ammobonus);
		else
			return ;//add item heal
	}
	get_item3(data, player, map, posbloc);	
}

void				get_item(t_doom *data, t_player *player,
	char *map[64][64][64], t_vec3d posbloc)
{
	char	bloc;

	bloc = *map[(int)posbloc.x][(int)posbloc.y][(int)posbloc.z];
	if (bloc == 45)
	{
		remove_item_from_map(data, map, posbloc);
		player->inventory.ammo_stock = (player->inventory.ammo_stock + 16 > 99
			? 99 : player->inventory.ammo_stock + 16);
	}
	else if (bloc == 47)
	{
		remove_item_from_map(data, map, posbloc);
		player->score = (player->score + 5000 > 2000000000
			? 2000000000 : player->score + 5000); 
	}
	else if (bloc == 49)
	{
		remove_item_from_map(data, map, posbloc);
		player->score = (player->score + 4000 > 2000000000
			? 2000000000 : player->score + 4000); 
	}
	get_item2(data, player, map, posbloc);
}
