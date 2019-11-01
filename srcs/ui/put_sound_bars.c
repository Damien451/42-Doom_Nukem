#include "doom.h"
#include "menus.h"

void	put_sound_bars(t_doom *data)
{
	int i;

	i = 0;
	while (i++ < 3)
	{
		draw_rectangle(&(data->lib), (t_point){500, (i + 1) * 300},
			(t_point){500, 10}, 0xffffff);
	}
}