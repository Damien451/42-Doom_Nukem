#include "doom.h"
#include "libft.h"
#include "menus.h"
#include "inputs.h"
#include <fcntl.h>
#include <unistd.h>

#include <stdio.h>

static int	save_inputs(t_doom *data)
{
	int			fd;

	if ((fd = open("./files/inputs", O_WRONLY | O_TRUNC | O_CREAT, 0777)) == -1)
		return (1);
	write(fd, (void*)data->tabinputs.keycode, NB_MODIF_INPUTS * 4);
	close(fd);
	switch_state(data, SETTINGS, MAIN_MENU);
	return (0);
}

static int	check_inputs_settings2(t_doom *data, int nbuttons)
{
	if (data->lib.event.key.keysym.sym == SDLK_RIGHT || 
		(unsigned int)data->lib.event.key.keysym.sym ==
		data->tabinputs.keycode[3])
	{
		if (data->button > 3)
			data->button = (data->button + 5 <= nbuttons - 1)
			? data->button + 5 : data->button;
		else
			data->button += 4;
	}
	else if (data->lib.event.key.keysym.sym == SDLK_RETURN)
	{
		if (data->button == 8)
		{
			if (save_inputs(data) != 0)
				return (1);
		}
		else if (data->button == 13)
			get_default_inputs(data);
		else
			switch_state(data, SETTINGS, GET_INPUT);
	}
	return (0);
}

static int	check_inputs_settings(t_doom *data, int nbuttons)
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
		{
			if (data->lib.event.key.keysym.sym == SDLK_UP ||
				(unsigned int)data->lib.event.key.keysym.sym == 
				data->tabinputs.keycode[0])
				data->button = data->button == 0 ? 0 : data->button - 1;
			else if (data->lib.event.key.keysym.sym == SDLK_DOWN ||
				(unsigned int)data->lib.event.key.keysym.sym ==
				data->tabinputs.keycode[2])
				data->button = (data->button == nbuttons - 1)
				? nbuttons - 1 : data->button + 1;
			else if (data->lib.event.key.keysym.sym == SDLK_LEFT || 
				(unsigned int)data->lib.event.key.keysym.sym ==
				data->tabinputs.keycode[1])
			{
				if (data->button > 3)
					data->button = ((data->button - 4) < 4)
					? data->button - 4 : data->button - 5;
			}
			else
				return (check_inputs_settings2(data, nbuttons));
		}
	}
	return (0);
}

static void	create_buttons2(t_doom *data, t_button *btab, int coords[NB_MODIF_INPUTS + 2][2])
{
	int			i;
	char		titles[NB_MODIF_INPUTS][30];
	char		*desc[NB_MODIF_INPUTS];

	i = -1;
	desc[0] = "Move forward - ";
	desc[1] = "Move left - ";
	desc[2] = "Move backward - ";
	desc[3] = "Move right - ";
	desc[4] = "Pick obj - ";
	desc[5] = "Reload - ";
	desc[6] = "Sprint - ";
	desc[7] = "Zoom - ";
	desc[8] = "Couch - ";
	desc[9] = "Jump - ";
	desc[10] = "Inventory - ";
	desc[11] = "Screenshot - ";
	while (++i < NB_MODIF_INPUTS + 2)
	{
		if (i != 8 && i != 13)
			btab[i] = button(point(coords[i][0], coords[i][1]), point(SET_BUTTON_W, SET_BUTTON_H), 0,
				ft_strcat(ft_strcpy(titles[(i > 8 ? i - 1 : i)], desc[(i > 8 ? i - 1 : i)]), SDL_GetKeyName(data->tabinputs.keycode[(i > 8 ? i - 1 : i)])));
		else if (i == 8)
			btab[8] = button(point(coords[i][0], coords[i][1]), point(SET_BUTTON_W, SET_BUTTON_H), 0, "Save & quit");
		else
			btab[13] = button(point(coords[i][0], coords[i][1]), point(SET_BUTTON_W, SET_BUTTON_H), 0, "Reset");
	}
}

static void	create_buttons(t_doom *data, t_button *btab)
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
			coords[i][0] = WIDTH_CENTER - (SET_BUTTON_W + SET_BUTTON_W / 2 + BUTTON_GAP_X);
		else if (i < 9)
			coords[i][0] = WIDTH_CENTER - SET_BUTTON_W / 2;
		else
			coords[i][0] = coords[8][0] + BUTTON_GAP_X + SET_BUTTON_W;
		coords[i][1] = (i < 4 ? posy[i] : posy[(i + 1) % 5]);
	}
	create_buttons2(data, btab, coords);
}

int			state_settings_menu(t_doom *data)
{
	t_button	buttons[14];

	ft_memset(data->lib.image, 0, WIDTH * HEIGHT * 4);
	create_buttons(data, buttons);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	put_buttons_on_img(data, buttons, 14);
	put_string_on_renderer(data, point(WIDTH / 2, HEIGHT / 13), label("SETTINGS", RED), data->lib.ptrfont[1]);
	put_buttons_names(data, buttons, BLACK, 14);
	if (check_inputs_settings(data, 14) != 0)
		return (1);
	SDL_RenderPresent(data->lib.renderer);
	return (0);
}

