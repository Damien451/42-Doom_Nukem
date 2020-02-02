/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:42:40 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/02 13:02:44 by roduquen         ###   ########.fr       */
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

unsigned int		compute_color(t_ray ray)
{
	ray.c_color[2] = ((ray.color >> 16) & 255) * ray.length;
	ray.c_color[1] = ((ray.color >> 8) & 255) * ray.length;
	ray.c_color[0] = ((ray.color) & 255) * ray.length;
	return (ray.black + *((unsigned int*)&ray.c_color));
}

unsigned int		launch_rays_to_lights(t_ray ray, const t_doom *const data)
{
	t_light	*light;

	ray.length = launch_ray_to_light2(ray, data->player_light, data);
	if (ray.length >= 0.875)
		return (ray.color);
	ray.length += launch_ray_to_light2(ray, data->sun_light, data);
	if (ray.length >= 0.875)
		return (ray.color);
	if (data->light_array[(int)ray.origin.x][(int)ray.origin.y]
		[(int)ray.origin.z].type >= 2)
	{
		light = data->light_array[(int)ray.origin.x][(int)ray.origin.y]
			[(int)ray.origin.z].next;
		while (light)
		{
			ray.length += launch_ray_to_light(ray, light, data);
			if (ray.length >= 0.875)
				return (ray.color);
			light = light->next;
		}
	}
	return (compute_color(ray));
}

unsigned int		compute_lights(t_ray ray, const t_doom *const data
	, t_octree *node)
{
	ray.node = node;
	ray.origin = ray.intersect;
	ray.color = data->add_texture[ray.face](ray.origin, data);
	ray.black = (ray.color & 0xF8F8F8) >> 3;
	ray.normal = data->normal[ray.face];
	data->player_light->position = data->player.camera.origin;
	return (launch_rays_to_lights(ray, data));
}

unsigned int		ray_intersect(t_ray ray, const t_doom *const data)
{
	int				sorted[3];
	int				i;
	t_octree		*tmp;
	double			length;

	max_absolute_between_three(ray.direction, sorted);
	tmp = ray.node;
	i = 0;
	while (i < 3)
	{
		ray.face = data->check_intersect[sorted[i]](&ray.intersect, ray.origin
				, &ray, &ray.node);
		if (ray.face == -1)
			i++;
		else if (ray.face == -3)
		{
			tmp = ray.node;
			ray.origin = ray.intersect;
			if (ray.node->leaf == BREAKABLE)
			{
				if (data->map_to_save[ray.node->center.x >> 1][ray.node->center.y >> 1][ray.node->center.z >> 1] == 41)
					if ((length = hit_sphere(&ray, data)) != 200)
						return ((ray.color << 16) | (ray.color << 8) | ray.color);
				if (data->map_to_save[ray.node->center.x >> 1][ray.node->center.y >> 1][ray.node->center.z >> 1] == 42)
					if ((length = hit_cylinder(&ray, data)) != 200)
						return ((ray.color << 16) | (ray.color << 8) | ray.color);
				if ((ray.mini = data->map_to_save[ray.node->center.x >> 1][ray.node->center.y >> 1][ray.node->center.z >> 1]) > 42)
				{
					ray.mini -= 43;
					if ((ray.color = ray_intersect_mini(&ray, data, sorted)))
						return (ray.color);
				//		if ((length = hit_cylinder(&ray, data)) != 200)
				//			return ((ray.color << 16) | (ray.color << 8) | ray.color);
				}
			}
			i = 0;
		}
		else if (ray.face >= 0)
			return (compute_lights(ray, data, tmp));
		else
			return (add_skybox(ray.intersect, data->skybox));
	}
	return (0);
}
