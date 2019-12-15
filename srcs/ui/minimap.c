/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:42:04 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/15 16:42:57 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "player.h"
#include "graphic_lib.h"
#include "menus.h"

static inline int	select_color(char map[64][64][64], int coords[3],
	t_player *player)
{
	if (coords[0] == (int)player->camera.origin.x &&
		coords[2] == (int)player->camera.origin.z)
		return (0x006600);
	if (map[coords[0]][coords[1]][coords[2]] == 0)
	{
		if (coords[1] > 0 && map[coords[0]][coords[1] - 1][coords[2]] != 0)
			return (0x1aff1a);
		else if (coords[1] > 1 && map[coords[0]][coords[1] - 2][coords[2]] != 0)
			return (0x66ff66);
		return (0xb3ffb3);
	}
	return (0x00cc00);
}

static void			draw_minimap(char map[64][64][64], t_player *player,
	t_graphic_lib *lib, int coords[5])
{
	int		i;
	int		j;
	int		posx;
	int		posy;

	i = coords[0] - 1;
	posy = MINIMAP_HEIGHT_START;
	while (++i <= coords[1])
	{
		j = coords[2] - 1;
		posx = MINIMAP_WIDTH_START;
		while (++j <= coords[3])
		{
			draw_rectangle(lib, (t_point){posx, posy}, (t_point){12, 12},
				select_color(map, (int[3]){i, coords[4], j}, player));
			posx += 13;
		}
		posy += 13;
	}
}

void				minimap(char map[64][64][64], t_player *player,
	t_graphic_lib *lib)
{
	int		start_i;
	int		start_j;
	int		end_i;
	int		end_j;
	int		step;

	step = (int)(player->camera.origin.y - 1.5);
	start_i = (int)player->camera.origin.x - 8;
	end_i = (int)player->camera.origin.x + 8;
	start_j = (int)player->camera.origin.z - 8;
	end_j = (int)player->camera.origin.z + 8;
	end_i += (start_i < 0 ? start_i * -1 : 0);
	if (start_i < 0)
		start_i = 0;
	end_j += (start_j < 0 ? start_j * -1 : 0);
	if (start_j < 0)
		start_j = 0;
	start_i -= (end_i > 63 ? end_i - 63 : 0);
	if (end_i > 63)
		end_i = 63;
	start_j -= (end_j > 63 ? end_j - 63 : 0);
	if (end_j > 63)
		end_j = 63;
	draw_minimap(map, player, lib, (int[5]){start_i, end_i, start_j
		, end_j, step});
}
