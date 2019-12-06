/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_in_octree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:59:25 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/03 11:26:58 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "octree.h"

t_octree	*find_actual_position(t_vec3d *position, t_octree *node)
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

t_octree	*find_node_to_go_neighboor(t_vec3d position, t_octree *node)
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

t_octree	*find_parent_x(t_vec3d position, t_octree *node, t_vec3d origin)
{
	while (node && position.x != node->center.x / 2.0)
		node = node->parent;
	if (origin.x <= position.x)
		position.x += 0.5;
	else
		position.x -= 0.5;
	position.y = (int)position.y + 0.5;
	position.z = (int)position.z + 0.5;
	if (node)
		return (find_node_to_go_neighboor(position, node));
	return (NULL);
}

t_octree	*find_parent_y(t_vec3d position, t_octree *node, t_vec3d origin)
{
	while (node && position.y != node->center.y / 2.0)
		node = node->parent;
	if (origin.y <= position.y)
		position.y += 0.5;
	else
		position.y -= 0.5;
	position.x = (int)position.x + 0.5;
	position.z = (int)position.z + 0.5;
	if (node)
		return (find_node_to_go_neighboor(position, node));
	return (NULL);
}

t_octree	*find_parent_z(t_vec3d position, t_octree *node, t_vec3d origin)
{
	while (node && position.z != node->center.z / 2.0)
		node = node->parent;
	if (origin.z <= position.z)
		position.z += 0.5;
	else
		position.z -= 0.5;
	position.y = (int)position.y + 0.5;
	position.x = (int)position.x + 0.5;
	if (node)
		return (find_node_to_go_neighboor(position, node));
	return (NULL);
}
