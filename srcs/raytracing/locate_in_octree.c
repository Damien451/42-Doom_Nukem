/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_in_octree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:59:25 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/11 13:05:04 by roduquen         ###   ########.fr       */
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

t_octree	*find_node_to_go_neighboor(t_vec3l position, t_octree *node)
{
	int			child;

	while (node->leaf == INSIDE)
	{
		child = 0;
		if (position.x > node->center.x)
			child |= 1;
		if (position.y >= node->center.y)
			child |= 2;
		if (position.z >= node->center.z)
			child |= 4;
		node = node->child[child];
	}
	return (node);
}

t_octree	*find_parent_x(t_vec3d position, t_octree *node, t_vec3d origin)
{
	t_vec3l		new;

	while (node && position.x != node->center.x / 2.0)
		node = node->parent;
	if (origin.x <= position.x)
		new.x = (position.x * 2.0) + 1;
	else
		new.x = (position.x * 2.0) - 1;
	new.y = (int)position.y * 2 + 1;
	new.z = (int)position.z * 2 + 1;
	if (node)
		return (find_node_to_go_neighboor(new, node));
	return (NULL);
}

t_octree	*find_parent_y(t_vec3d position, t_octree *node, t_vec3d origin)
{
	t_vec3l		new;

	while (node && position.y != node->center.y / 2.0)
		node = node->parent;
	if (origin.y <= position.y)
		new.y = (position.y * 2.0) + 1;
	else
		new.y = (position.y * 2.0) - 1;
	new.x = (int)position.x * 2 + 1;
	new.z = (int)position.z * 2 + 1;
	if (node)
		return (find_node_to_go_neighboor(new, node));
	return (NULL);
}

t_octree	*find_parent_z(t_vec3d position, t_octree *node, t_vec3d origin)
{
	t_vec3l		new;

	while (node && position.z != node->center.z / 2.0)
		node = node->parent;
	if (origin.z <= position.z)
		new.z = (position.z * 2.0) + 1;
	else
		new.z = (position.z * 2.0) - 1;
	new.y = (int)position.y * 2 + 1;
	new.x = (int)position.x * 2 + 1;
	if (node)
		return (find_node_to_go_neighboor(new, node));
	return (NULL);
}
