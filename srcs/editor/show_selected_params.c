/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_selected_params.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 00:21:04 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/03 18:47:03 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"

/*
**	block[0] -> current block, block[1] -> texture id of the block
*/

static inline void	draw_textures_square(t_graphic_lib *lib, t_point pos,
	t_point dim, int block[2])
{
	t_point	end;
	int		y;
	int		x;
	int		color;

	end = add_points(pos, dim);
	y = 0;
	color = (lib->editor.pickmode == block[0] ? 0xff0000 : 0);
	while (pos.y + y < end.y)
	{
		x = 0;
		while (pos.x + x < end.x)
		{
			if (!(x > 1 && y > 1) || !(x < 14 && y < 14))
				lib->image[(pos.y + y) * WIDTH + pos.x + x] = color;
			else
				lib->image[(pos.y + y) * WIDTH + pos.x + x] =
				lib->textures[block[1]]
				[y * (64 / BLOCK_SIZE_EDITOR) * 64 +
				x * (64 / BLOCK_SIZE_EDITOR)];
			++x;
		}
		++y;
	}
}

static inline void	draw_select_square(t_graphic_lib *lib, t_point pos,
	t_point dim, int color)
{
	t_point	end;
	int		y;
	int		x;

	end = add_points(pos, dim);
	y = 0;
	while (pos.y + y < end.y)
	{
		x = 0;
		while (pos.x + x < end.x)
		{
			if (!(x >= 5 && y >= 5) || !(x <= 80 && y <= 80))
				lib->image[(pos.y + y) * WIDTH + pos.x + x] = color;
			++x;
		}
		++y;
	}
}

static inline void	draw_select_rectangle(t_graphic_lib *lib, t_point pos,
	t_point dim, int color)
{
	t_point	end;
	int		y;
	int		x;

	end = add_points(pos, dim);
	y = 0;
	while (pos.y + y < end.y)
	{
		x = 0;
		while (pos.x + x < end.x)
		{
			if (!(x >= 5 && y >= 5) || !(x <= 60 && y <= 30))
				lib->image[(pos.y + y) * WIDTH + pos.x + x] = color;
			++x;
		}
		++y;
	}
}

static void			show_brush_selection_and_selected_blocks(t_doom *data,
	unsigned int block1, unsigned int block2, unsigned int blocktoremove)
{
	int			x;
	int			tmpbrush;
	int			size;

	tmpbrush = data->lib.editor.brush_size;
	size = BLOCK_SIZE_EDITOR;
	if (tmpbrush == 1)
		x = 1268;
	else if (tmpbrush == 2)
		x = 1385;
	else if (tmpbrush == 3)
		x = 1497;
	else if (tmpbrush == 4)
		x = 1611;
	else
		x = 1720;
	draw_select_rectangle(&data->lib, point(x, 705), point(65, 35), 0x000000);
	draw_textures_square(&data->lib, point(1234, 581),
		point(size, size), (int[2]){1, (int)block1});
	draw_textures_square(&data->lib, point(1341, 581),
		point(size, size), (int[2]){2, (int)block2});
	draw_textures_square(&data->lib, point(1223, 647),
		point(size, size), (int[2]){3, (int)blocktoremove});
}

void				show_selected_params(t_doom *data)
{
	double		x;
	int			y;
	int			tmp;

	x = 1049 + (data->lib.editor.picked_texture % 10) * TEXTURE_SIZE
		+ (data->lib.editor.picked_texture % 10) * 3.5;
	y = data->lib.editor.picked_texture / 10;
	tmp = y;
	if (y == 0)
		y = -2;
	if (y == 3)
		y = 6;
	if (y == 4)
		y = 20;
	if (y == 5)
		y = 44;
	y += 13 + (tmp * TEXTURE_SIZE);
	if ((data->lib.editor.mode == 0 && data->lib.editor.picked_texture != 62)
		|| (data->lib.editor.mode == 1 && data->lib.editor.picked_texture < 40))
		draw_select_square(&data->lib, point((int)x, y),
			point(85, 85), 0xff0000);
	else if (data->lib.editor.mode == 1 && data->lib.editor.picked_texture == 62)
		draw_select_square(&data->lib, point(1049, 364),
			point(85, 85), 0xff0000);
	if (data->lib.editor.mode == 0)
		show_brush_selection_and_selected_blocks(data, data->lib.editor.block1,
			data->lib.editor.block2, data->lib.editor.blocktoremove);
}
