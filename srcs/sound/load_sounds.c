/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_sounds.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:37:49 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/06 19:54:25 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <stdio.h>

int				load_sounds(t_doom *data)
{
	int			i;
	char		buf[70];

	i = -1;
	while (++i < NB_SOUND)
	{
		ft_bzero(buf, 70);
		sprintf(buf
			, "/sgoinfre/goinfre/Perso/dacuvill/sound/%d.wav", i);
		if (load_sound(buf, &(data->mix->sounds[i])))
			return (1);
	}
	return (0);
}
