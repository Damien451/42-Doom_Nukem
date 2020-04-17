/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:42:40 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/01 21:17:01 by dacuvill         ###   ########.fr       */
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

double			launch_rays_to_lights(t_ray ray, const t_doom *const data)
{
	t_light	*light;

	ray.length = launch_ray_to_light_player(ray, &data->player_light, data);
	if (ray.length >= 0.875)
		return (1);
	ray.length += launch_ray_to_light(ray, &data->sun_light, data);
	if (ray.length >= 0.875)
		return (1);
	if (data->light_array[(int)ray.origin.x][(int)ray.origin.y]
		[(int)ray.origin.z].type >= 2)
	{
		light = data->light_array[(int)ray.origin.x][(int)ray.origin.y]
			[(int)ray.origin.z].next;
		while (light)
		{
			ray.length += launch_ray_to_light(ray, light, data);
			if (ray.length >= 0.875)
				return (1);
			light = light->next;
		}
	}
	return (ray.length);
}

unsigned int	compute_lights(t_ray ray, const t_doom *const data
	, t_octree *node)
{
	ray.node = node;
	ray.origin = ray.intersect;
	ray.color = data->add_texture[ray.face](ray.origin, data);
	if (data->lib.cam_keys & BEST_SAMPLING)
		return ((ray.color & 0xFCFCFC) >> 2);
	ray.black = (ray.color & 0xF8F8F8) >> 3;
	ray.normal = data->normal[ray.face];
	ray.length = launch_rays_to_lights(ray, data);
	if (ray.length == 1)
		return (ray.color);
	return (compute_color(ray));
}

static int		cylinder_and_sphere_color(t_ray *ray)
{
	ray->color |= (ray->color << 16) | (ray->color << 8);
	return (1);
}

static int		compute_next_octant_intersect(t_ray *ray
	, const t_doom *const data, int sorted[3], t_octree **tmp)
{
	*tmp = ray->node;
	ray->origin = ray->intersect;
	if (ray->node->leaf == BREAKABLE)
	{
		if (data->map_to_save[ray->node->center.x >> 1]
			[ray->node->center.y >> 1][ray->node->center.z >> 1] == 41)
			if (hit_sphere(ray, data) != 200)
				return (cylinder_and_sphere_color(ray));
		if (data->map_to_save[ray->node->center.x >> 1]
			[ray->node->center.y >> 1][ray->node->center.z >> 1] == 42)
			if (hit_cylinder(ray, data) != 200)
				return (cylinder_and_sphere_color(ray));
		if ((ray->mini = data->map_to_save[ray->node->center.x >> 1]
			[ray->node->center.y >> 1][ray->node->center.z >> 1]) > 42)
		{
			ray->mini -= 43;
			if ((ray->color = ray_intersect_mini(ray, data, sorted)))
				return (1);
		}
	}
	return (0);
}

unsigned int	ray_intersect(t_ray ray, const t_doom *const data)
{
	int				sorted[3];
	int				i;
	t_octree		*tmp;

	max_absolute_between_three(ray.direction, sorted);
	tmp = ray.node;
	i = 0;
	while (i < 3)
	{
		ray.face = data->check_intersect[sorted[i]](&ray.intersect, ray.origin
				, &ray, &ray.node);
		if (ray.face == -1)
			i++;
		else if (ray.face == -3 && !(i = 0)
			&& compute_next_octant_intersect(&ray, data, sorted, &tmp))
			return (ray.color);
		else if (ray.face >= 0)
			return (compute_lights(ray, data, tmp));
		else if (ray.face != -3)
			return (add_skybox(ray.intersect, data));
	}
	return (0);
}
