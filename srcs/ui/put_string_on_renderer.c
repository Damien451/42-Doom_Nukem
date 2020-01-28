/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_string_on_renderer.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:41:11 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/27 20:40:19 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "menus.h"
#include "graphic_lib.h"
#include <SDL_ttf.h>
#include <SDL.h>

void    put_string_on_renderer(t_doom *data, t_point pos, t_label label
    , TTF_Font *font)
{
    SDL_Rect    dest;
    int         i;
    int         j;

    data->lib.surface = TTF_RenderText_Blended(font, label.str, label.color);
    i = 0;
    dest.w = data->lib.surface->w;
    dest.h = data->lib.surface->h;
//    printf("pitch = %d, width = %ld\n", data->lib.surface->pitch, dest.w);
    dest.x = pos.x - dest.w / 2;
    dest.y = pos.y;
    i = dest.y;
    while (i < dest.y + dest.h)
    {
        j = dest.x;
        while (j < dest.x + dest.w)
        {
			if (((unsigned int*)data->lib.surface->pixels)[j - dest.x + (i - dest.y) * dest.w] > 0xff0000)
				data->lib.image[j + i * WIDTH] = ((unsigned int*)data->lib.surface->pixels)[j - dest.x + (i - dest.y) * dest.w];
            j++;
        }
        i++;
    }
    SDL_FreeSurface(data->lib.surface);
}
