/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   switch_state.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 18:36:40 by dacuvill          #+#    #+#             */
/*   Updated: 2020/02/25 23:28:11 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "menus.h"

static int	check_before_switch(t_doom *data, long actual_state, long new_state)
{
	if (new_state != GET_INPUT && actual_state != GET_INPUT)
		data->button = 0;
	if (new_state == LEAVING)
	{
		data->running = 0;
		return (1);
	}
	if (new_state != EDITOR && new_state != SETTINGS_SOUND)
	{
		SDL_SetRelativeMouseMode(SDL_TRUE);
		SDL_ShowCursor(SDL_FALSE);
	}
	else
	{
		SDL_SetRelativeMouseMode(SDL_FALSE);
		SDL_ShowCursor(SDL_TRUE);
	}
	return (0);
}

void		switch_state(t_doom *data, long actual_state, long new_state)
{
	if (check_before_switch(data, actual_state, new_state))
		return ;
	data->state = new_state;
	if ((new_state == PLAYING || new_state == TEST_MODE)
		&& actual_state != PAUSE && actual_state != DEATH
		&& actual_state != FINISHED)
	{
		data->lib.cam_keys = 0;
		free_octree(data->octree);
		create_octree(data);
		init_game(data, &data->player);
	}
}
