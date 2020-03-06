/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sounds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:37:49 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/07 00:49:43 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <stdio.h>
#include "libft.h"

static int		load_sound(char *path, Mix_Chunk **sound)
{
	*sound = Mix_LoadWAV(path);
	if (*sound == NULL)
	{
		printf("Unable to load WAV file: %s\n", Mix_GetError());
		return (1);
	}
	return (0);
}

int				load_sounds(t_doom *data)
{
	int			i;
	char		buf[70];

	i = -1;
	while (++i < NB_SOUND)
	{
		ft_bzero(buf, 70);
		sprintf(buf
			, "ressources/sounds/%d.wav", i);
		if (load_sound(buf, &(data->mix.sounds[i])))
			return (1);
	}
	return (0);
}
