#include "doom.h"
#include "menus.h"
#include "libft.h"

static void	put_sound_bars_strings(t_doom *data, t_point coords, int nbsoundbar)
{
	char	string[20];

	ft_bzero(string, 20);
	if (nbsoundbar == 0)
		ft_strcat(string, "Soundbar 1");
	else if (nbsoundbar == 1)
		ft_strcat(string, "Soundbar 2");
	else if (nbsoundbar == 2)
		ft_strcat(string, "Soundbar 3");
	put_string_on_renderer(data, (t_point){WIDTH_CENTER * 1.005, coords.y - BUTTON_GAP_Y * 1.5},
		label(string, BLACK), data->lib.ptrfont[2]);
	put_string_on_renderer(data, (t_point){WIDTH_CENTER , coords.y - BUTTON_GAP_Y * 1.5},
		label(string, RED), data->lib.ptrfont[2]);
}

static void	put_filled_bars(t_doom *data, int *tab)
{
	int		i;
	t_point	coords;

	i = -1;
	while (++i < 3)
	{
		coords.x = BAR_WIDTH_START + 2;
		coords.y = BAR_HEIGHT_START + 2 + i * BAR_GAP;
		draw_rectangle(&(data->lib), coords,
			(t_point){(int)((tab[i] / 100.0) * BAR_WIDTH - 4),
			BAR_HEIGHT - 4}, 0xff0000);
		put_sound_bars_strings(data, coords, i);
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
