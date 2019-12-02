/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_in_octree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:59:25 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/02 09:01:35 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "octree.h"

t_octree				*find_actual_position(t_vec3d *position, t_octree *node)
{
	int			child;

	while (node->leaf != EMPTY)
	{
		child = 0;
		if (position->x >= (double)(node->center.x >> 1))
			child |= 1;
		if (position->y >= (double)(node->center.y >> 1))
			child |= 2;
		if (position->z >= (double)(node->center.z >> 1))
			child |= 4;
		node = node->child[child];
	}
	return (node);
}

t_octree		*find_node_to_go_neighboor(t_vec3d position, t_octree *node)
{
	int			child;

	while (node->leaf == INSIDE)
	{
		child = 0;
		if (position.x >= (double)(node->center.x >> 1))
			child |= 1;
		if (position.y >= (double)(node->center.y >> 1))
			child |= 2;
		if (position.z >= (double)(node->center.z >> 1))
			child |= 4;
		node = node->child[child];
	}
	return (node);
}
