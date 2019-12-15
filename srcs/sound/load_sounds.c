/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sounds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:37:49 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/15 16:37:51 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		add_sound_path(t_doom *data)
{
	data->mix->sound_path[0] = "ressources/sound/file_example_WAV_10MG.wav";
	data->mix->sound_path[1] = "ressources/sound/file_example_WAV_1MG.wav";
	data->mix->sound_path[2] = "ressources/sound/0124.wav";
	data->mix->sound_path[3] = "ressources/sound/Storm_exclamation.wav";
	data->mix->sound_path[4] = "ressources/sound/Posedion.wav";
}

int				load_sounds(t_doom *data)
{
	int			i;

	i = -1;
	add_sound_path(data);
	while (++i < NB_SOUND)
	{
		if (load_sound(data->mix->sound_path[i], &(data->mix->sounds[i])))
			return (1);
	}
	return (0);
}
