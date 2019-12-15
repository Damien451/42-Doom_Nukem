/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_main_menu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 15:21:38 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/15 15:24:58 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include "menus.h"

static void	check_inputs_menu(t_doom *data, t_button *btab, int but)
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
		{
			if (data->lib.event.key.keysym.sym == SDLK_UP ||
				(unsigned int)data->lib.event.key.keysym.sym ==
				data->tabinputs.keycode[0])
				data->button = data->button == 0 ? but - 1 : data->button - 1;
			if (data->lib.event.key.keysym.sym == SDLK_DOWN ||
				(unsigned int)data->lib.event.key.keysym.sym ==
				data->tabinputs.keycode[2])
				data->button = data->button == but - 1 ? 0 : data->button + 1;
			if (data->lib.event.key.keysym.sym == SDLK_RETURN)
				switch_state(data, MAIN_MENU, btab[data->button].state);
		}
	}
}

static void	buttons_main_menu(t_button buttons[5])
{
	buttons[0] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER - (DEF_BUTTON_H + BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), PLAYING, "PLAY");
	buttons[1] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), EDITOR_MENU, "MAP EDITOR");
	buttons[2] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER + (DEF_BUTTON_H + BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), SCORES, "SCOREBOARD");
	buttons[3] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER + (2 * DEF_BUTTON_H + 2 * BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), SETTINGS, "SETTINGS");
	buttons[4] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER + (3 * DEF_BUTTON_H + 3 * BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), LEAVING, "QUIT GAME");
}

int			state_main_menu(t_doom *data)
{
	t_button	buttons[5];
	static int	total_frame = 0;
	static int	frame = 0;
	static int	flag = 0;

	if (flag == 0)
	{
		loop_sound(data->mix->sounds[4]);
		flag = 1;
	}
	ft_memset(data->lib.image, 0, WIDTH * HEIGHT * 4);
	ft_memcpy(data->lib.image, data->lib.menu_texture[4]->pixels
		, (WIDTH * HEIGHT) << 2);
	anim_main_menu(data, total_frame++, frame);
	buttons_main_menu(buttons);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	put_buttons_on_img(data, buttons, 5);
	put_string_on_renderer(data, point(WIDTH / 2, HEIGHT / 8),
		label("DOOM", (SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[0]);
	put_buttons_names(data, buttons, (SDL_Color){0, 0, 0, 0}, 5);
	check_inputs_menu(data, buttons, 5);
	SDL_RenderPresent(data->lib.renderer);
	if (++frame == 1024)
		frame = 1;
	return (0);
}
