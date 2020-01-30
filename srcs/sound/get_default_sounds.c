/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_default_sounds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:37:43 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/30 14:36:27 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "mixer.h"

void		get_default_sounds(t_doom *data)
{
	data->mix->v_master = 0;
	data->mix->v_music = 0.8;
	data->mix->v_sound_effects = 0.8;
}
