/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   line_of_sight.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/30 14:33:38 by smokhtar          #+#    #+#             */
/*   Updated: 2020/02/20 17:20:26 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"
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
			return (ray->face);
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
	if (!(line->ray = (t_ray*)malloc(sizeof(t_ray))))
		return (NULL);
	line->ray->origin = camera.origin;
	line->ray->direction = camera.direction;
	line->ray->node = find_actual_position(&camera.origin, data->octree);
	line->ray->find_parent[0] = &find_parent_x;
	line->ray->find_parent[1] = &find_parent_y;
	line->ray->find_parent[2] = &find_parent_z;
	line->face = line_of_sight_intersection(line->ray, data);
	return (line);
}
