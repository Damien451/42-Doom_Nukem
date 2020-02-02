#include "doom.h"
#include "player.h"
#include "graphic_lib.h"
#include "menus.h"

/*static void	display_selected_block(t_graphic_lib *lib, t_player *player)
{
	int		i;
	int		j;

	i = -1;
	while (++i < INV_BLOCK_SIZE)
	{
		j = -1;
		while (++j < INV_BLOCK_SIZE)
		{
			lib->image[(BLOCK_POS_Y + i) * WIDTH + j + BLOCK_POS_X] =
			lib->textures_block[player->inventory.selected_block - 1]
			[i * (128 / INV_BLOCK_SIZE) * 128 + j * (128 / INV_BLOCK_SIZE)];
		}
	}
}*/

void		display_inventory(t_graphic_lib *lib, t_player *player)
{
	//display_selected_block(lib, player);
}