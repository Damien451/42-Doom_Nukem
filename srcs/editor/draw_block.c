/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_block.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/04 20:49:10 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/03 18:44:28 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"

static inline void	place_block(t_doom *data, int step, int tmpx, int tmpy)
{
	if (data->lib.editor.picked_texture == 27)
		data->map_to_save[(tmpy - 10) / BLOCK_SIZE_EDITOR][step][(tmpx - 10)
		/ BLOCK_SIZE_EDITOR] = 47;
	else if (data->lib.editor.picked_texture == 28)
		data->map_to_save[(tmpy - 10) / BLOCK_SIZE_EDITOR][step][(tmpx - 10) 
		/ BLOCK_SIZE_EDITOR] = 48;
	else if (data->lib.editor.picked_texture == 62)
		data->map_to_save[(tmpy - 10) / BLOCK_SIZE_EDITOR][step][(tmpx - 10)
		/ BLOCK_SIZE_EDITOR] = data->lib.editor.picked_texture + 1;
	else if (data->lib.editor.picked_texture > 45)
		data->map_to_save[(tmpy - 10) / BLOCK_SIZE_EDITOR][step][(tmpx - 10)
		/ BLOCK_SIZE_EDITOR] = data->lib.editor.picked_texture + 3;
	else
		data->map_to_save[(tmpy - 10) / BLOCK_SIZE_EDITOR][step][(tmpx - 10)
		/ BLOCK_SIZE_EDITOR] = data->lib.editor.picked_texture + 1;
}

void				draw_block(t_doom *data, int x, int y, int step)
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
				place_block(data, step, tmpx, tmpy);
			tmpx += BLOCK_SIZE_EDITOR;
		}
		tmpy += BLOCK_SIZE_EDITOR;
	}
}
