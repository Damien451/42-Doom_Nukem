/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 14:35:39 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/01 21:25:04 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <inputs.h>
#include "libft.h"
#include "octree.h"
#include "mixer.h"

static void	close_fonts_and_sounds(t_doom *data)
{
	int i;

	i = -1;
	while (++i < NBR_FONTS)
		TTF_CloseFont(data->lib.ptrfont[i]);
	i = -1;
	while (++i < NB_SOUND)
		Mix_FreeChunk(data->mix.sounds[i]);
	if (TTF_WasInit() == 1)
		TTF_Quit();
}

void		free_octree(t_octree *node)
{
	int			i;

	i = 0;
	if (node)
	{
		while (i < 8)
			free_octree(node->child[i++]);
		free(node);
		node = NULL;
	}
}

static void	free_octree_model(t_octree *node[NBR_OBJ])
{
	int		i;

	i = 0;
	while (i < NBR_OBJ)
	{
		free_octree(node[i]);
		i++;
	}
}

static void	free_bubbles(t_doom *data)
{
	t_bubble	*tmp;

	while (data->bubble_list)
	{
		tmp = data->bubble_list->next;
		free(data->bubble_list);
		data->bubble_list = tmp;
	}
	while (data->lightning_list)
	{
		tmp = data->lightning_list->next;
		free(data->lightning_list);
		data->lightning_list = tmp;
	}
	while (data->lightning_list2)
	{
		tmp = data->lightning_list2->next;
		free(data->lightning_list2);
		data->lightning_list2 = tmp;
	}
}

int			leave_program(t_doom *data, int type)
{
	free_octree(data->octree);
	free_octree_model(data->octree_obj);
	free_light_map(data);
	free_bubbles(data);
	close_fonts_and_sounds(data);
	Mix_CloseAudio();
	if (data->lib.texture)
		SDL_DestroyTexture(data->lib.texture);
	if (data->lib.renderer)
		SDL_DestroyRenderer(data->lib.renderer);
	if (data->lib.window)
		SDL_DestroyWindow(data->lib.window);
	SDL_Quit();
	free(data);
	return (type);
}
