/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullet_intersection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smokhtar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:33:38 by smokhtar          #+#    #+#             */
/*   Updated: 2020/01/30 14:33:41 by smokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "weapons.h"
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

static int		bullet_intersect(t_ray *ray, const t_doom *const data)
{
	int				sorted[3];
	int				i;

	max_absolute_between_three(ray->direction, sorted);
	i = 0;
	while (i < 3)
	{
		ray->face = data->check_intersect[sorted[i]](&ray->intersect,
			ray->origin, ray, &ray->node);
		if (ray->face == -1)
			i++;
		else if (ray->face == -3)
		{
			ray->origin = ray->intersect;
			if (ray->node->leaf == BREAKABLE)
			{
				if (hit_cylinder(ray, data) != 200)
					return (-4);
			}
			i = 0;
		}
		return (1);
	}
	return (0);
}

t_ray			*send_bullet(const t_camera camera, const t_doom *const data)
{
	t_ray		*bullet;

	if (!(bullet = (t_ray*)malloc(sizeof(t_ray))))
		return (NULL);
	bullet->origin = camera.origin;
	bullet->direction = camera.direction;
	bullet->node = find_actual_position(&camera.origin, data->octree);
	bullet->find_parent[0] = &find_parent_x;
	bullet->find_parent[1] = &find_parent_y;
	bullet->find_parent[2] = &find_parent_z;
	if ((bullet_intersect(bullet, data) == 1))
		return (bullet);
	return (NULL);
}
