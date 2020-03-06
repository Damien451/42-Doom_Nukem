/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_inventory.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 23:43:06 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/06 21:42:03 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "player.h"
#include "graphic_lib.h"
#include "menus.h"

static void	print_circle(t_graphic_lib *lib, int x, int y)
{
	int		i;
	int		j;

	i = -1;
	while(++i < 128)
	{
		j = -1;
		while (++j < 128)
		{
			if (lib->circle[i * 128 + j] > 0)
			{
				lib->image[(int)((y + i) * WIDTH + j + x)] =
				lib->circle[i * 128 + j];
			}
		}
	}
}

static void	display_select_circle(t_graphic_lib *lib, t_player *player)
{
	if (player->inventory.selected == 0)
		print_circle(lib, 33, 771);
	else if (player->inventory.selected == 1)
		print_circle(lib, 126, 854);
	else if (player->inventory.selected == 2)
		print_circle(lib, 230, 920);
	else if (player->inventory.selected == 3)
		print_circle(lib, 1569, 920);
	else if (player->inventory.selected == 4)
		print_circle(lib, 1672, 854);
	else
		print_circle(lib, 1763, 771);
}

static void	display_selected_block(t_graphic_lib *lib, t_player *player)
{
	int		i;
	int		j;
	int		aff;

	i = -1;
	aff = (player->inventory.selected
		> NBR_TEXTURES_BLOCKS + 2 ? 64 : 128);
	while (++i < INV_BLOCK_SIZE)
	{
		j = -1;
		while (++j < INV_BLOCK_SIZE)
		{
			lib->image[(BLOCK_POS_Y + i) * WIDTH + j + BLOCK_POS_X] =
			lib->textures
			[player->inventory.selected]
			[i * (aff / INV_BLOCK_SIZE) * aff + j * (aff / INV_BLOCK_SIZE)];
		}
	}
}

void		display_inventory(t_graphic_lib *lib, t_player *player, long state)
{
	if (state == EDITION_MODE)
		display_selected_block(lib, player);
	else
		display_select_circle(lib, player);
}
