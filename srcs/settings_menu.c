#include "doom.h"
#include "libft.h"
#include "menus.h"
#include "inputs.h"

#include <stdio.h>

/*static int	get_input(t_doom *data, )

static void	change_input(t_doom *data, t_button *btab, int button)
{
	SDL_Event	event;

	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_KEYDOWN)
		else if (event.type == SDL_MOUSEBUTTONDOWN)

	}
	// wait for the user input
	// get the scancode of the input
	// give it to the corresponding input
}*/

static int	reset_inputs(t_doom *data)
{
	free_tabinputs(data);
	if (!(parse_input_dict(data, "./files/def_input_dictionnary")))
		return (1);
	return (0);
}

static int	check_inputs_settings2(t_doom *data, t_button *btab)
{
	const uint8_t	*input;

	(void)btab;

	input = SDL_GetKeyboardState(NULL);
	if (input[SDL_SCANCODE_RETURN])
	{
		if (data->button == 10) // save & quit -> write the file
			return (0);
		else if (data->button == 15)
		{
			if (reset_inputs(data) != 0)
				return (1);
		}
		else
			return (0);//change_input(data, btab, data->button);
	}
	return (0);
}

static int	check_inputs_settings(t_doom *data, t_button *btab, int nbuttons)
{
	const uint8_t	*input;

	input = SDL_GetKeyboardState(NULL);
	if (input[data->tabinputs.inputs[0].scancode]) /*|| input[SDL_SCANCODE_W])*/
		data->button = (data->button == -1 || data->button == 0)
			? 0 : data->button - 1;
	else if (input[SDL_SCANCODE_DOWN] || input[SDL_SCANCODE_S])
		data->button = (data->button == nbuttons - 1)
			? nbuttons - 1 : data->button + 1;
	else if (input[SDL_SCANCODE_LEFT] || input[SDL_SCANCODE_A])
	{
		if (!(data->button >= 10))
			data->button = (data->button - 5 >= 0)
				? data->button - 5 : data->button;
		else
			data->button -= 6;
	}
	else if (input[SDL_SCANCODE_RIGHT] || input[SDL_SCANCODE_D])
	{
		if (!(data->button > 4 && data->button < 10))
			data->button = (data->button + 5 <= nbuttons - 1)
				? data->button + 5 : data->button;
		else
			data->button += 6;
	}
	return (check_inputs_settings2(data, btab));
}

static void	create_buttons2(t_doom *data, t_button *btab, int *posx, int *posy)
{
	int			x;
	int			y;

	x = 0;
	y = -1;
	while (++y < 15)
	{
		if (y == 10)
		{
			btab[y] = button(point(posx[x], posy[5]),
				point(SET_BUTTON_W, SET_BUTTON_H), MAIN_MENU, "Return and Save");
			++x;
			++y;
		}
		btab[y] = button(point(posx[x], posy[y > 10 ? (y - 1) % 5 : y % 5]),
			point(SET_BUTTON_W, SET_BUTTON_H), 0, data->tabinputs.inputs[y > 10 ? y - 1 : y].set_title);
		if (y == 4)
			++x;
	}
	btab[y] = button(point(posx[x], posy[4]),
		point(SET_BUTTON_W, SET_BUTTON_H), 0, "Reset");
}

static void	create_buttons(t_doom *data, t_button *btab)
{
	int			y;
	int			posx[3];
	int			posy[6];

	y = 0;
	posx[0] = WIDTH_CENTER - (SET_BUTTON_W + SET_BUTTON_W / 2 + BUTTON_GAP_X);
	posx[1] = WIDTH_CENTER - SET_BUTTON_W / 2;
	posx[2] = posx[1] + BUTTON_GAP_X + SET_BUTTON_W;
	posy[0] = HEIGHT_CENTER - (BUTTON_GAP_Y + 2 * SET_BUTTON_H);
	while (++y < 6)
		posy[y] = posy[y - 1] + SET_BUTTON_H + BUTTON_GAP_Y;
	create_buttons2(data, btab, posx, posy);
}

int			settings_menu(t_doom *data)
{
	t_button	buttons[16];

	create_buttons(data, buttons);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	put_buttons_on_img(data, buttons, 16);
	put_string_on_renderer(data, point(WIDTH / 2, HEIGHT / 13), label("SETTINGS", RED), data->lib.ptrfont[1]);
	put_buttons_names(data, buttons, BLACK, 16);
	if (check_inputs_settings(data, buttons, 16) != 0)
		return (1);
	return (0);
}
