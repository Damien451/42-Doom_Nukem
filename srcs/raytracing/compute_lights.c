/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lights.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 22:24:05 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/30 19:46:22 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include "graphic_lib.h"
#include "octree.h"

double		compute_normal(t_vec3d direction, t_vec3d normal)
{
	double		power;

	power = vec3d_dot(direction, normal);
	if (power > 1.0)
		return (1.0);
	return (power);
}

double		compute_light_power(t_ray ray, double length
		, const t_doom *const data, t_light *light)
{
	if (ray.face >= 0)
	{
		if (data->check_light_view[ray.face](ray.intersect, light->position))
			return (0);
		return ((1.0 - length / data->power[light->type])
				* compute_normal(ray.direction, ray.normal));
	}
	return ((1.0 - length / data->power[light->type])
			* compute_normal(ray.direction, ray.normal));
}

double		launch_ray_to_light2(t_ray ray, t_light *light
		, const t_doom *const data)
{
	double			length;
	int				i;
	int				sorted[3];

	if (data->check_light_view[ray.face](ray.origin, light->position))
		return (0);
	if ((length = vec3d_length2(vec3d_sub(light->position, ray.origin)))
			> data->power[light->type])
		return (0);
	ray.direction = vec3d_unit(vec3d_sub(light->position, ray.origin));
	max_absolute_between_three(ray.direction, sorted);
	ray.length = 0;
	i = 0;
	while (i < 3)
	{
		ray.face = data->check_intersect[sorted[i]](&ray.intersect, ray.origin
				, &ray, &ray.node);
		if (ray.face == -1)
			i++;
		else if (ray.face == -3 && !(i = 0))
			ray.origin = ray.intersect;
		else
			return (compute_light_power(ray, length, data, light));
	}
	return (0);
}

double		launch_ray_to_light(t_ray ray, t_light *light
		, const t_doom *const data)
{
	double			length;
	int				i;
	int				sorted[3];
	t_ray			ray2;

	if (data->check_light_view[ray.face](ray.origin, light->position))
		return (0);
	if ((length = vec3d_length2(vec3d_sub(light->position, ray.origin)))
			> data->power[light->type])
		return (0);
	ray.length = 0;
	ray.direction = vec3d_unit(vec3d_sub(light->position, ray.origin));
	max_absolute_between_three(ray.direction, sorted);
	if (ray.node->leaf == BREAKABLE)
	{
		if (data->map_to_save[ray.node->center.x >> 1][ray.node->center.y >> 1][ray.node->center.z >> 1] == 41)
			return (compute_light_power(ray, length, data, light));
	}
	i = 0;
	while (i < 3)
	{
		ray.face = data->check_intersect[sorted[i]](&ray.intersect, ray.origin
				, &ray, &ray.node);
		if (ray.length > length)
			return (compute_light_power(ray, length, data, light));
		if (ray.face == -1)
			i++;
		else if (ray.face == -3 && !(i = 0))
		{
			ray.origin = ray.intersect;
			if (ray.node->leaf == BREAKABLE)
			{
				if (data->map_to_save[ray.node->center.x >> 1][ray.node->center.y >> 1][ray.node->center.z >> 1] == 42)
				{
					ray2 = ray;
					if (ray_intersect_mini(&ray2, data, sorted))
						return (0);
				}
			}
		}
		else
			return (compute_light_power(ray, length, data, light));
	}
	return (0);
}
