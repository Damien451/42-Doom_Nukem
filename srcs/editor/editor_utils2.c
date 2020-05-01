/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 00:24:50 by dacuvill          #+#    #+#             */
/*   Updated: 2020/04/17 19:08:37 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"

void		init_editor(t_editor *editor)
{
	editor->picked_texture = 0;
	editor->brush_size = 1;
	editor->pickmode = 0;
	editor->block1 = 0;
	editor->block2 = 0;
	editor->blocktoremove = 0;
}

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
			if (data->map_to_save[i][step][j] != 63)
				data->map_to_save[i][step][j] =
					data->map_to_save[i][step - 1][j];
	}
}
