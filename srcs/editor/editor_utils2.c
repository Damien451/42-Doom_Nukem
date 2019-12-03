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