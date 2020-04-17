/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_anim_state_start.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 00:05:06 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/10 15:53:34 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "libft.h"
#include <SDL.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

static void		init_bubbles(t_doom *data)
{
	int			i;

	i = 0;
	while (i < NB_BUBBLE)
	{
		data->tab[i].pos = rand() % WIDTH * HEIGHT;
		if (rand() % 2)
			rand();
		data->tab[i].speed = rand() % 10 + 1;
		if (rand() % 3)
			rand();
		data->tab[i].size = rand() % 10 + 4;
		if (rand() % 4)
			rand();
		data->tab[i++].color = (rand() % 256) << 16;
	}
}

static void		init_credit(t_doom *data)
{
	t_bubble	*tmp;
	int			i;

	i = -1;
	tmp = NULL;
	while (++i < WIDTH * HEIGHT)
	{
		if (data->lib.credits[i] != 0xFFFFFF)
		{
			if (!tmp)
			{
				tmp = malloc(sizeof(t_bubble));
				tmp->pos = i;
				tmp->next = NULL;
				data->bubble_list = tmp;
			}
			else
			{
				tmp->next = malloc(sizeof(t_bubble));
				tmp->next->pos = i;
				tmp->next->next = NULL;
				tmp = tmp->next;
			}
		}
	}
}

static void		fill_tmp(t_bubble **tmp, int i, t_doom *data)
{
	if (!*tmp)
	{
		*tmp = malloc(sizeof(t_bubble));
		(*tmp)->pos = i;
		(*tmp)->next = NULL;
		data->lightning_list = *tmp;
	}
	else
	{
		(*tmp)->next = malloc(sizeof(t_bubble));
		(*tmp)->next->pos = i;
		(*tmp)->next->next = NULL;
		*tmp = (*tmp)->next;
	}
}

static void		fill_tmp2(t_bubble **tmp, int i, t_doom *data)
{
	if (!*tmp)
	{
		*tmp = malloc(sizeof(t_bubble));
		(*tmp)->pos = i;
		(*tmp)->next = NULL;
		data->lightning_list2 = *tmp;
	}
	else
	{
		(*tmp)->next = malloc(sizeof(t_bubble));
		(*tmp)->next->pos = i;
		(*tmp)->next->next = NULL;
		*tmp = (*tmp)->next;
	}
}

void			init_anim_state_start(t_doom *data)
{
	int				i;
	t_bubble		*tmp;
	t_bubble		*tmp2;

	init_bubbles(data);
	init_credit(data);
	tmp = NULL;
	i = -1;
	tmp2 = NULL;
	while (++i < WIDTH * HEIGHT)
	{
		if (data->lib.lightning[i] != UINT_MAX && (data->lib.lightning[i]
			% 0x1000000 <= 0x888888))
			fill_tmp(&tmp, i, data);
		else if (data->lib.lightning[i] != UINT_MAX && (data->lib.lightning[i]
			% 0x1000000 <= 0x999999))
			fill_tmp2(&tmp, i, data);
	}
}
