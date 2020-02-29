/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave_program.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 14:35:39 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/29 15:38:10 by dacuvill         ###   ########.fr       */
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

static void	close_fonts(t_doom *data)
{
	int i;

	i = 0;
	while (++i <= NBR_FONTS)
		TTF_CloseFont(data->lib.ptrfont[NBR_FONTS - i]);
	if (TTF_WasInit() == 1)
		TTF_Quit();
}

static void	free_textures(t_doom *data)
{
	int		i;

	i = -1;
	while (++i < NBR_TEXTURES_MENU)
		free(data->lib.menu_texture[i]);
	i = -1;
	while (++i < NBR_TEXTURES_EDITOR)
		free(data->lib.textures[i]);
	free(data->lib.character);
	free(data->lib.hud_texture);
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

int			leave_program(t_doom *data, int type)
{
	free_octree(data->octree);
	free_textures(data);
	if (data->lib.texture)
		SDL_DestroyTexture(data->lib.texture);
	if (data->lib.renderer)
		SDL_DestroyRenderer(data->lib.renderer);
	if (data->lib.window)
		SDL_DestroyWindow(data->lib.window);
	close_fonts(data);
	Mix_CloseAudio();
	SDL_Quit();
	return (type);
}
