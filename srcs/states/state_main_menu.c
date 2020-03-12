/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_main_menu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 15:21:38 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/12 16:33:18 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include "menus.h"
#include <unistd.h>

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
			else if (data->lib.event.key.keysym.sym == SDLK_DOWN ||
				(unsigned int)data->lib.event.key.keysym.sym ==
				data->tabinputs.keycode[2])
				data->button = data->button == but - 1 ? 0 : data->button + 1;
			else if (data->lib.event.key.keysym.sym == SDLK_RETURN)
				switch_state(data, MAIN_MENU, btab[data->button].state);
			else if (data->lib.event.key.keysym.sym == SDLK_ESCAPE)
				switch_state(data, MAIN_MENU, LEAVING);
		}
	}
}

static void	buttons_main_menu(t_button buttons[5])
{
	buttons[0] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER - (DEF_BUTTON_H + BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), PLAY_MENU, "PLAY");
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
	t_button				buttons[5];
	static int				total_frame = 0;
	static int				frame = 0;
	static unsigned long	time = 0;
	long					wait;

	if (!time)
		time = SDL_GetTicks();
	loop_music(data->mix.sounds[2], 2);
	ft_memset(data->lib.image, 0, WIDTH * HEIGHT * 4);
	ft_memcpy(data->lib.image, data->lib.bg_menu[0],
		(WIDTH * HEIGHT) << 2);
	anim_main_menu(data, total_frame++, frame);
	buttons_main_menu(buttons);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	put_buttons_on_img(data, buttons, 5);
	put_string_on_renderer(data, point(WIDTH / 2, HEIGHT / 6),
		label("DOOMCRAFT", (SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[0]);
	put_buttons_names(data, buttons, (SDL_Color){255, 0, 0, 0}, 5);
	check_inputs_menu(data, buttons, 5);
	if ((wait = (SDL_GetTicks() - time)) < 17)
		usleep(17000 - (wait * 1000));
	time = SDL_GetTicks();
	SDL_RenderPresent(data->lib.renderer);
	if (++frame == 1024)
		frame = 1;
	return (0);
}
