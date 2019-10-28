/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_in_octree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:59:25 by roduquen          #+#    #+#             */
/*   Updated: 2019/10/26 22:20:03 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "octree.h"

static inline t_octree	*on_x_higher_than_middle(t_vec3d *position
	, t_octree *node)
{
	if (position->y < (double)(node->center.y >> 1))
	{
		if (position->z < (double)(node->center.z >> 1))
			return (node->child[1]);
		else
			return (node->child[5]);
	}
	else
	{
		if (position->z < (double)(node->center.z >> 1))
			return (node->child[3]);
		else
			return (node->child[7]);
	}
}

static inline t_octree	*on_x_lower_than_middle(t_vec3d *position
		, t_octree *node)
{
	if (position->y < (double)(node->center.y >> 1))
	{
		if (position->z < (double)(node->center.z >> 1))
			return (node->child[0]);
		else
			return (node->child[4]);
	}
	else
	{
		if (position->z < (double)(node->center.z >> 1))
			return (node->child[2]);
		else
			return (node->child[6]);
	}
}

t_octree				*find_actual_position(t_vec3d *position, t_octree *node)
{
	while (node->leaf != EMPTY)
	{
		if (node->leaf == INSIDE)
		{
			if (position->x < (double)(node->center.x >> 1))
				node = on_x_lower_than_middle(position, node);
			else
				node = on_x_higher_than_middle(position, node);
		}
	}
	return (node);
}
