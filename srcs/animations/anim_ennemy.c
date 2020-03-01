/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_ennemy.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 18:07:13 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/01 22:03:41 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "thread.h"
#include <pthread.h>

# define ENNEMY_WALK_1			0
# define ENNEMY_WALK_2			213
# define ENNEMY_WALK_3			418

# define ENNEMY_WALK_P1			90
# define ENNEMY_WALK_P2			304
# define ENNEMY_WALK_P3			63 * 500

static int		create_ennemy_anim(const unsigned int ennemy[500 * 373], unsigned int *image,
    int frame, int move)
{
	int			i;
	int			j;

	i = 0;
	while (i < 230)
	{
		j = 0;
		while (j < 160)
		{
			if (ennemy[(i >> 2) * 500 + move + (j >> 2)] != 0xffffff)
				image[i * WIDTH + j + 525 * WIDTH + (WIDTH - (WIDTH >> 3))] =
					ennemy[(i >> 2) * 500 + move + (j >> 2)];
			j++;
		}
		i++;
	}
	return (0);
}

void			choose_animation_ennemy(const unsigned int ennemy[500 * 373],
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
		create_ennemy_anim(ennemy, image, frame, ENNEMY_WALK_1);
	else if (anim == 1)
		create_ennemy_anim(ennemy, image, frame, ENNEMY_WALK_2);
	else
		create_ennemy_anim(ennemy, image, frame, ENNEMY_WALK_3);
}
