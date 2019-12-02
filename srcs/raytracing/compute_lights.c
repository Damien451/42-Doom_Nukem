/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lights.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 22:24:05 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/02 09:45:49 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include "graphic_lib.h"

double		compute_normal(t_vec3d direction, t_vec3d normal)
{
	double		power;

	power = vec3d_dot(direction, normal);
	if (power > 1.0)
		return (1.0);
	return (power);
}

double		compute_light_power(t_ray ray, double length, t_vec3d position
	, const t_doom *const data, int power)
{
	if (ray.face >= 0)
	{
		if (data->check_light_view[ray.face](ray.intersect, position))
			return (0);
		return ((1.0 - length / power) * compute_normal(ray.direction
					, ray.normal));
	}
	return ((1.0 - length / power) * compute_normal(ray.direction
				, ray.normal));
}

double		launch_ray_to_light(t_ray ray, t_light *light
	, const t_doom *const data)
{
	double			length;
	int				i;
	int				sorted[3];

	if (data->check_light_view[ray.face](ray.origin, light->position))
		return (0);
	if ((length = vec3d_length2(vec3d_sub(light->position, ray.origin)))
			> data->torch)
		return (0);
	ray.direction = vec3d_unit(vec3d_sub(light->position, ray.origin));
	max_absolute_between_three(ray.direction.x, ray.direction.y
			, ray.direction.z, sorted);
	i = 0;
	while (i < 3)
	{
		ray.face = data->check_intersect[sorted[i]](&ray.intersect, ray.origin
				, &ray, &ray.node);
		if (ray.face == -1)
			i++;
		else if (ray.face == -3)
		{
			ray.origin = ray.intersect;
			i = 0;
		}
		else
			return (compute_light_power(ray, length, light->position, data, data->torch));
	}
	return (0);
}

double		launch_ray_to_sun(t_ray ray, const t_doom *const data)
{
	double			length;
	int				i;
	int				sorted[3];

	if (data->check_light_view[ray.face](ray.origin, data->sun))
		return (0);
	if ((length = vec3d_length2(vec3d_sub(data->sun, ray.origin))) > 5000)
		return (0);
	ray.direction = vec3d_unit(vec3d_sub(data->sun, ray.origin));
	max_absolute_between_three(ray.direction.x, ray.direction.y, ray.direction.z
			, sorted);
	i = 0;
	while (i < 3)
	{
		ray.face = data->check_intersect[sorted[i]](&ray.intersect, ray.origin
				, &ray, &ray.node);
		if (ray.face == -1)
			i++;
		else if (ray.face == -3)
		{
			ray.origin = ray.intersect;
			i = 0;
		}
		else
			return (compute_light_power(ray, length, data->sun, data, 5000));
	}
	return (0);
}
