/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octree_memory_management.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:31:37 by roduquen          #+#    #+#             */
/*   Updated: 2019/10/26 11:48:27 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "vec3.h"
#include "octree.h"
#include <math.h>
#include "libft.h"

t_octree	*create_node(int size, t_vec3l center, t_octree *parent)
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
	new->parent = parent;
	return (new);
}

int			create_child(t_octree *node, t_doom *data)
{
	int			offset;
	int			size;

	offset = node->size >> 2;
	size = node->size >> 1;
	node->child[0] = create_node(size, (t_vec3l){node->center.x
		- offset, node->center.y - offset, node->center.z - offset}, node);
	node->child[1] = create_node(size, (t_vec3l){node->center.x
		+ offset, node->center.y - offset, node->center.z - offset}, node);
	node->child[2] = create_node(size, (t_vec3l){node->center.x
		- offset, node->center.y + offset, node->center.z - offset}, node);
	node->child[3] = create_node(size, (t_vec3l){node->center.x
		+ offset, node->center.y + offset, node->center.z - offset}, node);
	node->child[4] = create_node(size, (t_vec3l){node->center.x
		- offset, node->center.y - offset, node->center.z + offset}, node);
	node->child[5] = create_node(size, (t_vec3l){node->center.x
		+ offset, node->center.y - offset, node->center.z + offset}, node);
	node->child[6] = create_node(size, (t_vec3l){node->center.x
		- offset, node->center.y + offset, node->center.z + offset}, node);
	node->child[7] = create_node(size, (t_vec3l){node->center.x
		+ offset, node->center.y + offset, node->center.z + offset}, node);
	check_if_child_is_leaf(data, node);
	return (0);
}

int			free_queue(t_queue *queue[2])
{
	while (queue[1])
	{
		queue[0] = queue[1]->prev;
		free(queue[1]);
		queue[1] = queue[0];
	}
	return (0);
}
