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

static void			update_for_next_octant(t_octree **tmp, t_ray *rayon, int *i)
{
	*tmp = rayon->node;
	rayon->origin = rayon->intersect;
	*i = 0;
}

unsigned int		ray_intersect_mini2(t_ray *ray, const t_doom *const data
		, int sorted[3])
{
	int			i;
	t_ray		rayon;
	t_octree	*tmp;

	if (!(tmp = initialize_ray_mini(ray, &rayon, data)))
		return (1);
	i = 0;
	while (i < 3)
	{
		rayon.face = data->check_intersect[sorted[i]](&rayon.intersect
		, rayon.origin, &rayon, &rayon.node);
		if (rayon.face == -1)
			i++;
		else if (rayon.face == -3)
			update_for_next_octant(&tmp, &rayon, &i);
		else if (rayon.face >= 0)
		{
			rayon.color = data->lib.object[ray->mini][rayon.node->center.x >> 1]
			[rayon.node->center.y >> 1][rayon.node->center.z >> 1];
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

	if (!(tmp = initialize_ray_mini(ray, &rayon, data)))
		return (1);
	i = 0;
	while (i < 3)
	{
		rayon.face = data->check_intersect[sorted[i]](&rayon.intersect
			, rayon.origin, &rayon, &rayon.node);
		if (rayon.face == -1)
			i++;
		else if (rayon.face == -3)
			update_for_next_octant(&tmp, &rayon, &i);
		else if (rayon.face >= 0)
		{
			rayon.color = data->lib.object[ray->mini][rayon.node->center.x >> 1]
				[rayon.node->center.y >> 1][rayon.node->center.z >> 1];
			return (compute_lights2(rayon, data, tmp, ray));
		}
		else
			return (0);
	}
	return (0);
}
