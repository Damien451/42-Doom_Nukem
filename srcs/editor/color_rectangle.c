
#include "doom.h"
#include "libft.h"
#include "graphic_lib.h"
#include "vec3.h"

#include <stdio.h>

/*
** coords[0] = i, [1] = j,
** [2] = coord_x, [3] = coord_y
*/

static inline void	color_rectangle2(t_doom *data, unsigned int *color,
	int coords[4], double alpha)
{
	unsigned char	c_color[4];
	unsigned char	c_color2[4];

	c_color[0] = 0;
	c_color2[0] = 0;
	c_color[1] = *color >> 16;
	c_color[2] = (*color >> 8) & 255;
	c_color[3] = *color & 255;
	c_color2[1] = data->lib.image[(coords[0] + coords[2])
		* WIDTH + coords[3] + coords[1]] >> 16;
	c_color2[2] = (data->lib.image[(coords[0] + coords[2])
		* WIDTH + coords[3] + coords[1]] >> 8) & 255;
	c_color2[3] = data->lib.image[(coords[0] + coords[2])
		* WIDTH + coords[3] + coords[1]] & 255;
	c_color[1] = c_color[1] * alpha + c_color2[1] * (1.0 - alpha);
	c_color[2] = c_color[2] * alpha + c_color2[2] * (1.0 - alpha);
	c_color[3] = c_color[3] * alpha + c_color2[3] * (1.0 - alpha);
	*color = (c_color[1] << 16) | (c_color[2] << 8) | c_color[3];
}

static inline int	texture(int idtexture)
{
	if (idtexture > 28)
		return (idtexture);
	return (idtexture);
}

void				color_rectangle(t_doom *data, t_vec3l rectangle,
	int step, double alpha)
{
	int				i;
	int				j;
	int				coord_x;
	int				coord_y;
	unsigned int	color;

	i = -1;
	coord_x = rectangle.x * BLOCK_SIZE_EDITOR + 10;
	coord_y = rectangle.y * BLOCK_SIZE_EDITOR + 10;
	while (++i < BLOCK_SIZE_EDITOR)
	{
		j = -1;
		while (++j < BLOCK_SIZE_EDITOR)
		{
			color = ((unsigned int*)data->lib.textures[texture((int)data->map_to_save
				[rectangle.x][step][rectangle.y] - 1)]->pixels)
				[i * (64 / BLOCK_SIZE_EDITOR) * 64 + j *
				(64 / BLOCK_SIZE_EDITOR)];
			color_rectangle2(data, &color, (int[4]){i, j,
				coord_x, coord_y}, alpha);
			if (data->map_to_save[rectangle.x][step][rectangle.y] > 0)
				data->lib.image[(i + coord_x) * WIDTH + coord_y + j] = color;
		}
	}
}
