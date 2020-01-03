/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:42:04 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/03 21:37:45 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "player.h"
#include "vec3.h"
#include "graphic_lib.h"
#include "menus.h"

/*static inline void	draw_player_pos(t_graphic_lib *lib, t_player *player)
{
	bresenham(lib->image, (t_vec3l){MINIMAP_WIDTH_START +
		player->camera.origin.x, MINIMAP_HEIGHT_START +
		player->camera.origin.z, 3}, 0xff0000);
}*/

static inline int	select_color(char map[64][64][64], t_graphic_lib *lib,
	int coords[3], double pos[2])
{
	if (map[coords[0]][coords[1]][coords[2]] == 0)
	{
		if (coords[1] > 0 && map[coords[0]][coords[1] - 1][coords[2]] != 0)
			return (lib->textures_block[(int)map[coords[0]][coords[1] - 1][coords[2]] - 1][(int)(pos[1] * 128 + pos[0])]);
		else if (coords[1] > 1 && map[coords[0]][coords[1] - 2][coords[2]] != 0)
			return (lib->textures_block[(int)map[coords[0]][coords[1] - 2][coords[2]] - 1][(int)(pos[1] * 128 + pos[0])]);
		return (0xffffff);
	}
	return (lib->textures_block[(int)map[coords[0]][coords[1]][coords[2]] - 1][(int)(pos[1] * 128 + pos[0])]);
}

static void			draw_minimap(char map[64][64][64], t_player *player,
	t_graphic_lib *lib, double coords[5])
{
	double		i;
	double		j;
	int		posx;
	int		posy;

	i = coords[0] - 1;
	posy = MINIMAP_HEIGHT_START;
	while ((i += 0.07692) <= coords[1])
	{
		j = coords[2] - 1;
		posx = MINIMAP_WIDTH_START;
		while ((j += 0.07692) <= coords[3])
		{
			lib->image[posy * WIDTH + posx] =
				select_color(map, lib, (int[3]){i, (int)coords[4], j},
				(double[2]){i, j});
			posx++;
		}
		posy++;
	}
	//draw_player_pos(lib, player);
}

void				minimap(char map[64][64][64], t_player *player,
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
	start_i -= (end_i > 63 ? end_i - 63 : 0);
	if (end_i > 63)
		end_i = 63;
	start_j -= (end_j > 63 ? end_j - 63 : 0);
	if (end_j > 63)
		end_j = 63;
	draw_minimap(map, player, lib, (double[5]){start_i, end_i, start_j
		, end_j, step});
}
