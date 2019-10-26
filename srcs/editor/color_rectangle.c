
#include "doom.h"
#include "graphic_lib.h"
#include "vec3.h"

void		color_rectangle(t_doom *data, t_vec3l rectangle, int step)
{
	int			i;
	int			j;

	i = 0;
	while (i < BLOCK_SIZE_EDITOR)
	{
		j = 0;
		while (j < BLOCK_SIZE_EDITOR)
		{
			data->lib.image[(i + rectangle.x) * WIDTH + rectangle.y + j] =
				((unsigned int*)data->lib.picked_texture->pixels)[i * 512 / BLOCK_SIZE_EDITOR * 512 + j * (512 / BLOCK_SIZE_EDITOR)];
			j++;
		}
		i++;
	}
	if (rectangle.z)
	{
		data->map_to_save[step][rectangle.x / BLOCK_SIZE_EDITOR]
			[rectangle.y / BLOCK_SIZE_EDITOR] = 0;
	}
	else
	{
		data->map_to_save[step][rectangle.x / BLOCK_SIZE_EDITOR]
			[rectangle.y / BLOCK_SIZE_EDITOR] = 0;
	}
}