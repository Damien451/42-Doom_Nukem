/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_default_sounds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:37:43 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/06 19:28:24 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "mixer.h"

void		get_default_sounds(t_doom *data)
{
	data->mix->v_master = 0.1;
	data->mix->v_music = 0.8;
	data->mix->v_sound_effects = 0.8;
}
