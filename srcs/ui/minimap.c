#include "doom.h"
#include "player.h"
#include "graphic_lib.h"
#include "menus.h"

# define MINIMAP_WIDTH_START (WIDTH / 1.16)
# define MINIMAP_HEIGHT_START (HEIGHT / 15)

static inline int	select_color(char map[64][64][64], int coords[3],
	t_player *player)
{
	if (coords[0] == (int)player->camera.origin.z &&
		coords[2] == (int)player->camera.origin.x)
		return (0x009900);
	return (0x00e6e6);
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
			if (map[i][coords[4]][j] != 0)
				draw_rectangle(lib, (t_point){posx, posy}, (t_point){12, 12},
					select_color(map, (int [3]){i, 0, j}, player));
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
	draw_minimap(map, player, lib, (int [5]){start_i, end_i, start_j, end_j, step});
}