/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_octree.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:19:56 by roduquen          #+#    #+#             */
/*   Updated: 2019/11/10 09:50:55 by roduquen         ###   ########.fr       */
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
	t_vec3l		count;
	int			nbr_node;
	int			total;
	char		c;

	total = 0;
	nbr_node = 0;
	tester.x = (node->center.x >> 1) - (node->size >> 2);
	tester.y = (node->center.y >> 1) - (node->size >> 2);
	tester.z = (node->center.z >> 1) - (node->size >> 2);
	count.x = -1;
	while (++count.x < node->size >> 1 && (count.y = -1))
	{
		while (++count.y < node->size >> 1 && (count.z = -1))
		{
			while (++count.z < node->size >> 1)
			{
				if ((c = data->map_to_save[tester.x + count.x][tester.y + count.y]
					[tester.z + count.z]) == 2 && node->size >> 1 > 1)
					return (-1);
				else if (c == 2)
					return (-2);
				else if (c)
					nbr_node++;
				else if (nbr_node)
					return (-1);
				total++;
			}
		}
	}
	if (nbr_node != 0 && total != nbr_node)
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
				create_child(actual, data);
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

int						strlen_of_octree_v2(t_octree *node)
{
	int			i;
	int			r;

	i = 0;
	if (node)
	{
		r = 1;
		while (i < 8)
			r += strlen_of_octree_v2(node->child[i++]);
		return (r);
	}
	return (0);
}

int				fill_node_type(t_octree *node, unsigned int *value)
{
	int			i;
	int			nbr_inside;

	i = 0;
	nbr_inside = 0;
	while (i < 8)
	{
		*value |= node->child[i]->leaf;
		if (node->child[i]->leaf == INSIDE)
			nbr_inside++;
		i++;
		if (i < 8)
			(*value) <<= 2;
	}
	(*value) |= 0xFFFF0000;
	return (nbr_inside);
}

int						create_octree_v2(t_doom *data)
{
	int				i;
	t_octree		*actual;
	t_queue			*queue;
	t_queue			*end;
	unsigned int	index;
	unsigned int	*octree_v2;
	int				j;
	unsigned		nbr_inside;
	int				k;

	octree_v2 = malloc(40 * strlen_of_octree_v2(data->octree));
	ft_memset(octree_v2, 0, 40 * strlen_of_octree_v2(data->octree));
	queue = queue_new(data->octree);
	end = queue;
	index = 0;
	i = 2;
	while (queue)
	{
		actual = (t_octree*)queue->ptr;
		nbr_inside = fill_node_type(actual, &octree_v2[index]);
		if (nbr_inside)
		{
			octree_v2[i++] = index++;
			octree_v2[index++] = i;
			j = 0;
			while (j < 8)
			{
				if (actual->child[j]->leaf == INSIDE)
				{
					i++;
					k = 0;
					while (k < 8)
					{
						if (actual->child[j]->child[k] && actual->child[j]->child[k]->leaf == INSIDE)
						{
							if (fill_node_type(actual->child[j]->child[k], &nbr_inside))
							{
								i++;
								break ;
							}
						}
						k++;
					}
				}
				j++;
			}
		}
		index++;
		j = 0;
		k = 1;
		while (j < 8)
		{
			if (actual->child[j]->leaf == INSIDE)
			{
				end->next = queue_new(actual->child[j]);
				end->next->prev = end;
				end = end->next;
			}
			j++;
		}
		queue = queue->next;
	}
	data->octree_v2 = octree_v2;
	printf("Pointerless bytes used = %d\n", i * 4);
	return (0);
}

void				aff_octree(t_octree *node, t_doom *data, int oct[3])
{
	int i;
	i = 0;
	while (i < 8)
	{
		if (node->child[i])
			aff_octree(node->child[i], data, oct);
		i++;
	}
	if (node->leaf == INSIDE)
		oct[2]++;
	else if (node->leaf == EMPTY)
		oct[1]++;
	else
		oct[0]++;
}

int						create_octree(t_doom *data)
{
	t_octree	*actual;
	int			size;
	int			ret;
	int			oct[3];

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
	actual = data->octree;
	oct[0] = 0;
	oct[1] = 0;
	oct[2] = 0;
	aff_octree(actual, data, oct);
	printf("empty = %d, full = %d, inside = %d, total = %d, total bytes used = %d\n"
			, oct[1], oct[0], oct[2], oct[0] + oct[1] + oct[2], (oct[0] + oct[1] + oct[2]) * 65);
//	create_octree_v2(data);
	return (0);
}
