/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_which_face_is_touched_pos.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 15:51:32 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/02 05:49:29 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "player.h"
#include "thread.h"
#include "octree.h"
#include <pthread.h>
#include <math.h>

int		check_x_intersect_pos(t_vec3d *intersect, t_vec3d origin, t_ray *ray
		, t_octree **node)
{
	double		distance;
	int			size;

	size = (*node)->size >> 1;
	intersect->x = ((*node)->center.x + size) >> 1;
	if ((distance = (intersect->x - origin.x)) <= 0)
		return (-1);
	distance /= ray->direction.x;
	intersect->y = origin.y + distance * ray->direction.y;
	if (intersect->y >= (((*node)->center.y - size) >> 1)
			&& intersect->y <= (((*node)->center.y + size) >> 1))
	{
		intersect->z = origin.z + distance * ray->direction.z;
		if (intersect->z >= (((*node)->center.z - size) >> 1)
				&& intersect->z <= (((*node)->center.z + size) >> 1))
		{
			ray->length += distance;
			*node = find_node_to_go_parent(*intersect, *node, 1, origin);
			if (*node == NULL)
				return (-2);
			if ((*node)->leaf == FULL || (*node)->leaf == BREAKABLE)
				return (1);
			return (-3);
		}
	}
	return (-1);
}

int		check_y_intersect_pos(t_vec3d *intersect, t_vec3d origin, t_ray *ray
		, t_octree **node)
{
	double		distance;
	int			size;

	size = (*node)->size >> 1;
	intersect->y = ((*node)->center.y + size) >> 1;
	if ((distance = (intersect->y - origin.y)) <= 0)
		return (-1);
	distance /= ray->direction.y;
	intersect->x = origin.x + distance * ray->direction.x;
	if (intersect->x >= (((*node)->center.x - size) >> 1)
			&& intersect->x <= (((*node)->center.x + size) >> 1))
	{
		intersect->z = origin.z + distance * ray->direction.z;
		if (intersect->z >= (((*node)->center.z - size) >> 1)
				&& intersect->z <= (((*node)->center.z + size) >> 1))
		{
			ray->length += distance;
			*node = find_node_to_go_parent(*intersect, *node, 2, origin);
			if (*node == NULL)
				return (-2);
			if ((*node)->leaf == FULL || (*node)->leaf == BREAKABLE)
				return (3);
			return (-3);
		}
	}
	return (-1);
}

int		check_z_intersect_pos(t_vec3d *intersect, t_vec3d origin, t_ray *ray
		, t_octree **node)
{
	double		distance;
	int			size;

	size = (*node)->size >> 1;
	intersect->z = ((*node)->center.z + size) >> 1;
	if ((distance = (intersect->z - origin.z)) <= 0)
		return (-1);
	distance /= ray->direction.z;
	intersect->x = origin.x + distance * ray->direction.x;
	if (intersect->x >= (((*node)->center.x - size) >> 1)
			&& intersect->x <= (((*node)->center.x + size) >> 1))
	{
		intersect->y = origin.y + distance * ray->direction.y;
		if (intersect->y >= (((*node)->center.y - size) >> 1)
				&& intersect->y <= (((*node)->center.y + size) >> 1))
		{
			ray->length += distance;
			*node = find_node_to_go_parent(*intersect, *node, 3, origin);
			if (*node == NULL)
				return (-2);
			if ((*node)->leaf == FULL || (*node)->leaf == BREAKABLE)
				return (5);
			return (-3);
		}
	}
	return (-1);
}
