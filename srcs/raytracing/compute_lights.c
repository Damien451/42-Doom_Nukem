/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lights.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/29 22:24:05 by roduquen          #+#    #+#             */
/*   Updated: 2019/11/30 18:58:20 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include "graphic_lib.h"

int			check_light_view(int face, t_vec3d position, t_vec3d light_pos)
{
	if (face == -2 && position.x < light_pos.x)
		return (1);
	if (face == -1 && position.x > light_pos.x)
		return (1);
	if (face == -4 && position.y < light_pos.y)
		return (1);
	if (face == -3 && position.y > light_pos.y)
		return (1);
	if (face == -6 && position.z < light_pos.z)
		return (1);
	if (face == -5 && position.z > light_pos.z)
		return (1);
	return (0);
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

	if (light->type == SUN)
		light->position = data->sun;
	if (check_light_view(ray.face, ray.origin, light->position))
		return (0);
	if ((length = vec3d_length2(vec3d_sub(light->position, ray.origin))) > (light->type == SUN ? 5000 : data->torch))
		return (0);
	length = 1.0 - length / (light->type == SUN ? 5000 : data->torch);
	ray.direction = vec3d_unit(vec3d_sub(light->position, ray.origin));
	max_absolute_between_three(ray.direction.x, ray.direction.y, ray.direction.z, sorted);
	i = 0;
	while (i < 3)
	{
		ray.face = data->check_intersect[sorted[i]](&ray.intersect, ray.origin
				, &ray, &ray.node);
		if (ray.face == 0)
			i++;
		else if (ray.face == 2)
		{
			ray.origin = ray.intersect;
			i = 0;
		}
		else if (ray.face < 0)
		{
			if (check_light_view(ray.face, ray.intersect, light->position))
				return (0);
			return (length * compute_normal(ray.direction, ray.normal));
		}
		else
			return (length * compute_normal(ray.direction, ray.normal));
	}
	return (0);
}
