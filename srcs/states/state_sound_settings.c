/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_sound_settings.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 15:25:53 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/16 20:09:50 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include "menus.h"
#include "inputs.h"
#include <fcntl.h>
#include <unistd.h>

static int	check_sound_settings(t_doom *data, int tab[3])
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
		{
			if (data->lib.event.key.keysym.sym == SDLK_UP ||
				(unsigned int)data->lib.event.key.keysym.sym ==
				data->tabinputs.keycode[0])
				data->button = data->button == 0 ? 1 : 0;
			else if (data->lib.event.key.keysym.sym == SDLK_DOWN ||
				(unsigned int)data->lib.event.key.keysym.sym ==
				data->tabinputs.keycode[2])
				data->button = (data->button == 1) ? 0 : 1;
			else if (data->lib.event.key.keysym.sym == SDLK_ESCAPE)
				switch_state(data, SETTINGS_SOUND, SETTINGS);
			else if (data->lib.event.key.keysym.sym == SDLK_RETURN &&
				data->button == 0)
				switch_state(data, SETTINGS_SOUND, SETTINGS);
			else if (data->lib.event.key.keysym.sym == SDLK_RETURN &&
				data->button == 1)
				get_default_sounds(data);
		}
		if (data->lib.event.type == SDL_MOUSEBUTTONDOWN)
			mouse_sound_commands(data, tab);
	}
	return (0);
}

static int	state_sound_settings_2(t_doom *data, int tab[3], t_button *btab)
{
	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_ShowCursor(SDL_TRUE);
	if (check_sound_settings(data, tab) != 0)
		return (1);
	put_buttons_on_img(data, btab, 2);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	put_sound_bars(data, tab);
	put_buttons_names(data, btab, (SDL_Color){0, 0, 0, 0}, 2);
	put_string_with_shadow(data, point(WIDTH / 2, HEIGHT / 6),
		label("SETTINGS", (SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[1]);
	SDL_RenderPresent(data->lib.renderer);
	return (0);
}

int			state_sound_settings(t_doom *data)
{
	t_button	buttons[2];
	static int	first = 1;
	static int	tab[3];

	if (first == 1)
	{
		tab[0] = (int)(data->mix.v_master * 100);
		tab[1] = (int)(data->mix.v_music * 100);
		tab[2] = (int)(data->mix.v_sound_effects * 100);
	}
	buttons[0] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER + (2 * DEF_BUTTON_H + 2 * BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), LEAVING, "RETURN");
	buttons[1] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER + (3 * DEF_BUTTON_H + 3 * BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), LEAVING, "RESET");
	ft_memset(data->lib.image, 0, WIDTH * HEIGHT * 4);
	ft_memcpy(data->lib.image, data->lib.menu_texture[4]->pixels
		, (WIDTH * HEIGHT) << 2);
	return (state_sound_settings_2(data, tab, buttons));
}
