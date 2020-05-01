/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect_mini.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:42:40 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/01 22:52:38 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "octree.h"

double				launch_ray_to_light_player_mini(t_ray ray
	, const t_light *light, const t_doom *const data, t_ray *big_ray)
{
	int				i;
	int				sorted[3];

	ray.direction = vec3d_unit(vec3d_sub(light->position, big_ray->origin));
	big_ray->direction = ray.direction;
	max_absolute_between_three(ray.direction, sorted);
	i = 0;
	while (i < 3)
	{
		ray.face = data->check_intersect[sorted[i]](&ray.intersect, ray.origin
				, &ray, &ray.node);
		if (ray.face == -1)
			i++;
		else if (ray.face == -3 && !(i = 0))
			ray.origin = ray.intersect;
		else if (ray.face >= 0)
			return (0);
		else
			return (launch_ray_to_light_player(*big_ray, light, data));
	}
	return (0);
}

double				launch_ray_to_light_mini(t_ray ray, const t_light *light
		, const t_doom *const data, t_ray *big_ray)
{
	int				i;
	int				sorted[3];

	ray.direction = vec3d_unit(vec3d_sub(light->position, big_ray->origin));
	big_ray->direction = ray.direction;
	max_absolute_between_three(ray.direction, sorted);
	i = 0;
	while (i < 3)
	{
		ray.face = data->check_intersect[sorted[i]](&ray.intersect, ray.origin
				, &ray, &ray.node);
		if (ray.face == -1)
			i++;
		else if (ray.face == -3 && !(i = 0))
			ray.origin = ray.intersect;
		else if (ray.face >= 0)
			return (0);
		else
			return (launch_ray_to_light(*big_ray, light, data));
	}
	return (0);
}

unsigned int		launch_rays_to_lights_mini(t_ray ray
	, const t_doom *const data, t_ray *big_ray)
{
	t_light	*light;
	t_vec3d	position;

	initialize_rays_and_position(big_ray, &ray, &position);
	ray.length = launch_ray_to_light_player_mini(ray, &data->player_light, data
		, big_ray);
	if (ray.length >= 0.75)
		return (ray.color);
	if ((ray.length += launch_ray_to_light_mini(ray, &data->sun_light, data
		, big_ray)) >= 0.75)
		return (ray.color);
	if (data->light_array[big_ray->node->center.x >> 1]
		[big_ray->node->center.y >> 1][big_ray->node->center.z >> 1].type >= 2)
	{
		light = data->light_array[big_ray->node->center.x >> 1]
			[big_ray->node->center.y >> 1][big_ray->node->center.z >> 1].next;
		while (light)
		{
			ray.length += launch_ray_to_light_mini(ray, light, data, big_ray);
			if (ray.length >= 0.75)
				return (ray.color);
			light = light->next;
		}
	}
	return (compute_color(ray));
}

unsigned int		compute_lights2(t_ray ray, const t_doom *const data
		, t_octree *node, t_ray *big_ray)
{
	ray.node = node;
	ray.origin = ray.intersect;
	big_ray->black = (ray.color & 0xFCFCFC) >> 2;
	if (data->lib.cam_keys & BEST_SAMPLING)
		return (big_ray->black);
	ray.black = big_ray->black;
	big_ray->normal = data->normal[ray.face];
	ray.normal = data->normal[ray.face];
	big_ray->face = ray.face;
	return (launch_rays_to_lights_mini(ray, data, big_ray));
}
