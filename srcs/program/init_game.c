/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 22:03:07 by dacuvill          #+#    #+#             */
/*   Updated: 2020/02/15 19:55:58 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "player.h"

void		init_game(t_doom *data, t_player *player)
{
	int		randmusic;

	randmusic = 3 + (rand() % NB_MUSIC);
	if (player->gamemode == CLASSIC_MODE)
	{
		player->lifes = 3;
		player->levels_left = 3;
		select_next_level(data);
	}
	else
		player->lifes = -1;
	loop_music(data->mix.sounds[randmusic], randmusic);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	set_player_spawn(data->map_to_save, &data->player.camera.origin);
	player->score = 0;
	data->player.camera.x_angle = 0;
}
