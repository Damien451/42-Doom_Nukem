/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sounds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:37:49 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/05 19:37:21 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		add_sound_path(t_doom *data)
{
	data->mix->sound_path[0] = "ressources/sound/0124.wav";
	data->mix->sound_path[1] = "ressources/sound/Storm_exclamation.wav";
	data->mix->sound_path[2] = "ressources/sound/Posedion.wav";
	data->mix->sound_path[3] = "ressources/sound/button_switch_sound.wav";
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
