/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mixer2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:37:55 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/15 18:23:45 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		change_volume(t_mixer *mix)
{
	if ((Mix_Volume(-1, (int)(mix->v_master
		* mix->v_sound_effects * 128)) == -1) ||
		(Mix_Volume(CHANNEL_MUSIC,
		(int)(mix->v_master * mix->v_music * 128)) == -1))
		return (-1);
	return (0);
}

int		set_master_volume(t_mixer *mix, double a)
{
	if (a < 0 || a > 1)
		return (-1);
	mix->v_master = a;
	change_volume(mix);
	return (0);
}

int		set_music_volume(t_mixer *mix, double a)
{
	if (a < 0 || a > 1)
		return (-1);
	mix->v_music = a;
	change_volume(mix);
	return (0);
}

int		set_sound_effects_volume(t_mixer *mix, double a)
{
	if (a < 0 || a > 1)
		return (-1);
	mix->v_sound_effects = a;
	change_volume(mix);
	return (0);
}
