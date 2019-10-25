#include <menus.h>

int		draw_rectangle(t_graphic_lib *lib, t_point pos, t_point dim, int color)
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
			lib->image[(pos.y + i) * WIDTH + pos.x + x] = color;
			++x;
		}
		++i;
	}
	return (0);
}
