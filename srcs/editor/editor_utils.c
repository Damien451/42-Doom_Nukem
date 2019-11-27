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
	data->lib.editor.picked_texture = j * 10 + i;
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
			data->map_to_save[i][step][j] =
				data->lib.editor.picked_texture + 1;
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
	int			tmpx;
	int			tmpy;
	int			tmpbrush;
	int			nbrx;
	int			nbry;

	tmpbrush = data->lib.editor.brush_size;
	tmpy = y - tmpbrush / 2;
	nbry = tmpbrush + 1;
	while (--nbry > 0)
	{
		nbrx = tmpbrush + 1;
		tmpx = x - tmpbrush / 2;
		while (--nbrx > 0)
		{
			if (tmpx >= 15 && tmpx <= 1030 && tmpy >= 15 && tmpy <= 1030)
				data->map_to_save[(tmpy - 10) / BLOCK_SIZE_EDITOR][
					step][(tmpx - 10) / BLOCK_SIZE_EDITOR] = 0;
			tmpx += BLOCK_SIZE_EDITOR;
		}
		tmpy += BLOCK_SIZE_EDITOR;
	}
}

void	draw_block(t_doom *data, int x, int y, int step)
{
	int			tmpx;
	int			tmpy;
	int			tmpbrush;
	int			nbrx;
	int			nbry;

	tmpbrush = data->lib.editor.brush_size;
	tmpy = y - tmpbrush / 2;
	nbry = tmpbrush + 1;
	while (--nbry > 0)
	{
		nbrx = tmpbrush + 1;
		tmpx = x - tmpbrush / 2;
		while (--nbrx > 0)
		{
			if (tmpx >= 15 && tmpx <= 1030 && tmpy >= 15 && tmpy <= 1030)
				data->map_to_save[(tmpy - 10) / BLOCK_SIZE_EDITOR][
					step][(tmpx - 10)
					/ BLOCK_SIZE_EDITOR] = data->lib.editor.picked_texture + 1;
			tmpx += BLOCK_SIZE_EDITOR;
		}
		tmpy += BLOCK_SIZE_EDITOR;
	}
}
