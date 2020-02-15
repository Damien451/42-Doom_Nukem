/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_sounds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:28:56 by dacuvill          #+#    #+#             */
/*   Updated: 2020/02/13 21:22:28 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "mixer.h"
#include "graphic_lib.h"

static void	play_movement_sounds(t_mixer *mix, unsigned int tmp,
	int f1, int f2)
{
	if (!(tmp & COURSE))
	{
		if ((f1 % 22 == 0) && !Mix_Playing(CHANNEL_FOOTSTEP))
			Mix_PlayChannel(CHANNEL_FOOTSTEP, mix->sounds[5], 0);
		else if (f1 % 22 == 11 && !Mix_Playing(CHANNEL_FOOTSTEP2))
			Mix_PlayChannel(CHANNEL_FOOTSTEP2, mix->sounds[6], 0);
	}
	else
	{
		if ((f2 % 14 == 0) && !Mix_Playing(CHANNEL_FOOTSTEP))
			Mix_PlayChannel(CHANNEL_FOOTSTEP, mix->sounds[5], 0);
		else if (f2 % 14 == 7 && !Mix_Playing(CHANNEL_FOOTSTEP2))
			Mix_PlayChannel(CHANNEL_FOOTSTEP2, mix->sounds[6], 0);
	}
}

static void	movement_sounds(t_doom *data, t_graphic_lib *lib,
	t_mixer *mix, t_player *player)
{
	static int		f1 = 0;
	static int		f2 = 0;
	unsigned int	tmp;

	tmp = lib->cam_keys;
	if (!(tmp & CRAWL) && data->map_to_save[(int)player->camera.origin.x]
		[(int)player->camera.origin.y - 2][(int)player->camera.origin.z] != 0
		&& ((tmp & CAMERA_TR_LEFT) || (tmp & CAMERA_TR_RIGHT)
		|| (tmp & CAMERA_TR_FRONT) || (tmp & CAMERA_TR_BACK)))
	{
		play_movement_sounds(mix, tmp, f1, f2);
		if (f1 == 110)
			f1 = -1;
		else if (f2 == 112)
			f2 = -1;
		++f1;
		++f2;
	}
	else
	{
		f1 = 0;
		f2 = 0;
	}
}

void		game_sounds(t_doom *data, t_player *player)
{
	movement_sounds(data, &data->lib, &data->mix, player);
}
