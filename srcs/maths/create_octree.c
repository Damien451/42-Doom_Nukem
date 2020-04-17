/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_octree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:19:56 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/03 15:10:47 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "vec3.h"
#include "octree.h"
#include <math.h>
#include "libft.h"

static inline int		verify_inside_node(t_doom *data, t_octree *node)
{
	t_vec3l		tester;
	int			ret;
	int			nbr_node;

	init_all(&tester, data, &nbr_node, node);
	ret = inside_loopb(data, node, &nbr_node, tester);
	if (ret)
		return (ret);
	if (nbr_node != 0 && data->tmp != nbr_node)
		return (-1);
	return (nbr_node);
}

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
				check_if_child_is_leaf(data, actual);
				verify_and_add_to_queue(queue, actual);
			}
		}
		queue[0] = queue[0]->next;
	}
	return (free_queue(queue));
}

void					check_if_child_is_leaf(t_doom *data, t_octree *node)
{
	int			i;
	int			ret;

	i = 0;
	while (i < 8)
	{
		if ((ret = verify_inside_node(data, node->child[i])) == 0)
			node->child[i]->leaf = EMPTY;
		else if (ret == -1)
			node->child[i]->leaf = INSIDE;
		else if (ret == -2)
			node->child[i]->leaf = BREAKABLE;
		else
			node->child[i]->leaf = FULL;
		i++;
	}
}

int						create_octree(t_doom *data)
{
	t_octree	*actual;
	int			size;
	int			ret;

	size = SIZE_MAP;
	actual = create_node(size << 1, vec3l(size, size, size), NULL);
	data->octree = actual;
	ret = verify_inside_node(data, actual);
	if (ret == -1)
		actual->leaf = INSIDE;
	else if (!ret)
		actual->leaf = EMPTY;
	else
		actual->leaf = FULL;
	if (actual->leaf == INSIDE)
		breadth_first_create_octree(data, actual);
	create_light_array(data);
	return (0);
}
