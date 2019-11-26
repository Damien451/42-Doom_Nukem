#include "doom.h"

void	pick_texture(t_doom *data, int x, int y)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	x -= 1052;
	y -= 16;
	while ((i + 1) * 85 < x)
		++i;
	while ((j + 1) * 83 < y)
		++j;
	data->lib.picked_texture = j * 10 + i;
}

void	fill_step(t_doom *data, int step)
{
	int			i;
	int			j;

	i = -1;
	while (++i < SIZE_MAP)
	{
		j = -1;
		while (++j < SIZE_MAP)
		{
			if (data->lib.picked_texture)
				data->map_to_save[i][step][j] =
					data->lib.picked_texture + 1;
		}
	}
}

void	reset_step(t_doom *data, int step)
{
	int			i;
	int			j;

	i = -1;
	while (++i < SIZE_MAP)
	{
		j = -1;
		while (++j < SIZE_MAP)
			data->map_to_save[i][step][j] = 0;
	}
}

void	erase_block(t_doom *data, int x, int y, int step)
{
	if (x >= 15 && y >= 15 && x <= 1030 && y <= 1030)
		data->map_to_save[(y - 10) / BLOCK_SIZE_EDITOR][step][(x - 10)
			/ BLOCK_SIZE_EDITOR] = 0;
}

void	draw_block(t_doom *data, int x, int y, int step)
{
	if (x >= 15 && y >= 15 && x <= 1030 && y <= 1030)
		data->map_to_save[(y - 10) / BLOCK_SIZE_EDITOR][step][(x - 10)
			/ BLOCK_SIZE_EDITOR] = data->lib.picked_texture + 1;
}
