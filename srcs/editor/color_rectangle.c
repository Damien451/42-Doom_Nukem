
#include "doom.h"
#include "libft.h"
#include "graphic_lib.h"
#include "vec3.h"

#include <stdio.h>

void		color_rectangle(t_doom *data, t_vec3l rectangle, int step)
{
	int			i;
	int			j;
	int			coord_x;
	int			coord_y;

	i = 0;
	coord_x = rectangle.x * BLOCK_SIZE_EDITOR + 10;
	coord_y = rectangle.y * BLOCK_SIZE_EDITOR + 10;
	while (i < BLOCK_SIZE_EDITOR)
	{
		j = 0;
		while (j < BLOCK_SIZE_EDITOR)
		{
			if (data->map_to_save[step][rectangle.x][rectangle.y] > 0)
				data->lib.image[(i + coord_x) * WIDTH + coord_y + j] =
					((unsigned int*)data->lib.textures[(int)data->map_to_save[step][rectangle.x][rectangle.y] - 1]->pixels)
					[i * (512 / BLOCK_SIZE_EDITOR) * 512 + j * (512 / BLOCK_SIZE_EDITOR)];
			else
				data->lib.image[(i + coord_x) * WIDTH + coord_y + j] = 0xFFFFFF;
			j++;
		}
		i++;
	}
}