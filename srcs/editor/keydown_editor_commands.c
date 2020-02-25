/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keydown_editor_commands.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 22:55:22 by dacuvill          #+#    #+#             */
/*   Updated: 2020/02/26 00:29:50 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include <inputs.h>
#include <fcntl.h>
#include <unistd.h>

static inline void	keydown_editor_commands2(t_doom *data, int *step,
	char *map_name)
{
	if (data->lib.event.key.keysym.sym == SDLK_g
		&& !data->lib.event.key.repeat)
		data->lib.editor.alpha = data->lib.editor.alpha == 1 ? 10 : 1;
	else if (data->lib.event.key.keysym.sym == SDLK_s
		&& !data->lib.event.key.repeat)
		save_map_to_file(data, map_name);
	else if (data->lib.event.key.keysym.sym == SDLK_f
		&& !data->lib.event.key.repeat)
		fill_step(data, *step);
	else if (data->lib.event.key.keysym.sym == SDLK_r
		&& !data->lib.event.key.repeat)
		reset_step(data, *step);
	else if (data->lib.event.key.keysym.sym == SDLK_c
		&& !data->lib.event.key.repeat)
		copy_step(data, *step);
}

void				keydown_editor_commands(t_doom *data, int *step,
	int *first, char *map_name)
{
	if (data->lib.event.key.keysym.sym == SDLK_UP)
		*step = (*step < SIZE_MAP - 1 ? *step + 1 : *step);
	else if (data->lib.event.key.keysym.sym == SDLK_DOWN)
		*step = (*step > 0 ? *step - 1 : *step);
	else if (data->lib.event.key.keysym.sym == SDLK_ESCAPE)
	{
		*first = 0;
		*step = 0;
		switch_state(data, EDITOR, EDITOR_MENU);
	}
	else if (data->lib.event.key.keysym.sym == SDLK_t
		&& !data->lib.event.key.repeat)
	{
		data->player.gamemode = TEST_MODE;
		switch_state(data, EDITOR, TEST_MODE);
	}
	keydown_editor_commands2(data, step, map_name);
}
