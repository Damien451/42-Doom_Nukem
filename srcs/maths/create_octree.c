/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_octree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:19:56 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/27 15:25:13 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "vec3.h"
#include "octree.h"
#include <math.h>
#include "libft.h"

static inline void		init_all(t_vec3l *tester, t_doom *data, int *nbr_node
		, t_octree *node)
{
	data->tmp = 0;
	*nbr_node = 0;
	tester->x = (node->center.x >> 1) - (node->size >> 2);
	tester->y = (node->center.y >> 1) - (node->size >> 2);
	tester->z = (node->center.z >> 1) - (node->size >> 2);
}

static inline int		inside_loop(t_doom *data, t_octree *node, int *nbr_node
	, t_vec3l tester)
{
	t_vec3l		count;
	char		c;

	count.x = -1;
	while (++count.x < node->size >> 1 && (count.y = -1))
	{
		while (++count.y < node->size >> 1 && (count.z = -1))
		{
			while (++count.z < node->size >> 1)
			{
				if (((c = data->map_to_save[tester.x + count.x][tester.y +
					count.y][tester.z + count.z]) >= 41) && node->size >> 1 > 1)
					return (-1);
				else if (c >= 41)
					return (-2);
				else if (c)
					(*nbr_node)++;
				else if (*nbr_node)
					return (-1);
				data->tmp++;
			}
		}
	}
	return (0);
}

static inline int		verify_inside_node(t_doom *data, t_octree *node)
{
	t_vec3l		tester;
	int			ret;
	int			nbr_node;

	init_all(&tester, data, &nbr_node, node);
	ret = inside_loop(data, node, &nbr_node, tester);
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
			printf("actual->size = %d\n", actual->size);
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
