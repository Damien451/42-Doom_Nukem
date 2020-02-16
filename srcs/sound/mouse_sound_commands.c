/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse_sound_commands.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:37:57 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/12 19:52:32 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include "menus.h"
#include "inputs.h"
#include <fcntl.h>
#include <unistd.h>

static void	mouse_sound_commands3(t_doom *data)
{
	if (data->lib.event.button.x >= WIDTH_CENTER - DEF_BUTTON_W &&
		data->lib.event.button.y >= HEIGHT_CENTER + (3 * DEF_BUTTON_H + 3
		* BUTTON_GAP_Y) && data->lib.event.button.x <= WIDTH_CENTER
		- DEF_BUTTON_W + DEF_BUTTON_W * 2 &&
		data->lib.event.button.y <= HEIGHT_CENTER + (3 * DEF_BUTTON_H + 3
		* BUTTON_GAP_Y) + DEF_BUTTON_H)
		get_default_sounds(data);
}

static void	mouse_sound_commands2(t_doom *data, int tab[3])
{
	if (data->lib.event.button.y >= BAR_HEIGHT_START + 2 * BAR_GAP
		&& data->lib.event.button.x >= BAR_WIDTH_START
		&& data->lib.event.button.y <= BAR_HEIGHT_START + BAR_HEIGHT + 2
		* BAR_GAP && data->lib.event.button.x <= BAR_WIDTH_START + BAR_WIDTH)
	{
		tab[2] = (int)((data->lib.event.button.x - BAR_WIDTH_START)
			* 100.0 / BAR_WIDTH + 0.5);
		set_sound_effects_volume(&data->mix, (data->lib.event.button.x -
			(double)BAR_WIDTH_START) / (double)BAR_WIDTH);
	}
	else if (data->lib.event.button.x >= WIDTH_CENTER - DEF_BUTTON_W &&
		data->lib.event.button.y >= HEIGHT_CENTER + (2 * DEF_BUTTON_H + 2
		* BUTTON_GAP_Y) && data->lib.event.button.x <= WIDTH_CENTER
		- DEF_BUTTON_W + DEF_BUTTON_W * 2 &&
		data->lib.event.button.y <= HEIGHT_CENTER + (2 * DEF_BUTTON_H + 2
		* BUTTON_GAP_Y) + DEF_BUTTON_H)
		switch_state(data, SETTINGS_SOUND, SETTINGS);
	mouse_sound_commands3(data);
}

void		mouse_sound_commands(t_doom *data, int tab[3])
{
	if (data->lib.event.button.y >= BAR_HEIGHT_START &&
		data->lib.event.button.x >= BAR_WIDTH_START && data->lib.event.button.y
		<= BAR_HEIGHT_START + BAR_HEIGHT && data->lib.event.button.x
		<= BAR_WIDTH_START + BAR_WIDTH)
	{
		tab[0] = (int)((data->lib.event.button.x - BAR_WIDTH_START)
			* 100.0 / BAR_WIDTH + 0.5);
		set_master_volume(&data->mix, (data->lib.event.button.x -
			(double)BAR_WIDTH_START) / (double)BAR_WIDTH);
	}
	else if (data->lib.event.button.y >= BAR_HEIGHT_START + BAR_GAP &&
		data->lib.event.button.x >= BAR_WIDTH_START && data->lib.event.button.y
		<= BAR_HEIGHT_START + BAR_HEIGHT + BAR_GAP && data->lib.event.button.x
		<= BAR_WIDTH_START + BAR_WIDTH)
	{
		tab[1] = (int)((data->lib.event.button.x - BAR_WIDTH_START)
			* 100.0 / BAR_WIDTH + 0.5);
		set_music_volume(&data->mix, (data->lib.event.button.x -
			(double)BAR_WIDTH_START) / (double)BAR_WIDTH);
	}
	mouse_sound_commands2(data, tab);
}
