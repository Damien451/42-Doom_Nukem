/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 22:24:05 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/01 20:56:39 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include "graphic_lib.h"
#include "octree.h"

int				compute_next_octant(t_ray *ray, const t_doom *const data
	, int sorted[3])
{
	t_ray	ray2;

	ray->origin = ray->intersect;
	if (ray->node->leaf == BREAKABLE)
	{
		if (data->map_to_save[ray->node->center.x >> 1]
				[ray->node->center.y >> 1][ray->node->center.z >> 1] == 42)
		{
			ray2 = *ray;
			ray2.mini = -1000;
			if (hit_cylinder(&ray2, data) != 200)
				return (0);
		}
		if ((ray->mini = data->map_to_save[ray->node->center.x >> 1]
					[ray->node->center.y >> 1][ray->node->center.z >> 1]) > 42)
		{
			ray2 = *ray;
			ray2.mini -= 43;
			if (ray_intersect_mini2(&ray2, data, sorted))
				return (0);
		}
	}
	return (1);
}

int				shadow_mini(t_ray *ray, const t_doom *const data, int sorted[3])
{
	t_ray	ray2;

	if ((ray->mini = data->map_to_save[ray->node->center.x >> 1]
				[ray->node->center.y >> 1][ray->node->center.z >> 1]) > 42)
	{
		if (floor(ray->origin.x) == ray->origin.x || floor(ray->origin.y)
				== ray->origin.y || floor(ray->origin.z) == ray->origin.z)
		{
			ray2 = *ray;
			ray2.mini -= 43;
			if (ray_intersect_mini2(&ray2, data, sorted))
				return (0);
		}
	}
	return (1);
}

unsigned int	compute_color(t_ray ray)
{
	ray.c_color[2] = ((ray.color >> 16) & 255) * ray.length;
	ray.c_color[1] = ((ray.color >> 8) & 255) * ray.length;
	ray.c_color[0] = ((ray.color) & 255) * ray.length;
	return (ray.black + *((unsigned int*)&ray.c_color));
}
