/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_octree_model.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:19:56 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/31 11:01:00 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "vec3.h"
#include "octree.h"
#include <math.h>
#include "libft.h"

static inline void		verify_and_add_to_queue(t_queue *queue[2]
	, t_octree *actual)
{
	int			i;

	i = 0;
	while (i < 8)
	{
		if (actual->child[i]->leaf == INSIDE)
		{
			queue[1]->next = queue_new(actual->child[i]);
			queue[1]->next->prev = queue[1];
			queue[1] = queue[1]->next;
		}
		i++;
	}
}

static inline int		breadth_first_create_octree(t_doom *data
	, t_octree *actual)
{
	t_queue		*queue[2];

	queue[0] = queue_new(actual);
	queue[1] = queue[0];
	while (queue[0])
	{
		actual = (t_octree*)queue[0]->ptr;
		if (actual->leaf == INSIDE)
		{
			if (actual->size > 2)
			{
				create_child(actual);
				check_if_child_isleaf(data, actual);
				verify_and_add_to_queue(queue, actual);
			}
		}
		queue[0] = queue[0]->next;
	}
	return (free_queue(queue));
}

int						create_octree_model(t_doom *data)
{
	t_octree	*actual;
	int			size;
	int			ret;

	size = SIZE_MAP;
	actual = create_node(size << 1, vec3l(size, size, size), NULL);
	data->octree_obj[data->actual_obj] = actual;
	ret = verify_inside_node_model(data, actual);
	if (ret == -1)
		actual->leaf = INSIDE;
	else if (!ret)
		actual->leaf = EMPTY;
	else
		actual->leaf = FULL;
	if (actual->leaf == INSIDE)
		breadth_first_create_octree(data, actual);
	return (0);
}
