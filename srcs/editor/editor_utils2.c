#include "doom.h"
#include "graphic_lib.h"

void		replace_blocks(t_doom *data)
{
	int		i;
	int		j;
	int		step;
	int		block1;
	int		block2;

	block1 = data->lib.editor.block1;
	block2 = data->lib.editor.block2;
	step = -1;
	while (++step < SIZE_MAP)
	{
		i = -1;
		while (++i < SIZE_MAP)
		{
			j = -1;
			while (++j < SIZE_MAP)
				if (data->map_to_save[i][step][j] == block1 + 1)
					data->map_to_save[i][step][j] = block2 + 1;
		}
	}
}

void		remove_type_block(t_doom *data)
{
	int		i;
	int		j;
	int		step;
	int		blocktoremove;

	blocktoremove = data->lib.editor.blocktoremove;
	step = -1;
	while (++step < SIZE_MAP)
	{
		i = -1;
		while (++i < SIZE_MAP)
		{
			j = -1;
			while (++j < SIZE_MAP)
				if (data->map_to_save[i][step][j] == blocktoremove + 1)
					data->map_to_save[i][step][j] = 0;
		}
	}
}

void		copy_step(t_doom *data, int step)
{
	int		i;
	int		j;

	i = -1;
	while (++i < SIZE_MAP)
	{
		j = -1;
		while (++j < SIZE_MAP)
			data->map_to_save[i][step][j] = data->map_to_save[i][step - 1][j];
	}
}

void		pick_element(t_doom *data, int x, int y)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	x -= 1052;
	y -= 368;
	while ((i + 1) * 85 < x && i < 2)
		++i;
	while ((j + 1) * 83 < y && j < 2)
		++j;
	if (data->lib.editor.pickmode == 0)
		data->lib.editor.picked_texture = 40 + i;
	else if (data->lib.editor.pickmode == 1)
		data->lib.editor.block1 = 40 + i;
	else if (data->lib.editor.pickmode == 2)
		data->lib.editor.block2 = 40 + i;
	else if (data->lib.editor.pickmode == 3)
		data->lib.editor.blocktoremove = 40 + i;
	data->lib.editor.pickmode = 0;
}