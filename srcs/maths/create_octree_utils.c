/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_octree_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:19:56 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/03 15:10:47 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "vec3.h"
#include "octree.h"
#include <math.h>
#include "libft.h"

int		inside_loopb(t_doom *data, t_octree *node, int *nbr_node
	, t_vec3l tester)
{
	t_vec3l		count;
	char		c;

	count.x = -1;
	while (++count.x < node->size >> 1 && (count.y = -1))
	{
		while (++count.y < node->size >> 1 && (count.z = -1))
		{
			while (++count.z < node->size >> 1)
			{
				if (((c = data->map_to_save[tester.x + count.x][tester.y +
					count.y][tester.z + count.z]) >= 41) && node->size >> 1 > 1)
					return (-1);
				else if (c >= 41)
					return (-2);
				else if (c)
					(*nbr_node)++;
				else if (*nbr_node)
					return (-1);
				data->tmp++;
			}
		}
	}
	return (0);
}
