/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/12 22:03:07 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/05 11:51:52 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "player.h"
#include "gameplay.h"

int			init_game(t_doom *data, t_player *player)
{
	int		randmusic;

	randmusic = 3 + (rand() % NB_MUSIC);
	if (player->gamemode == CLASSIC_MODE)
	{
		player->lifes = 3;
		player->levels_left = 3;
		get_time_levels();
		select_next_level(data);
	}
	else
		player->lifes = -1;
	loop_music(data->mix.sounds[randmusic], randmusic);
	SDL_SetRelativeMouseMode(SDL_TRUE);
	reset_game_values(data, &data->player);
	//player->score = 1000000;
	printf("INIT GAME !\n");
	if (init_enemies(data, &data->enemies, data->map_to_save))
		return (1);
	return (0);
}
