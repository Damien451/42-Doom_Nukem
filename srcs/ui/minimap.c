/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:42:04 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/04 20:21:02 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "player.h"
#include "vec3.h"
#include "graphic_lib.h"
#include "menus.h"

static inline int			check_block(char block)
{
	if (block == 0)
		return (0);
	return (1);
}

static inline unsigned int	select_color(char map[64][64][64],
	t_graphic_lib *lib, t_player *player, double coords[3])
{
	if (coords[0] >= player->camera.origin.x - 0.3
		&& coords[0] <= player->camera.origin.x + 0.3
		&& coords[2] >= player->camera.origin.z - 0.3
		&& coords[2] <= player->camera.origin.z + 0.3)
		return (0x040fe5);
	if (check_block(map[(int)coords[0]][(int)coords[1]][(int)coords[2]]) == 0)
	{
		if (coords[1] > 0 && check_block(map[(int)coords[0]]
			[(int)coords[1] - 1][(int)coords[2]]) != 0)
			return (lib->map_colors[map[(int)coords[0]]
				[(int)coords[1] - 1][(int)coords[2]] - 1]);
		else if (coords[1] > 1 && check_block(map[(int)coords[0]]
			[(int)coords[1] - 2][(int)coords[2]]) != 0)
			return (lib->map_colors[map[(int)coords[0]]
				[(int)coords[1] - 2][(int)coords[2]] - 1]);
		else
			return (0xb30000);
	}
	return (lib->map_colors[map[(int)coords[0]]
		[(int)coords[1]][(int)coords[2]] - 1]);
}

static void					draw_minimap(char map[64][64][64], t_player *player,
	t_graphic_lib *lib, double coords[5])
{
	double		i;
	double		j;
	int			posx;
	int			posy;

	i = coords[0];
	posy = MINIMAP_HEIGHT_START;
	while ((i += 0.0727272) <= coords[1])
	{
		j = coords[2];
		posx = MINIMAP_WIDTH_START;
		while ((j += 0.0727272) <= coords[3])
		{
			lib->image[posy * WIDTH + posx] =
				select_color(map, lib, player, (double[3]){i, coords[4], j});
			posx++;
		}
		posy++;
	}
}

void						minimap(char map[64][64][64], t_player *player,
	t_graphic_lib *lib)
{
	double	start_i;
	double	start_j;
	double	end_i;
	double	end_j;
	double	step;

	step = player->camera.origin.y - 1.5;
	start_i = player->camera.origin.x - 8;
	end_i = player->camera.origin.x + 8;
	start_j = player->camera.origin.z - 8;
	end_j = player->camera.origin.z + 8;
	end_i += (start_i < 0 ? start_i * -1 : 0);
	if (start_i < 0)
		start_i = 0;
	end_j += (start_j < 0 ? start_j * -1 : 0);
	if (start_j < 0)
		start_j = 0;
	start_i -= (end_i > 64 ? end_i - 64 : 0);
	if (end_i > 64)
		end_i = 64;
	start_j -= (end_j > 64 ? end_j - 64 : 0);
	if (end_j > 64)
		end_j = 64;
	draw_minimap(map, player, lib, (double[5]){start_i, end_i, start_j
		, end_j, step});
}
