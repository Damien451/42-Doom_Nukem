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
#include "libft.h"
#include "graphic_lib.h"
#include "player.h"
#include "thread.h"
#include "octree.h"
#include "vec3.h"
#include <pthread.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>

double		launch_ray_to_light_player_mini(t_ray ray, const t_light *light
		, const t_doom *const data, t_ray *big_ray)
{
	int				i;
	int				sorted[3];
	double			power;

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

double		launch_ray_to_light_mini(t_ray ray, const t_light *light
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

unsigned int		launch_rays_to_lights_mini(t_ray ray, const t_doom *const data, t_ray *big_ray)
{
	t_light	*light;
	t_vec3d			position;

	if (big_ray->intersect.x == floor(big_ray->intersect.x))
	{
		position.y = ray.origin.y / 64.0 + floor(big_ray->origin.y);
		position.z = ray.origin.z / 64.0 + floor(big_ray->origin.z);
		if (big_ray->direction.x >= 0)
			position.x = ray.origin.x / 64.0 + floor(big_ray->origin.x);
		else
			position.x = ray.origin.x / 64.0 + floor(big_ray->origin.x) - 1;
	}
	else if (big_ray->intersect.y == floor(big_ray->intersect.y))
	{
		position.x = ray.origin.x / 64.0 + floor(big_ray->origin.x);
		position.z = ray.origin.z / 64.0 + floor(big_ray->origin.z);
		if (big_ray->direction.y >= 0)
			position.y = ray.origin.y / 64.0 + floor(big_ray->origin.y);
		else
			position.y = ray.origin.y / 64.0 + floor(big_ray->origin.y) - 1;
	}
	else
	{
		position.x = ray.origin.x / 64.0 + floor(big_ray->origin.x);
		position.y = ray.origin.y / 64.0 + floor(big_ray->origin.y);
		if (big_ray->direction.z >= 0)
			position.z = ray.origin.z / 64.0 + floor(big_ray->origin.z);
		else
			position.z = ray.origin.z / 64.0 + floor(big_ray->origin.z) - 1;
	}
	big_ray->origin = position;
	big_ray->intersect = position;
	ray.length = launch_ray_to_light_player_mini(ray, &data->player_light, data, big_ray);
	if (ray.length >= 0.75)
		return (ray.color);
	ray.length += launch_ray_to_light_mini(ray, &data->sun_light, data, big_ray);
	if (ray.length >= 0.75)
		return (ray.color);
	if (data->light_array[big_ray->node->center.x >> 1][big_ray->node->center.y >> 1][big_ray->node->center.z >> 1].type >= 2)
	{
		light = data->light_array[big_ray->node->center.x >> 1][big_ray->node->center.y >> 1][big_ray->node->center.z >> 1].next;
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

t_octree	*find_actual_position2(t_vec3d *position, t_octree *node)
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

unsigned int		ray_intersect_mini2(t_ray *ray, const t_doom *const data
		, int sorted[3])
{
	int			i;
	t_ray		rayon;
	t_octree	*tmp;

	rayon.direction = ray->direction;
	rayon.find_parent[0] = &find_parent_x;
	rayon.find_parent[1] = &find_parent_y;
	rayon.find_parent[2] = &find_parent_z;
	if (ray->intersect.x == floor(ray->intersect.x))
	{
		rayon.origin.y = (ray->intersect.y - floor(ray->intersect.y)) * 64.0;
		rayon.origin.z = (ray->intersect.z - floor(ray->intersect.z)) * 64.0;
		if (ray->direction.x >= 0)
			rayon.origin.x = 0;
		else
			rayon.origin.x = 64;
	}
	else if (ray->intersect.y == floor(ray->intersect.y))
	{
		rayon.origin.x = (ray->intersect.x - floor(ray->intersect.x)) * 64.0;
		rayon.origin.z = (ray->intersect.z - floor(ray->intersect.z)) * 64.0;
		if (ray->direction.y >= 0)
			rayon.origin.y = 0;
		else
			rayon.origin.y = 64;
	}
	else
	{
		rayon.origin.x = (ray->intersect.x - floor(ray->intersect.x)) * 64.0;
		rayon.origin.y = (ray->intersect.y - floor(ray->intersect.y)) * 64.0;
		if (ray->direction.z >= 0)
			rayon.origin.z = 0;
		else
			rayon.origin.z = 64;
	}
	rayon.node = find_actual_position2(&rayon.origin, data->octree_obj[ray->mini]);
	if (!rayon.node)
		return (1);
	tmp = rayon.node;
	i = 0;
	while (i < 3)
	{
		rayon.face = data->check_intersect[sorted[i]](&rayon.intersect, rayon.origin
				, &rayon, &rayon.node);
		if (rayon.face == -1)
			i++;
		else if (rayon.face == -3)
		{
			tmp = rayon.node;
			rayon.origin = rayon.intersect;
			i = 0;
		}
		else if (rayon.face >= 0)
		{
			rayon.color = data->lib.object[ray->mini][rayon.node->center.x >> 1][rayon.node->center.y >> 1][rayon.node->center.z >> 1];
			return (1);
		}
		else
			return (0);
	}
	return (0);
}

unsigned int		ray_intersect_mini(t_ray *ray, const t_doom *const data
		, int sorted[3])
{
	int			i;
	t_ray		rayon;
	t_octree	*tmp;

	rayon.direction = ray->direction;
	rayon.find_parent[0] = &find_parent_x;
	rayon.find_parent[1] = &find_parent_y;
	rayon.find_parent[2] = &find_parent_z;
	if (ray->intersect.x == floor(ray->intersect.x))
	{
		rayon.origin.y = (ray->intersect.y - floor(ray->intersect.y)) * 64.0;
		rayon.origin.z = (ray->intersect.z - floor(ray->intersect.z)) * 64.0;
		if (ray->direction.x >= 0)
			rayon.origin.x = 0;
		else
			rayon.origin.x = 64;
	}
	else if (ray->intersect.y == floor(ray->intersect.y))
	{
		rayon.origin.x = (ray->intersect.x - floor(ray->intersect.x)) * 64.0;
		rayon.origin.z = (ray->intersect.z - floor(ray->intersect.z)) * 64.0;
		if (ray->direction.y >= 0)
			rayon.origin.y = 0;
		else
			rayon.origin.y = 64;
	}
	else
	{
		rayon.origin.x = (ray->intersect.x - floor(ray->intersect.x)) * 64.0;
		rayon.origin.y = (ray->intersect.y - floor(ray->intersect.y)) * 64.0;
		if (ray->direction.z >= 0)
			rayon.origin.z = 0;
		else
			rayon.origin.z = 64;
	}
	rayon.node = find_actual_position2(&rayon.origin, data->octree_obj[ray->mini]);
	if (!rayon.node)
		return (1);
	tmp = rayon.node;
	i = 0;
	while (i < 3)
	{
		rayon.face = data->check_intersect[sorted[i]](&rayon.intersect, rayon.origin
				, &rayon, &rayon.node);
		if (rayon.face == -1)
			i++;
		else if (rayon.face == -3)
		{
			tmp = rayon.node;
			rayon.origin = rayon.intersect;
			i = 0;
		}
		else if (rayon.face >= 0)
		{
			rayon.color = data->lib.object[ray->mini][rayon.node->center.x >> 1][rayon.node->center.y >> 1][rayon.node->center.z >> 1];
			return (compute_lights2(rayon, data, tmp, ray));
		}
		else
			return (0);
	}
	return (0);
}
