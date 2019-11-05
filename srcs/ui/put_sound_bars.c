#include "doom.h"
#include "menus.h"

void	put_sound_bars(t_doom *data)
{
	int i;

	i = -1;
	while (++i < 3)
	{
		draw_rectangle(&(data->lib), (t_point){BAR_WIDTH_START, BAR_HEIGHT_START + i * BAR_GAP},
			(t_point){BAR_WIDTH, BAR_HEIGHT}, 0xffffff);
	}
}

void	put_filled_bars(t_doom *data, int *tab)
{
	int i;

	i = -1;
	while (++i < 3)
	{
		draw_rectangle(&(data->lib), (t_point){BAR_WIDTH_START + 2, BAR_HEIGHT_START + 2 + (i) * BAR_GAP},
			(t_point){(int)((tab[i] / 100.0) * BAR_WIDTH - 4), BAR_HEIGHT - 4}, 0xff9900);
	}
}