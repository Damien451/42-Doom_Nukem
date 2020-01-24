/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_string_with_shadow.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:40:31 by dacuvill          #+#    #+#             */
/*   Updated: 2020/01/21 18:06:49 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "menus.h"
#include <SDL_ttf.h>
#include <SDL.h>

void	put_string_with_shadow(t_doom *data, t_point pos, t_label lab
	, TTF_Font *font)
{
	put_string_on_renderer(data, point(pos.x + 7, pos.y), label(lab.str,
		(SDL_Color){0, 0, 0, 0}), font);
	put_string_on_renderer(data, pos, lab, font);
}