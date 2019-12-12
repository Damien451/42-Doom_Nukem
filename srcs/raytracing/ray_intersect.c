/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:42:40 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/12 16:55:54 by roduquen         ###   ########.fr       */
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

unsigned int		compute_lights(t_ray ray, const t_doom *const data
	, t_octree *node)
{
	t_light		*light;
	t_vec3d		previous;

	ray.node = node;
	ray.origin = ray.intersect;
	ray.color = data->add_texture[ray.face](ray.origin, data);
	ray.black = (ray.color & 0xF8F8F8) >> 3;
	ray.normal = data->normal[ray.face];
	previous = ray.intersect;
	if (ray.face == 0)
		previous.x -= 1;
	else if (ray.face == 2)
		previous.y -= 1;
	else if (ray.face == 4)
		previous.z -= 1;
	data->player_light->position = data->player.camera.origin;
	ray.length = launch_ray_to_light(ray, data->player_light, data);
	if (ray.length >= 0.875)
		return (ray.color);
	ray.length += launch_ray_to_light(ray, data->sun_light, data);
	if (ray.length >= 0.875)
		return (ray.color);
	if (data->light_array[(int)previous.x][(int)previous.y][(int)previous.z].type >= 2)
	{
		light = data->light_array[(int)previous.x][(int)previous.y][(int)previous.z].next;
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

unsigned int		ray_intersect(t_ray ray, const t_doom *const data)
{
	int				sorted[3];
	int				i;
	t_octree		*tmp;
	unsigned int	j;

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
			if ((j = print_octree(ray.intersect)))
				return (j);
			tmp = ray.node;
			ray.origin = ray.intersect;
			i = 0;
		}
		else if (ray.face >= 0)
		{
			return (compute_lights(ray, data, tmp));
		}
		else
			return (add_skybox(ray.intersect, data->skybox));
	}
	return (0);
}
