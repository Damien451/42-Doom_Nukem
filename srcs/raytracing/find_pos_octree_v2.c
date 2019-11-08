/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   locate_in_octree.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:59:25 by roduquen          #+#    #+#             */
/*   Updated: 2019/11/03 05:02:51 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "octree.h"

static inline int	*on_x_higher_than_middle(t_vec3d *position
	, t_vec3d *centeri, double size)
{
	if (position->y < (double)(center->y >> 1))
	{
		center->y -= (size);
		if (position->z < (double)(center->z >> 1))
		{
			center->z -= (size);
			return (6);
		}
		else
		{
			center->z += size;
			return (2);
		}
	}
	else
	{
		center->y += (size);
		if (position->z < (double)(node->center->z >> 1))
		{
			center->z -= (size);
			return (4);
		}
		else
		{
			center->z += size;
			return (0);
		}
	}
}

static inline int	*on_x_lower_than_middle(t_vec3d *position
		, t_vec3d *center, double size)
{
	if (position->y < (double)(center->y >> 1))
	{
		center->y -= (size);
		if (position->z < (double)(center->z >> 1))
		{
			center->z -= (size);
			return (7);
		}
		else
		{
			center->z += size;
			return (3);
		}
	}
	else
	{
		center->y += (size);
		if (position->z < (double)(node->center->z >> 1))
		{
			center->z -= (size);
			return (5);
		}
		else
		{
			center->z += size;
			return (1);
		}
	}
}

int				find_ac_position(t_vec3d *position, unsigned int *octree_v2, int *value)
{
	t_vec3d		center;
	double		size;
	int			new;
	int			i;
	int			j;
	int			count;

	center = vec3d(64, 64, 64);
	i = 1;
	size = 32;
	while (1)
	{
		if (position->x < (double)(center.x >> 1))
			j = on_x_lower_than_middle(position, &center, size);
		else
			j = on_x_higher_than_middle(position, &center, size);
		new = (INSIDE << (4 * j));
		if ((new & octree_v2[i]) >> (4 * j) == INSIDE)
		{
			new = 0;
			count = 1;
			j = 7 - j;
			while (new <= j)
			{
				if (((EMPTY << (4 * new)) & octree_v2[i]) >> (4 * new) != EMPTY)
					count++;
				new++;
			}
			i = octree_v2[i + count];
		}
		else
		{
			*value = 7 - j;
			printf("INT center = (%.2f|%.2f|%.2f)\n", center.x, center.y, center.z);
			return (i);
		}
		size /= 2;
	}
	return (0);
}
