#include "doom.h"
#include "libft.h"
#include "menus.h"
#include "inputs.h"
#include <fcntl.h>
#include <unistd.h>

static int	check_inputs_settings(t_doom *data, t_button *btab, int nbuttons)
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
		{
			if (data->lib.event.key.keysym.sym == SDLK_UP ||
				(unsigned int)data->lib.event.key.keysym.sym ==
				data->tabinputs.keycode[0])
				data->button = data->button == 0 ? nbuttons - 1 :
				data->button - 1;
			else if (data->lib.event.key.keysym.sym == SDLK_DOWN ||
				(unsigned int)data->lib.event.key.keysym.sym ==
				data->tabinputs.keycode[2])
				data->button = (data->button == nbuttons - 1)
				? 0 : data->button + 1;
			else if (data->lib.event.key.keysym.sym == SDLK_RETURN)
				switch_state(data, SETTINGS, btab[data->button].state);
		}
	}
	return (0);
}

int			state_settings_menu(t_doom *data)
{
	t_button	buttons[3];

	ft_memset(data->lib.image, 0, WIDTH * HEIGHT * 4);
	ft_memcpy(data->lib.image, data->lib.menu_texture[4]->pixels,
		(WIDTH * HEIGHT) << 2);
	buttons[0] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER - (DEF_BUTTON_H + BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), SETTINGS_SOUND,
			"SOUND SETTINGS");
	buttons[1] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), SETTINGS_INPUTS,
			"INPUT SETTINGS");
	buttons[2] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER + (DEF_BUTTON_H + BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), MAIN_MENU, "RETURN");
	SDL_SetRelativeMouseMode(SDL_TRUE);
	SDL_ShowCursor(SDL_FALSE);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	put_buttons_on_img(data, buttons, 3);
	put_string_on_renderer(data, point(WIDTH / 2, HEIGHT / 13),
		label("SETTINGS", (SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[1]);
	put_buttons_names(data, buttons, (SDL_Color){0, 0, 0, 0}, 3);
	if (check_inputs_settings(data, buttons, 3) != 0)
		return (1);
	SDL_RenderPresent(data->lib.renderer);
	return (0);
}
