/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_which_face_is_touched.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 15:51:32 by roduquen          #+#    #+#             */
/*   Updated: 2019/10/26 17:38:56 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "player.h"
#include "thread.h"
#include "octree.h"
#include <pthread.h>
#include <math.h>

int		check_x_intersect(t_vec3d *intersect, t_vec3d origin, t_vec3d ray
	, t_octree **node)
{
	double		distance;
	int			size;

	size = (*node)->size >> 1;
	intersect->x = ((*node)->center.x - size) >> 1;
	if ((distance = (intersect->x - origin.x) / ray.x) < 0)
	{
		intersect->x = ((*node)->center.x + size) >> 1;
		distance = (intersect->x - origin.x) / ray.x;
	}
	intersect->y = origin.y + distance * ray.y;
	intersect->z = origin.z + distance * ray.z;
	if (intersect->y >= (((*node)->center.y - size) >> 1)
		&& intersect->y < (((*node)->center.y + size) >> 1)
		&& intersect->z >= (((*node)->center.z - size) >> 1)
		&& intersect->z < (((*node)->center.z + size) >> 1))
	{
		if (!(*node)->parent)
			return (1);
		*node = find_node_to_go_parent(*intersect, *node, 1);
		if ((*node)->leaf == FULL)
			return (2);
		return (3);
	}
	return (0);
}

int		check_y_intersect(t_vec3d *intersect, t_vec3d origin, t_vec3d ray
	, t_octree **node)
{
	double		distance;
	int			size;

	size = (*node)->size >> 1;
	intersect->y = ((*node)->center.y - size) >> 1;
	if ((distance = (intersect->y - origin.y) / ray.y) < 0)
	{
		intersect->y = ((*node)->center.y + size) >> 1;
		distance = (intersect->y - origin.y) / ray.y;
	}
	intersect->x = origin.x + distance * ray.x;
	intersect->z = origin.z + distance * ray.z;
	if (intersect->x >= (((*node)->center.x - size) >> 1)
		&& intersect->x < (((*node)->center.x + size) >> 1)
		&& intersect->z >= (((*node)->center.z - size) >> 1)
		&& intersect->z < (((*node)->center.z + size) >> 1))
	{
		if (!(*node)->parent)
			return (1);
		*node = find_node_to_go_parent(*intersect, *node, 2);
		if ((*node)->leaf == FULL)
			return (2);
		return (3);
	}
	return (0);
}

int		check_z_intersect(t_vec3d *intersect, t_vec3d origin, t_vec3d ray
	, t_octree **node)
{
	double		distance;
	int			size;

	size = (*node)->size >> 1;
	intersect->z = ((*node)->center.z - size) >> 1;
	if ((distance = (intersect->z - origin.z) / ray.z) < 0)
	{
		intersect->z = ((*node)->center.z + size) >> 1;
		distance = (intersect->z - origin.z) / ray.z;
	}
	intersect->x = origin.x + distance * ray.x;
	intersect->y = origin.y + distance * ray.y;
	if (intersect->x >= (((*node)->center.x - size) >> 1)
		&& intersect->x < (((*node)->center.x + size) >> 1)
		&& intersect->y >= (((*node)->center.y - size) >> 1)
		&& intersect->y < (((*node)->center.y + size) >> 1))
	{
		if (!(*node)->parent)
			return (1);
		*node = find_node_to_go_parent(*intersect, *node, 3);
		if ((*node)->leaf == FULL)
			return (2);
		return (3);
	}
	return (0);
}
