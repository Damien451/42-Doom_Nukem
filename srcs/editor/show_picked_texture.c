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
			if (!(x >= 5 && i >= 5) || !(x <= 78 && i <= 78))
				lib->image[(pos.y + i) * WIDTH + pos.x + x] = color;
			++x;
		}
		++i;
	}
}

void				show_picked_texture(t_doom *data)
{
	double		x;
	int			y;
	int			tmp;

	x = 1050 + (data->lib.picked_texture % 10) * TEXTURE_SIZE + (data->lib.picked_texture % 10) * 3.5;
	y = data->lib.picked_texture / 10;
	tmp = y;
	if (y == 2)
		y += 3;
	if (y == 3)
		y += 4;
	y += 13 + (tmp * TEXTURE_SIZE);
	draw_select_square(&data->lib, (t_point){(int)x, y}, (t_point){83, 83}, 0xff0000);
}