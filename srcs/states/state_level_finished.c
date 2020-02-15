/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_level_finished.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:23:39 by dacuvill          #+#    #+#             */
/*   Updated: 2020/02/12 17:43:08 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

/*
**	Faire un check du score au préalable pour l'ajouter si besoin au tableau des highscores
*/

static void	check_inputs(t_doom *data, int gamemode, int *ok)
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN &&
			data->lib.event.key.keysym.sym == SDLK_RETURN)
		{
			if (data->player.levels_left == 0 || gamemode == FREEPLAY_MODE)
			{
				*ok = 1;
				leave_game(data, &data->player);
				switch_state(data, FINISHED, PLAY_MENU);
			}
			else
			{
				*ok = 1;
				select_next_level(data);
				switch_state(data, FINISHED, PLAYING);
			}
		}
	}
}

static void	put_strings(t_doom *data, t_player *player)
{
	put_string_with_shadow(data, point(WIDTH / 2, HEIGHT / 8),
		label("LEVEL CLEAR", (SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[1]);
	if (player->gamemode == FREEPLAY_MODE || !player->levels_left)
		put_string_with_shadow(data, point(WIDTH / 2, HEIGHT / 3),
			label("Press enter to return to the menu",
			(SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[2]);
	else if (player->gamemode == CLASSIC_MODE && player->levels_left == 2)
	{
		put_string_with_shadow(data, point(WIDTH / 2, HEIGHT / 3),
			label("2 levels left, press enter to continue.",
			(SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[2]);
	}
	else if (player->gamemode == CLASSIC_MODE &&
		player->levels_left == 1)
	{
		put_string_with_shadow(data, point(WIDTH / 2, HEIGHT / 3),
			label("1 level left, press enter to continue.",
			(SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[2]);
	}
}

int			state_level_finished(t_doom *data)
{
	static int	ok = 1;

	if (ok == 1)
	{
		data->player.levels_left--;
		SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
		put_strings(data, &data->player);
		SDL_RenderPresent(data->lib.renderer);
		SDL_RenderClear(data->lib.renderer);
		Mix_HaltChannel(-1);
		ok--;
	}
	check_inputs(data, data->player.gamemode, &ok);
	return (0);
}
