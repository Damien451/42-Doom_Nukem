/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_octree_model_utils.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:19:56 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/31 11:01:00 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "vec3.h"
#include "octree.h"
#include <math.h>
#include "libft.h"

static inline int		inside_loop(t_doom *data, t_octree *node, int *nbr_node
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
				c = data->lib.object[data->actual_obj][tester.x + count.x]
					[tester.y + count.y]
					[tester.z + count.z];
				if (c)
					(*nbr_node)++;
				else if (*nbr_node)
					return (-1);
				data->tmp++;
			}
		}
	}
	return (0);
}

int						verify_inside_node_model(t_doom *data, t_octree *node)
{
	t_vec3l		tester;
	int			ret;
	int			nbr_node;

	init_all(&tester, data, &nbr_node, node);
	ret = inside_loop(data, node, &nbr_node, tester);
	if (ret)
		return (ret);
	if (nbr_node != 0 && data->tmp != nbr_node)
		return (-1);
	return (nbr_node);
}

void					check_if_child_isleaf(t_doom *data, t_octree *node)
{
	int			i;
	int			ret;

	i = 0;
	while (i < 8)
	{
		if ((ret = verify_inside_node_model(data, node->child[i])) == 0)
			node->child[i]->leaf = EMPTY;
		else if (ret == -1)
			node->child[i]->leaf = INSIDE;
		else if (ret == -2)
			node->child[i]->leaf = BREAKABLE;
		else
			node->child[i]->leaf = FULL;
		i++;
	}
}

void					init_all(t_vec3l *tester, t_doom *data, int *nbr_node
		, t_octree *node)
{
	data->tmp = 0;
	*nbr_node = 0;
	tester->x = (node->center.x >> 1) - (node->size >> 2);
	tester->y = (node->center.y >> 1) - (node->size >> 2);
	tester->z = (node->center.z >> 1) - (node->size >> 2);
}
