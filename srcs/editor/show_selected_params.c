#include "doom.h"
#include "graphic_lib.h"

/*
**	block[0] -> current block, block[1] -> texture id of the block
*/

static inline void	draw_textures_square(t_graphic_lib *lib, t_point pos,
	t_point dim, int block[2])
{
	t_point	end;
	int		i;
	int		x;
	int		color;

	end = add_points(pos, dim);
	i = 0;
	color = (lib->editor.pickmode == block[0] ? 0xff0000 : 0);
	while (pos.y + i < end.y)
	{
		x = 0;
		while (pos.x + x < end.x)
		{
			if (!(x >= 2 && i >= 2) || !(x <= 18 && i <= 18))
				lib->image[(pos.y + i) * WIDTH + pos.x + x] = color;
			else
				lib->image[(pos.y + i) * WIDTH + pos.x + x] =
				((unsigned int *)lib->textures[block[1]]->pixels)
				[(x - 2) * (128 / BLOCK_SIZE_EDITOR) * 128 +
				(i - 2) * (128 / BLOCK_SIZE_EDITOR)];
			++x;
		}
		++i;
	}
}

static inline void	draw_select_square(t_graphic_lib *lib, t_point pos,
	t_point dim, int color)
{
	t_point	end;
	int		i;
	int		x;

	end = add_points(pos, dim);
	i = 0;
	while (pos.y + i < end.y)
	{
		x = 0;
		while (pos.x + x < end.x)
		{
			if (!(x >= 5 && i >= 5) || !(x <= 80 && i <= 80))
				lib->image[(pos.y + i) * WIDTH + pos.x + x] = color;
			++x;
		}
		++i;
	}
}

static inline void	draw_select_rectangle(t_graphic_lib *lib, t_point pos,
	t_point dim, int color)
{
	t_point	end;
	int		i;
	int		x;

	end = add_points(pos, dim);
	i = 0;
	while (pos.y + i < end.y)
	{
		x = 0;
		while (pos.x + x < end.x)
		{
			if (!(x >= 5 && i >= 5) || !(x <= 60 && i <= 30))
				lib->image[(pos.y + i) * WIDTH + pos.x + x] = color;
			++x;
		}
		++i;
	}
}

static void			show_brush_selection_and_selected_blocks(t_doom *data,
	unsigned int block1, unsigned int block2, unsigned int blocktoremove)
{
	int			x;
	int			y;
	int			tmpbrush;

	y = 705;
	tmpbrush = data->lib.editor.brush_size;
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
	draw_select_rectangle(&data->lib, (t_point){x, y},
			(t_point){65, 35}, 0x000000);
	draw_textures_square(&data->lib, (t_point){1234, 581},
		(t_point){20, 20}, (int [2]){1, (int)block1});
	draw_textures_square(&data->lib, (t_point){1341, 581},
		(t_point){20, 20}, (int [2]){2, (int)block2});
	draw_textures_square(&data->lib, (t_point){1223, 647},
		(t_point){20, 20}, (int [2]){3, (int)blocktoremove});
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
	if (y == 1)
		y = 1;
	if (y == 2)
		y = 2;
	if (y == 3)
		y = 6;
	if (y == 4)
		y = 20;
	y += 13 + (tmp * TEXTURE_SIZE);
	draw_select_square(&data->lib, (t_point){(int)x, y},
		(t_point){85, 85}, 0xff0000);
	if (data->lib.editor.mode == 0)
		show_brush_selection_and_selected_blocks(data, data->lib.editor.block1,
			data->lib.editor.block2, data->lib.editor.blocktoremove);
}