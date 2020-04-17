/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lights.c                                   :+:      :+:    :+:   */
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

double			compute_normal(t_vec3d direction, t_vec3d normal)
{
	double		power;

	power = vec3d_dot(direction, normal);
	if (power > 1.0)
		return (1.0);
	return (power);
}

double			compute_light_power(t_ray ray, double length
		, const t_doom *const data, const t_light *light)
{
	return ((1.0 - length / data->power[light->type])
			* compute_normal(ray.direction, ray.normal));
}

static double	move_in_octree(const t_doom *const data, const t_light *light
	, t_ray *ray, double length)
{
	int				i;
	int				sorted[3];

	i = 0;
	max_absolute_between_three(ray->direction, sorted);
	while (i < 3)
	{
		ray->face = data->check_intersect[sorted[i]](&ray->intersect
			, ray->origin, ray, &ray->node);
		if (ray->length * ray->length >= length)
		{
			return (compute_light_power(*ray, length, data, light));
		}
		if (ray->face == -1)
			i++;
		else if (ray->face == -3 && !(i = 0) && !compute_next_octant(ray, data
			, sorted))
			return (0);
		else if (ray->face >= 0)
			return (0);
		else if (ray->face != -3)
			return (compute_light_power(*ray, length, data, light));
	}
	return (0);
}

double			launch_ray_to_light(t_ray ray, const t_light *light
		, const t_doom *const data)
{
	double			length;
	int				sorted[3];

	if (data->check_light_view[ray.face](ray.origin, light->position))
		return (0);
	if ((length = vec3d_length2(vec3d_sub(light->position, ray.origin)))
			> data->power[light->type])
		return (0);
	ray.length = 0;
	ray.direction = vec3d_unit(vec3d_sub(light->position, ray.origin));
	max_absolute_between_three(ray.direction, sorted);
	if (ray.node->leaf == BREAKABLE && !shadow_mini(&ray, data, sorted))
		return (0);
	return (move_in_octree(data, light, &ray, length));
}
