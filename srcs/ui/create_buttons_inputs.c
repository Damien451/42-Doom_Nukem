#include "doom.h"
#include "menus.h"
#include "libft.h"
#include "inputs.h"

#include <stdio.h>

static void	init_desc(char desc[NB_MODIF_INPUTS][25])
{
	int			i;

	i = -1;
	while (++i < NB_MODIF_INPUTS)
		ft_bzero(desc[i], 25);
	ft_strcat(desc[0], "Move forward - ");
	ft_strcat(desc[1], "Move left - ");
	ft_strcat(desc[2], "Move backward - ");
	ft_strcat(desc[3], "Move right - ");
	ft_strcat(desc[4], "Pick obj - ");
	ft_strcat(desc[5], "Reload - ");
	ft_strcat(desc[6], "Sprint - ");
	ft_strcat(desc[7], "Zoom - ");
	ft_strcat(desc[8], "Couch - ");
	ft_strcat(desc[9], "Jump - ");
	ft_strcat(desc[10], "Inventory - ");
	ft_strcat(desc[11], "Screenshot - ");
}

static void	create_buttons_inputs2(t_doom *data, t_button *btab,
	int coords[NB_MODIF_INPUTS + 2][2])
{
	int			i;
	static char	titles[NB_MODIF_INPUTS][40];
	static char	desc[NB_MODIF_INPUTS][25];

	i = -1;
	init_desc(desc);
	while (++i < NB_MODIF_INPUTS + 2)
	{
		ft_bzero(&titles[i], 40);
		if (i != 8 && i != 13)
			btab[i] = button(point(coords[i][0], coords[i][1]),
				point(SET_BUTTON_W, SET_BUTTON_H), 0,
				ft_strcat(ft_strcpy(titles[(i > 8 ? i - 1 : i)],
				desc[(i > 8 ? i - 1 : i)]),
				SDL_GetKeyName(data->tabinputs.keycode[(i > 8 ? i - 1 : i)])));
		else if (i == 8)
			btab[8] = button(point(coords[i][0], coords[i][1]),
			point(SET_BUTTON_W, SET_BUTTON_H), 0, "Save & quit");
		else
			btab[13] = button(point(coords[i][0], coords[i][1]),
			point(SET_BUTTON_W, SET_BUTTON_H), 0, "Reset");
	}
}

void		create_buttons_inputs(t_doom *data, t_button *btab)
{
	int			posy[5];
	int			coords[NB_MODIF_INPUTS + 2][2];
	int			i;
	int			j;

	i = -1;
	j = 0;
	posy[0] = HEIGHT_CENTER - (BUTTON_GAP_Y + 2 * SET_BUTTON_H);
	while (++j < 5)
		posy[j] = posy[j - 1] + SET_BUTTON_H + BUTTON_GAP_Y;
	while (++i < NB_MODIF_INPUTS + 2)
	{
		if (i < 4)
			coords[i][0] = WIDTH_CENTER - (SET_BUTTON_W +
				SET_BUTTON_W / 2 + BUTTON_GAP_X);
		else if (i < 9)
			coords[i][0] = WIDTH_CENTER - SET_BUTTON_W / 2;
		else
			coords[i][0] = coords[8][0] + BUTTON_GAP_X + SET_BUTTON_W;
		coords[i][1] = (i < 4 ? posy[i] : posy[(i + 1) % 5]);
	}
	create_buttons_inputs2(data, btab, coords);
}
