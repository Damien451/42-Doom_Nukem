/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select_next_level.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 19:00:53 by dacuvill          #+#    #+#             */
/*   Updated: 2020/01/29 20:21:11 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <time.h>

void	select_next_level(t_doom *data)
{
	static char	randmap[25];
	int			randnumber;

	ft_bzero(randmap, 25);
	randnumber = rand() % NBR_CLASSIC_MAPS;
	ft_strcpy(randmap, get_map_name(randnumber, "maps"));
	data->map_name = randmap;
	load_map(data, data->map_name);
	free_octree(data->octree);
	create_octree(data);
}
