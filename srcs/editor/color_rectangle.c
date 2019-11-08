
#include "doom.h"
#include "libft.h"
#include "graphic_lib.h"
#include "vec3.h"

#include <stdio.h>

void			color_rectangle(t_doom *data, t_vec3l rectangle, int step, double alpha)
{
	int			i;
	int			j;
	int			coord_x;
	int			coord_y;
	unsigned int	color;
	unsigned char	c_color[4];
	unsigned char	c_color2[4];

	i = 0;
	coord_x = rectangle.x * BLOCK_SIZE_EDITOR + 10;
	coord_y = rectangle.y * BLOCK_SIZE_EDITOR + 10;
	c_color2[0] = 0;
	c_color[0] = 0;
	while (i < BLOCK_SIZE_EDITOR)
	{
		j = 0;
		while (j < BLOCK_SIZE_EDITOR)
		{
			color = ((unsigned int*)data->lib.textures[(int)data->map_to_save[rectangle.x][step][rectangle.y] - 1]->pixels)
					[i * (512 / BLOCK_SIZE_EDITOR) * 512 + j * (512 / BLOCK_SIZE_EDITOR)];
			c_color[1] = color >> 16;
			c_color[2] = (color >> 8) & 255;
			c_color[3] = color & 255;
			c_color2[1] = data->lib.image[(i + coord_x) * WIDTH + coord_y + j] >> 16;
			c_color2[2] = (data->lib.image[(i + coord_x) * WIDTH + coord_y + j] >> 8) & 255;
			c_color2[3] = data->lib.image[(i + coord_x) * WIDTH + coord_y + j] & 255;
			c_color[1] = c_color[1] * alpha + c_color2[1] * (1.0 - alpha);
			c_color[2] = c_color[2] * alpha + c_color2[2] * (1.0 - alpha);
			c_color[3] = c_color[3] * alpha + c_color2[3] * (1.0 - alpha);
			color = (c_color[1] << 16) | (c_color[2] << 8) | c_color[3];
			if (data->map_to_save[rectangle.x][step][rectangle.y] > 0)
				data->lib.image[(i + coord_x) * WIDTH + coord_y + j] = color;
			j++;
		}
		i++;
	}
}
