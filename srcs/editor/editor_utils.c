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
	if (data->lib.editor.pickmode == 0)
		data->lib.editor.picked_texture = j * 10 + i;
	else if (data->lib.editor.pickmode == 1)
		data->lib.editor.block1 = j * 10 + i;	
	else if (data->lib.editor.pickmode == 2)
		data->lib.editor.block2 = j * 10 + i;
	else if (data->lib.editor.pickmode == 3)
		data->lib.editor.blocktoremove = j * 10 + i;
	data->lib.editor.pickmode = 0;
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
	nbry = tmpbrush + 1;
	tmpy = (tmpbrush == 1 ? y : y - BLOCK_SIZE_EDITOR * tmpbrush / 2);
	while (--nbry > 0)
	{
		nbrx = tmpbrush + 1;
		tmpx = (tmpbrush == 1 ? x : x - BLOCK_SIZE_EDITOR * tmpbrush / 2);
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
	nbry = tmpbrush + 1;
	tmpy = (tmpbrush == 1 ? y : y - BLOCK_SIZE_EDITOR * tmpbrush / 2);
	while (--nbry > 0)
	{
		nbrx = tmpbrush + 1;
		tmpx = (tmpbrush == 1 ? x : x - BLOCK_SIZE_EDITOR * tmpbrush / 2);
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
