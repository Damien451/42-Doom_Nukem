/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lights.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 22:24:05 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/01 20:24:44 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include "graphic_lib.h"

int			check_light_view_x_pos(t_vec3d position, t_vec3d light_pos)
{
	return (position.x < light_pos.x);
}

int			check_light_view_x_neg(t_vec3d position, t_vec3d light_pos)
{
	return (position.x > light_pos.x);
}

int			check_light_view_y_pos(t_vec3d position, t_vec3d light_pos)
{
	return (position.y < light_pos.y);
}

int			check_light_view_y_neg(t_vec3d position, t_vec3d light_pos)
{
	return (position.y > light_pos.y);
}

int			check_light_view_z_pos(t_vec3d position, t_vec3d light_pos)
{
	return (position.z < light_pos.z);
}

int			check_light_view_z_neg(t_vec3d position, t_vec3d light_pos)
{
	return (position.z > light_pos.z);
}

double		compute_normal(t_vec3d direction, t_vec3d normal)
{
	double		power;

	power = vec3d_dot(direction, normal);
	if (power > 1.0)
		return (1.0);
	return (power);
}

double		launch_ray_to_light(t_ray ray, t_light *light, t_doom *data)
{
	double			length;
	int				i;
	int				sorted[3];

	if (data->check_light_view[ray.face](ray.origin, light->position))
		return (0);
	if ((length = vec3d_length2(vec3d_sub(light->position, ray.origin))) > data->torch)
		return (0);
	ray.direction = vec3d_unit(vec3d_sub(light->position, ray.origin));
	max_absolute_between_three(ray.direction.x, ray.direction.y, ray.direction.z, sorted);
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
		else if (ray.face >= 0)
		{
			if (data->check_light_view[ray.face](ray.intersect, light->position))
				return (0);
			return ((1.0 - length / data->torch) * compute_normal(ray.direction, ray.normal));
		}
		else
			return ((1.0 - length / data->torch) * compute_normal(ray.direction, ray.normal));
	}
	return (0);
}

double		launch_ray_to_sun(t_ray ray, t_doom *data)
{
	double			length;
	int				i;
	int				sorted[3];

	if (data->check_light_view[ray.face](ray.origin, data->sun))
		return (0);
	if ((length = vec3d_length2(vec3d_sub(data->sun, ray.origin))) > 5000)
		return (0);
	ray.direction = vec3d_unit(vec3d_sub(data->sun, ray.origin));
	max_absolute_between_three(ray.direction.x, ray.direction.y, ray.direction.z, sorted);
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
		else if (ray.face >= 0)
		{
			if (data->check_light_view[ray.face](ray.intersect, data->sun))
				return (0);
			return ((1.0 - length / 5000) * compute_normal(ray.direction, ray.normal));
		}
		else
			return ((1.0 - length / 5000) * compute_normal(ray.direction, ray.normal));
	}
	return (0);
}
