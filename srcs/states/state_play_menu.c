/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_play_menu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 15:01:58 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/13 16:28:37 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "player.h"
#include "libft.h"
#include "menus.h"

static void	check_inputs_play(t_doom *data, t_button *btab, int but)
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
		{
			if (data->lib.event.key.keysym.sym == SDLK_UP ||
				(unsigned int)data->lib.event.key.keysym.sym ==
				data->tabinputs.keycode[0])
				data->button = data->button ? data->button - 1 : but - 1;
			if (data->lib.event.key.keysym.sym == SDLK_DOWN ||
				(unsigned int)data->lib.event.key.keysym.sym ==
				data->tabinputs.keycode[2])
				data->button = data->button == but - 1 ? 0 : data->button + 1;
			if (data->lib.event.key.keysym.sym == SDLK_RETURN)
			{
				if (data->button == 0)
					data->player.gamemode = CLASSIC_MODE;
				else if (data->button == 1)
					data->player.gamemode = FREEPLAY_MODE;
				switch_state(data, PLAY_MENU, btab[data->button].state);
			}
		}
	}
}

int			state_play_menu(t_doom *data)
{
	t_button	buttons[3];

	loop_sound(data->mix.sounds[2], 2);
	ft_memset(data->lib.image, 0, WIDTH * HEIGHT * 4);
	ft_memcpy(data->lib.image, data->lib.menu_texture[4]->pixels
		, (WIDTH * HEIGHT) << 2);
	buttons[0] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER - (DEF_BUTTON_H + BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), PLAYING, "CLASSIC MODE");
	buttons[1] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), PLAY_EDIT_MAP, "CUSTOM MAPS");
	buttons[2] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER + (DEF_BUTTON_H + BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), MAIN_MENU, "RETURN");
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	put_buttons_on_img(data, buttons, 3);
	put_string_on_renderer(data, point(WIDTH / 2, HEIGHT / 6),
		label("DOOM", (SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[0]);
	put_buttons_names(data, buttons, (SDL_Color){0, 0, 0, 0}, 3);
	check_inputs_play(data, buttons, 3);
	SDL_RenderPresent(data->lib.renderer);
	return (0);
}
