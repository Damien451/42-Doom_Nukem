#include "doom.h"
#include "graphic_lib.h"

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

static void			show_brush_selection(t_doom *data)
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
		x = 1495;
	else if (tmpbrush == 4)
		x = 1610;
	else
		x = 1720;
	draw_select_rectangle(&data->lib, (t_point){x, y}, (t_point){65, 35}, 0x000000);
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
	y += 13 + (tmp * TEXTURE_SIZE);
	draw_select_square(&data->lib, (t_point){(int)x, y}, (t_point){85, 85}, 0xff0000);
	if (data->lib.editor.mode == 0)
		show_brush_selection(data);
}