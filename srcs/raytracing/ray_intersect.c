/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:42:40 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/15 15:30:13 by roduquen         ###   ########.fr       */
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

	ray.length = launch_ray_to_light(ray, data->player_light, data);
	if (ray.length >= 0.875)
		return (ray.color);
	ray.length += launch_ray_to_light(ray, data->sun_light, data);
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
			i = 0;
		}
		else if (ray.face >= 0)
		{
			if (!(ray.length < data->zbuf.zdist[ray.pos[1] + ray.pos[0] * WIDTH] || data->zbuf.zdist[ray.pos[0] + ray.pos[1] * WIDTH] == 0))
				return (data->zbuf.zcolor[ray.pos[1] + ray.pos[0] * WIDTH]);
			else 
				return (compute_lights(ray, data, tmp));
		}
		else
			return (add_skybox(ray.intersect, data->skybox));
	}
	return (0);
}
