/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_of_sight.c                                    :+:      :+:    :+:   */
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

static int		line_of_sight_intersection(t_ray *ray, const t_doom *const data)
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
		else if (ray->face >= 0)
			return (1);
		else
			return (-5);
	}
	return (0);
}

t_hit			*line_of_sight(const t_camera camera, const t_doom *const data)
{
	t_hit		*line;
	int			ret;

	if (!(line = (t_hit*)malloc(sizeof(t_hit))))
		return (NULL);
	bullet->origin = camera.origin;
	bullet->direction = camera.direction;
	bullet->node = find_actual_position(&camera.origin, data->octree);
	bullet->find_parent[0] = &find_parent_x;
	bullet->find_parent[1] = &find_parent_y;
	bullet->find_parent[2] = &find_parent_z;
	ret = line_of_sight_intersection(bullet, data);
	if (ret == 0)
		printf("Skyblock");
	else
		printf("c'est     %d\n", ret);
	return (NULL);
}
