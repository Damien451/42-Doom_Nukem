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

double			compute_light_power_player(t_ray ray, double length
		, const t_doom *const data, double coef)
{
	return (coef * (1.0 - length / data->power[PLAYER])
			* compute_normal(ray.direction, ray.normal));
}

static int		initialize_ray_to_light(const t_doom *const data
	, const t_light *light, t_ray *ray, int sorted[3])
{
	double		length;

	if (data->check_light_view[ray->face](ray->origin, light->position))
		return (0.0);
	if ((length = vec3d_length2(vec3d_sub(light->position, ray->origin)))
			> data->power[light->type])
		return (0.0);
	ray->length = 0.0;
	ray->direction = vec3d_unit(vec3d_sub(light->position, ray->origin));
	max_absolute_between_three(ray->direction, sorted);
	if (ray->node->leaf == BREAKABLE && !shadow_mini(ray, data, sorted))
		return (0.0);
	return (length);
}

static void		compute_power(double *power)
{
	if (*power < 0.960)
	{
		*power -= 0.950;
		*power /= 0.01;
	}
	else
		*power = 1;
}

static double	move_in_octree_player(const t_doom *const data, int sorted[3]
	, t_ray *ray, double length[2])
{
	int				i;

	i = 0;
	while (i < 3)
	{
		ray->face = data->check_intersect[sorted[i]](&ray->intersect
			, ray->origin, ray, &ray->node);
		if (ray->length * ray->length >= length[0])
		{
			return (compute_light_power_player(*ray, length[0], data
				, length[1]));
		}
		if (ray->face == -1)
			i++;
		else if (ray->face == -3 && !(i = 0) && !compute_next_octant(ray, data
			, sorted))
			return (0);
		else if (ray->face >= 0)
			return (0);
		else if (ray->face != -3)
			return (compute_light_power_player(*ray, length[0], data
				, length[1]));
	}
	return (0);
}

double			launch_ray_to_light_player(t_ray ray, const t_light *light
		, const t_doom *const data)
{
	double			length[2];
	int				sorted[3];

	if (!(length[0] = initialize_ray_to_light(data, light, &ray, sorted)))
		return (0);
	if ((length[1] = -vec3d_dot(vec3d_unit(data->oriented_light)
		, ray.direction))
			< 0.950)
		return (0);
	compute_power(&length[1]);
	return (move_in_octree_player(data, sorted, &ray, length));
}
