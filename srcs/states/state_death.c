/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_death.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/11 19:03:39 by dacuvill          #+#    #+#             */
/*   Updated: 2020/01/13 20:52:29 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void	check_death_inputs(t_doom *data, int gamemode, int *ok)
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
		{
			if (data->player.lifes == 0 && gamemode == CLASSIC_MODE)
			{
				*ok = 1;
				switch_state(data, DEATH, PLAY_MENU);
			}
			if (data->lib.event.key.keysym.sym == SDLK_ESCAPE)
			{
				*ok = 1;
				switch_state(data, DEATH, PLAYING);
			}
			else if (data->lib.event.key.keysym.sym == SDLK_q)
			{
				*ok = 1;
				leave_game(data, &data->player);
				switch_state(data, DEATH, PLAY_MENU);
			}
		}
	}
}

static void	put_death_strings(t_doom *data, t_player *player)
{
	if (player->lifes > 0 || data->player.gamemode == FREEPLAY_MODE)
	{
		put_string_on_renderer(data, point(WIDTH / 2, HEIGHT / 13),
			label("YOU ARE DEAD", (SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[1]);
		put_string_on_renderer(data, point(WIDTH / 1.99, HEIGHT / 3),
			label("Press Enter to continue or Q to quit the game.",
			(SDL_Color){0, 0, 0, 0}), data->lib.ptrfont[2]);
		put_string_on_renderer(data, point(WIDTH / 2, HEIGHT / 3),
			label("Press Enter to continue or Q to quit the game.",
			(SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[2]);
	}
	else
	{
		put_string_on_renderer(data, point(WIDTH / 2, HEIGHT / 13),
			label("GAME OVER", (SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[1]);
		put_string_on_renderer(data, point(WIDTH / 1.99, HEIGHT / 3),
			label("Press any key to quit the game.",
			(SDL_Color){0, 0, 0, 0}), data->lib.ptrfont[2]);
		put_string_on_renderer(data, point(WIDTH / 2, HEIGHT / 3),
			label("Press any key to quit the game.",
			(SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[2]);
	}
}

int			state_death(t_doom *data)
{
	static int	ok = 1;

	if (ok == 1)
	{
		SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
		put_death_strings(data, &data->player);
		SDL_RenderPresent(data->lib.renderer);
		SDL_RenderClear(data->lib.renderer);
		data->player.lifes--;
		ok--;
	}
	check_death_inputs(data, data->player.gamemode, &ok);
	return (0);
}
