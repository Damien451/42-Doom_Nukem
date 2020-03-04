/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_next_level.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 19:00:53 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/03 15:42:14 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include <time.h>

int		randnumber_map(t_player *player)
{
	int		randn;

	randn = 0;
	if (player->levels_left == 3)
		return (rand() % NBR_CLASSIC_MAPS);
	else if (player->levels_left == 2)
		while (randn == player->firstlevel)
			randn = rand() % NBR_CLASSIC_MAPS;
	else if (player->levels_left == 1)
		while (randn == player->firstlevel
			|| randn == player->secondlevel)
			randn = rand() % NBR_CLASSIC_MAPS;
	return (randn);
}

void	select_next_level(t_doom *data)
{
	static char	randmap[LENGTH_MAPNAME];
	int			randn;

	ft_bzero(randmap, LENGTH_MAPNAME);
	randn = randnumber_map(&data->player);
	ft_strcpy(randmap, get_map_name(randn, "maps"));
	if (data->player.levels_left == 3)
		data->player.firstlevel = randn;
	else if (data->player.levels_left == 2)
		data->player.secondlevel = randn;
	data->map_name = randmap;
	data->lib.cam_keys = 0;
	load_map(data, data->map_name);
	free_octree(data->octree);
	create_octree(data);
	set_player_spawn(data->map_to_save, &data->player.camera.origin);
}
