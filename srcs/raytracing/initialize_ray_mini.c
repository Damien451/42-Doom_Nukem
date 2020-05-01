/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_ray_mini.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:42:40 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/01 22:52:38 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "octree.h"

void			initialize_rays_and_position(t_ray *big_ray, t_ray *ray
	, t_vec3d *position)
{
	position->x = ray->origin.x / 64.0 + floor(big_ray->origin.x);
	position->y = ray->origin.y / 64.0 + floor(big_ray->origin.y);
	position->z = ray->origin.z / 64.0 + floor(big_ray->origin.z);
	if (big_ray->intersect.x == floor(big_ray->intersect.x))
	{
		if (big_ray->direction.x < 0)
			position->x -= 1;
	}
	else if (big_ray->intersect.y == floor(big_ray->intersect.y))
	{
		if (big_ray->direction.y < 0)
			position->y -= 1;
	}
	else if (big_ray->direction.z < 0)
		position->z -= 1;
	big_ray->origin = *position;
	big_ray->intersect = *position;
}

static t_octree	*find_actual_position2(t_vec3d *position, t_octree *node)
{
	int			child;

	while (node && node->leaf != EMPTY && node->leaf != BREAKABLE)
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

t_octree		*initialize_ray_mini(t_ray *ray, t_ray *rayon
	, const t_doom *const data)
{
	rayon->direction = ray->direction;
	rayon->find_parent[0] = &find_parent_x;
	rayon->find_parent[1] = &find_parent_y;
	rayon->find_parent[2] = &find_parent_z;
	rayon->origin.x = (ray->intersect.x - floor(ray->intersect.x)) * 64.0;
	rayon->origin.y = (ray->intersect.y - floor(ray->intersect.y)) * 64.0;
	rayon->origin.z = (ray->intersect.z - floor(ray->intersect.z)) * 64.0;
	if (ray->intersect.x == floor(ray->intersect.x))
	{
		if (ray->direction.x < 0)
			rayon->origin.x = 64;
	}
	else if (ray->intersect.y == floor(ray->intersect.y))
	{
		if (ray->direction.y < 0)
			rayon->origin.y = 64;
	}
	else if (ray->direction.z < 0)
		rayon->origin.z = 64;
	rayon->node = find_actual_position2(&rayon->origin, data->octree_obj
	[ray->mini]);
	return (rayon->node);
}
