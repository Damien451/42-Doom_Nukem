/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_load_save.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 20:57:58 by dacuvill          #+#    #+#             */
/*   Updated: 2020/02/24 21:14:26 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "player.h"
#include "libft.h"
#include "menus.h"

static void	check_inputs_load(t_doom *data, t_button *btab, int but)
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
		{
			if (data->lib.event.key.keysym.sym == SDLK_UP ||
				(unsigned int)data->lib.event.key.keysym.sym ==
				data->tabinputs.keycode[0])
				data->button = data->button ? data->button - 1 : but - 1;
			else if (data->lib.event.key.keysym.sym == SDLK_DOWN ||
				(unsigned int)data->lib.event.key.keysym.sym ==
				data->tabinputs.keycode[2])
				data->button = data->button == but - 1 ? 0 : data->button + 1;
			else if (data->lib.event.key.keysym.sym == SDLK_ESCAPE)
				switch_state(data, LOAD_SAVE, MAIN_MENU);
			else if (data->lib.event.key.keysym.sym == SDLK_RETURN)
				switch_state(data, LOAD_SAVE, btab[data->button].state);
		}
	}
}

static void	buttons_load_save(t_button buttons[5])
{
	buttons[0] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER - (DEF_BUTTON_H + BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), PLAY_MENU, "NEW GAME");
	buttons[1] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), PLAY_MENU, "NEW GAME");
	buttons[2] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER + (DEF_BUTTON_H + BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), PLAY_MENU, "NEW GAME");
	buttons[3] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER + (DEF_BUTTON_H * 2 + BUTTON_GAP_Y * 2)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), MAIN_MENU, "RETURN");
}

int			state_load_save(t_doom *data)
{
	t_button	buttons[4];

	loop_music(data->mix.sounds[2], 2);
	ft_memset(data->lib.image, 0, WIDTH * HEIGHT * 4);
	ft_memcpy(data->lib.image, data->lib.menu_texture[4]->pixels
		, (WIDTH * HEIGHT) << 2);
	buttons_load_save(buttons);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	put_buttons_on_img(data, buttons, 4);
	put_string_on_renderer(data, point(WIDTH / 2, HEIGHT / 6),
		label("DOOMCRAFT", (SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[0]);
	put_buttons_names(data, buttons, (SDL_Color){255, 0, 0, 0}, 4);
	check_inputs_load(data, buttons, 4);
	SDL_RenderPresent(data->lib.renderer);
	return (0);
}
