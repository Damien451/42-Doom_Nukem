/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lights.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 22:24:05 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/16 16:35:36 by roduquen         ###   ########.fr       */
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
	return ((1.0 - length / data->power[light->type])
			* compute_normal(ray.direction, ray.normal));
}

double		compute_light_power_player(t_ray ray, double length
		, const t_doom *const data, double coef)
{
	return (coef * (1.0 - length / data->power[PLAYER])
			* compute_normal(ray.direction, ray.normal));
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
		if ((ray.mini = data->map_to_save[ray.node->center.x >> 1][ray.node->center.y >> 1][ray.node->center.z >> 1]) > 42)
		{
			if (floor(ray.origin.x) == ray.origin.x || floor(ray.origin.y) == ray.origin.y || floor(ray.origin.z) == ray.origin.z)
			{
				ray2 = ray;
				ray2.mini -= 43;
				if (ray_intersect_mini2(&ray2, data, sorted))
					return (0);
			}
		}
	}
	i = 0;
	while (i < 3)
	{
		ray.face = data->check_intersect[sorted[i]](&ray.intersect, ray.origin
				, &ray, &ray.node);
		if (ray.length * ray.length >= length)
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
					ray2.mini = -1000;
					if (hit_cylinder(&ray2, data) != 200)
						return (0);
				}
				if ((ray.mini = data->map_to_save[ray.node->center.x >> 1][ray.node->center.y >> 1][ray.node->center.z >> 1]) > 42)
				{
					ray2 = ray;
					ray2.mini -= 43;
					if (ray_intersect_mini2(&ray2, data, sorted))
						return (0);
				}
			}
		}
		else if (ray.face >= 0)
			return (0);
		else
			return (compute_light_power(ray, length, data, light));
	}
	return (0);
}

double		launch_ray_to_light_player(t_ray ray, t_light *light
		, const t_doom *const data)
{
	double			length;
	int				i;
	int				sorted[3];
	t_ray			ray2;
	double			power;

	if (data->check_light_view[ray.face](ray.origin, light->position))
		return (0);
	if ((length = vec3d_length2(vec3d_sub(light->position, ray.origin)))
			> data->power[light->type])
		return (0);
	ray.length = 0;
	ray.direction = vec3d_unit(vec3d_sub(light->position, ray.origin));
	if ((power = -vec3d_dot(vec3d_unit(data->oriented_light), ray.direction)) < 0.950)
		return (0);
	else if (power < 0.960)
	{
		power -= 0.950;
		power /= 0.01;
	}
	else
		power = 1;
	max_absolute_between_three(ray.direction, sorted);
	if (ray.node->leaf == BREAKABLE)
	{
		if ((ray.mini = data->map_to_save[ray.node->center.x >> 1][ray.node->center.y >> 1][ray.node->center.z >> 1]) > 42)
		{
			if (floor(ray.origin.x) == ray.origin.x || floor(ray.origin.y) == ray.origin.y || floor(ray.origin.z) == ray.origin.z)
			{
				ray2 = ray;
				ray2.mini -= 43;
				if (ray_intersect_mini2(&ray2, data, sorted))
					return (0);
			}
		}
	}
	i = 0;
	while (i < 3)
	{
		ray.face = data->check_intersect[sorted[i]](&ray.intersect, ray.origin
				, &ray, &ray.node);
		if (ray.length * ray.length >= length)
			return (compute_light_power_player(ray, length, data, power));
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
					ray2.mini = -1000;
					if (hit_cylinder(&ray2, data) != 200)
						return (0);
				}
				if ((ray.mini = data->map_to_save[ray.node->center.x >> 1][ray.node->center.y >> 1][ray.node->center.z >> 1]) > 42)
				{
					ray2 = ray;
					ray2.mini -= 43;
					if (ray_intersect_mini2(&ray2, data, sorted))
						return (0);
				}
			}
		}
		else if (ray.face >= 0)
			return (0);
		else
			return (compute_light_power_player(ray, length, data, power));
	}
	return (0);
}
