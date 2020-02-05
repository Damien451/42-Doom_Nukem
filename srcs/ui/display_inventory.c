#include "doom.h"
#include "player.h"
#include "graphic_lib.h"
#include "menus.h"

static void	display_selected_block(t_graphic_lib *lib, t_player *player)
{
	int		i;
	int		j;
	int		aff;

	i = -1;
	aff = (player->inventory.selected_block > NBR_TEXTURES_BLOCKS + 2 ? 64 : 128);
	while (++i < INV_BLOCK_SIZE)
	{
		j = -1;
		while (++j < INV_BLOCK_SIZE)
		{
			lib->image[(BLOCK_POS_Y + i) * WIDTH + j + BLOCK_POS_X] =
			((unsigned int*)lib->textures[player->inventory.selected_block - 1]->pixels)
			[i * (aff / INV_BLOCK_SIZE) * aff + j * (aff / INV_BLOCK_SIZE)];
		}
	}
}

void		display_inventory(t_graphic_lib *lib, t_player *player)
{
	display_selected_block(lib, player);
}