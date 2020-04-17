/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pick_element.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <dacuvill@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/17 19:00:06 by damien            #+#    #+#             */
/*   Updated: 2020/04/17 19:05:49 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"

static void	pick_ennemy(t_doom *data)
{
	if (data->lib.editor.pickmode == 0)
		data->lib.editor.picked_texture = 62;
	else if (data->lib.editor.pickmode == 1)
		data->lib.editor.block1 = 62;
	else if (data->lib.editor.pickmode == 2)
		data->lib.editor.block2 = 62;
	else
		data->lib.editor.blocktoremove = 62;
	data->lib.editor.pickmode = 0;
}

void		pick_element(t_doom *data, int x, int y)
{
	int		i;
	int		j;

	i = 0;
	j = 1;
	x -= 1052;
	y -= 368;
	if (data->lib.editor.mode == 1)
	{
		pick_ennemy(data);
		return ;
	}
	while ((i + 1) * 85 < x && i < 10)
		++i;
	while (j * 83 < y && j < 2)
		++j;
	if (data->lib.editor.pickmode == 0)
		data->lib.editor.picked_texture = 30 + 10 * j + i;
	else if (data->lib.editor.pickmode == 1)
		data->lib.editor.block1 = 30 + 10 * j + i;
	else if (data->lib.editor.pickmode == 2)
		data->lib.editor.block2 = 30 + 10 * j + i;
	else
		data->lib.editor.blocktoremove = 30 + 10 * j + i;
	data->lib.editor.pickmode = 0;
}
