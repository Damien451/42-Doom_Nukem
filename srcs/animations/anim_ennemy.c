/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_ennemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 18:07:13 by dacuvill          #+#    #+#             */
/*   Updated: 2020/02/29 20:28:21 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "thread.h"
#include <pthread.h>

// frame 1 marche : 0 / 0 -> 43 / 60
// frame 2 marche : 213 / 0 -> 253 / 60
// frame 3 marche : 417 / 0 -> 457 / 60

static int		create_ennemy_anim(SDL_Surface *ennemy, unsigned int *image,
    int move)
{
	int			i;
	int			j;

	i = 0;
	while (i < 250)
	{
		j = 0;
		while (j < 165)
		{
			if (((unsigned int *)ennemy->pixels)[(i >> 2) * 500 + move + (j >> 2)] > 0xfffffff)
				image[i * WIDTH + j + 525 * WIDTH + (WIDTH - (WIDTH >> 3))] =
					((unsigned int *)ennemy->pixels)[(i >> 2) * 500 + move + (j >> 2)];
			j++;
		}
		i++;
	}
	return (0);
}

void			choose_animation_ennemy(SDL_Surface *ennemy,
    unsigned int *image, int frame)
{
	static int	anim = 0;
	static int	way = 0;

	if (frame % 10 == 0)
		anim += way;
	if (anim == 2)
		way = -1;
	if (anim == 0)
		way = 1;
	if (anim == 0)
		create_ennemy_anim(ennemy, image, 0);
	else if (anim == 1)
		create_ennemy_anim(ennemy, image, 213);
	else
		create_ennemy_anim(ennemy, image, 417);
}
