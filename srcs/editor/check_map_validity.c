/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_validity.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 22:46:04 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/03 18:44:03 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "vec3.h"

static inline void	checks(char map_to_save[SIZE_MAP][SIZE_MAP][SIZE_MAP],
	t_vec3d *coords, int *start, int *finish)
{
	int			block;
	int			upblock;
	int			upblock2;

	block = (int)map_to_save[(int)coords->x][(int)coords->y]
		[(int)coords->z];
	upblock = (int)map_to_save[(int)coords->x][(int)coords->y + 1]
		[(int)coords->z];
	upblock2 = (int)map_to_save[(int)coords->x][(int)coords->y + 2]
		[(int)coords->z];
	if (block == ID_START_BLOCK + 1 && upblock == 0 && upblock2 == 0)
		(*start)++;
	else if (block == ID_FINISH_BLOCK + 1 && upblock == 0 && upblock2 == 0)
		(*finish)++;
	else if (block == 63 && upblock != 0)
		*finish += 2;
}

int					check_map_validity(t_doom *data)
{
	t_vec3d		coords;
	int			start;
	int			finish;
	int			enemies;

	coords.x = -1;
	start = 0;
	finish = 0;
	enemies = 0;
	while (++coords.x < SIZE_MAP)
	{
		coords.y = -1;
		while (++coords.y < SIZE_MAP - 2)
		{
			coords.z = -1;
			while (++coords.z < SIZE_MAP)
			{
				checks(data->map_to_save, &coords, &start, &finish);
				enemies = ((int)data->map_to_save[(int)coords.x][(int)coords.y]
					[(int)coords.z] == 63 ? enemies + 1 : enemies);
			}
		}
	}
	return (start == 1 && finish == 1 && enemies < 21 ? 0 : 1);
}
