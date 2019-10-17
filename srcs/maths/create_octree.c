/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_octree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:19:56 by roduquen          #+#    #+#             */
/*   Updated: 2019/10/17 18:45:57 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "vec3.h"
#include "octree.h"
#include <math.h>
#include "libft.h"

t_octree	*create_node(int size, t_vec3l center)
{
	t_octree	*new;
	int			i;

	new = (t_octree*)malloc(sizeof(t_octree));
	if (!new)
		return (NULL);
	i = 0;
	while (i < 8)
		new->child[i++] = NULL;
	new->size = size;
	new->center = center;
	new->leaf = 0;
	return (new);
}

int		verify_inside_node(t_doom *data, t_octree *node)
{
	t_vec3l		tester;
	t_vec3l		count;
	int			nbr_node;

	nbr_node = 0;
	tester.x = (node->center.x - (node->size >> 1)) >> 1;
	tester.y = (node->center.y - (node->size >> 1)) >> 1;
	tester.z = (node->center.z - (node->size >> 1)) >> 1;
	count.x = -1;
	printf("SIZE = %d\n", node->size);
	while (++count.x < node->size >> 1)
	{
		count.y = -1;
		while (++count.y < node->size >> 1)
		{
			count.z = -1;
			while (++count.z < node->size >> 1)
			{
				if (data->map_to_save[tester.x + count.x][tester.y + count.y][tester.z + count.z])
					nbr_node++;
				else if (nbr_node)
					return (1);
			}
		}
	}
	return (nbr_node);
}

static int	create_child(t_octree *node)
{
		node->child[0] = create_node(node->size >> 1, (t_vec3l){node->center.x - (node->center.x >> 1), node->center.y - (node->center.y >> 1), node->center.z - (node->center.z >> 1)});
		node->child[1] = create_node(node->size >> 1, (t_vec3l){node->center.x + (node->center.x >> 1), node->center.y - (node->center.y >> 1), node->center.z - (node->center.z >> 1)});
		node->child[2] = create_node(node->size >> 1, (t_vec3l){node->center.x - (node->center.x >> 1), node->center.y + (node->center.y >> 1), node->center.z - (node->center.z >> 1)});
		node->child[3] = create_node(node->size >> 1, (t_vec3l){node->center.x + (node->center.x >> 1), node->center.y + (node->center.y >> 1), node->center.z - (node->center.z >> 1)});
		node->child[4] = create_node(node->size >> 1, (t_vec3l){node->center.x - (node->center.x >> 1), node->center.y - (node->center.y >> 1), node->center.z + (node->center.z >> 1)});
		node->child[5] = create_node(node->size >> 1, (t_vec3l){node->center.x + (node->center.x >> 1), node->center.y - (node->center.y >> 1), node->center.z + (node->center.z >> 1)});
		node->child[6] = create_node(node->size >> 1, (t_vec3l){node->center.x - (node->center.x >> 1), node->center.y + (node->center.y >> 1), node->center.z + (node->center.z >> 1)});
		node->child[7] = create_node(node->size >> 1, (t_vec3l){node->center.x + (node->center.x >> 1), node->center.y + (node->center.y >> 1), node->center.z + (node->center.z >> 1)});
		return (0);
}

static int	breadth_first_create_octree(t_doom *data, t_octree *actual)
{
	t_queue		*queue[2];
	int			i;
	int			ret;

	queue[0] = queue_new(actual);
	queue[1] = queue[0];
	while (queue[0])
	{
		if (((t_octree*)queue[0]->ptr)->leaf == INSIDE)
		{
			if (((t_octree*)queue[0]->ptr)->size > 1)
			{
				i = -1;
				create_child((t_octree*)queue[0]->ptr);
				while (++i < 8)
				{
					if ((ret = verify_inside_node(data, ((t_octree*)queue[0]->ptr)->child[i])) == 0)
						((t_octree*)queue[0]->ptr)->child[i]->leaf = EMPTY;
					else if (ret == (((t_octree*)queue[0]->ptr)->child[i]->size * ((t_octree*)queue[0]->ptr)->child[i]->size * ((t_octree*)queue[0]->ptr)->child[i]->size) >> 3)
						((t_octree*)queue[0]->ptr)->child[i]->leaf = FULL;
					else
					{
						((t_octree*)queue[0]->ptr)->child[i]->leaf = INSIDE;
						queue[1]->next = queue_new(((t_octree*)queue[0]->ptr)->child[i]);
						queue[1]->next->prev = queue[1];
						queue[1] = queue[1]->next;
					}
				}
			}
		}
		queue[0] = queue[0]->next;
	}
	while (queue[1])
	{
		queue[0] = queue[1]->prev;
		free(queue[1]);
		queue[1] = queue[0];
	}
	return (0);
}

int		create_octree(t_doom *data)
{
	t_octree	*actual;
	int			size;
	int			ret;

	size = SIZE_MAP;
	actual = create_node(size << 1, (t_vec3l){size, size, size});
	data->octree = actual;
	ret = verify_inside_node(data, actual);
	printf("ret = %d\n", ret);
	if (ret == (size * size * size) >> 3)
		actual->leaf = FULL;
	else if (!ret)
		actual->leaf = EMPTY;
	else
		actual->leaf = INSIDE;
	if (actual->leaf == INSIDE)
		breadth_first_create_octree(data, actual);
	return (0);
}
