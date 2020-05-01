/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 22:48:34 by dacuvill          #+#    #+#             */
/*   Updated: 2020/02/25 23:39:49 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include <inputs.h>

static inline void	mouse_button_up(SDL_Event *event, t_editor *editor)
{
	if (event->button.button == SDL_BUTTON_LEFT)
		editor->mouseinputs &= ~L_INPUT_EDITOR;
	else if (event->button.button == SDL_BUTTON_RIGHT)
		editor->mouseinputs &= ~R_INPUT_EDITOR;
}

static inline void	mouse_button_down(t_doom *data, int *step,
	SDL_Event *event, t_editor *editor)
{
	if (event->button.x >= 15 && event->button.y >= 15
		&& event->button.x <= 1030 && event->button.y <= 1030 &&
		event->button.button == SDL_BUTTON_LEFT)
		editor->mouseinputs |= L_INPUT_EDITOR;
	else if (event->button.button == SDL_BUTTON_RIGHT)
		editor->mouseinputs |= R_INPUT_EDITOR;
	mouse_editor_commands(data, step);
}

void				editor_commands(t_doom *data, char map_name[50],
	int *step, int *first)
{
	if (data->lib.event.type == SDL_MOUSEBUTTONDOWN)
		mouse_button_down(data, step, &data->lib.event, &data->lib.editor);
	if (data->lib.event.type == SDL_MOUSEBUTTONDOWN
		&& data->lib.editor.mode == 0
		&& data->lib.event.button.x >= 1197 && data->lib.event.button.y >= 773
		&& data->lib.event.button.x <= 1226 && data->lib.event.button.y <= 802)
		save_map_to_file(data, map_name);
	if (data->lib.event.type == SDL_MOUSEBUTTONUP)
		mouse_button_up(&data->lib.event, &data->lib.editor);
	if (data->lib.editor.mouseinputs & L_INPUT_EDITOR)
		draw_block(data, data->lib.event.button.x,
			data->lib.event.button.y, *step);
	else if (data->lib.editor.mouseinputs & R_INPUT_EDITOR)
		erase_block(data, data->lib.event.button.x,
			data->lib.event.button.y, *step);
	else if (data->lib.event.type == SDL_KEYDOWN)
		keydown_editor_commands(data, step, first, map_name);
}
