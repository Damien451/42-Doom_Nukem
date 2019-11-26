#include "doom.h"
#include "menus.h"
#include "libft.h"

static void	put_sound_bars_strings(t_doom *data, int coordy, int nbsoundbar)
{
	char	string[35];

	ft_bzero(string, 35);
	if (nbsoundbar == 0)
		ft_strcat(string, "Master volume");
	else if (nbsoundbar == 1)
		ft_strcat(string, "Music volume");
	else if (nbsoundbar == 2)
		ft_strcat(string, "Sound effects volume");
	put_string_on_renderer(data, (t_point){WIDTH_CENTER * 1.005,
		coordy - BUTTON_GAP_Y * 1.5},
		label(string, RED), data->lib.ptrfont[2]);
	put_string_on_renderer(data, (t_point){WIDTH_CENTER ,
		coordy - BUTTON_GAP_Y * 1.5},
		label(string, WHITE), data->lib.ptrfont[2]);
}

static void	put_filled_bars(t_doom *data, int *tab)
{
	int		i;
	int		coordy;

	i = -1;
	while (++i < 3)
	{
		coordy = BAR_HEIGHT_START + 2 + i * BAR_GAP;
		draw_rectangle(&(data->lib), (t_point){BAR_WIDTH_START + 2, coordy},
			(t_point){(int)((tab[i] / 100.0) * BAR_WIDTH - 4),
			BAR_HEIGHT - 4}, 0xff0000);
	}
	i = -1;
	while (++i < 3)
	{
		coordy = BAR_HEIGHT_START + 2 + i * BAR_GAP;
		put_sound_bars_strings(data, coordy, i);
	}
}

void		put_sound_bars(t_doom *data, int *tab)
{
	int i;

	i = -1;
	while (++i < 3)
	{
		draw_rectangle(&(data->lib), (t_point){BAR_WIDTH_START, BAR_HEIGHT_START + i * BAR_GAP},
			(t_point){BAR_WIDTH, BAR_HEIGHT}, 0xffffff);
	}
	put_filled_bars(data, tab);
}
