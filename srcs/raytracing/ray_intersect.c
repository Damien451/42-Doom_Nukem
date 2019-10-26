/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:42:40 by roduquen          #+#    #+#             */
/*   Updated: 2019/10/26 20:50:01 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include "graphic_lib.h"
#include "player.h"
#include "thread.h"
#include "octree.h"
#include <pthread.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>

void		max_absolute_between_three(double a, double b, double c, int tab[3])
{
	if (a <= b && a <= c)
	{
		if (c < b)
		{
			tab[1] = 2;
			tab[2] = 1;
		}
	}
	else if (b <= a && b <= c)
	{
		tab[0] = 1;
		tab[1] = 0;
		if (c < a)
		{
			tab[1] = 2;
			tab[2] = 0;
		}
	}
	else
	{
		tab[0] = 2;
		tab[2] = 0;
		if (a < b)
		{
			tab[1] = 0;
			tab[2] = 1;
		}
	}
}

t_octree		*find_node_to_go_neighboor(t_vec3d position, t_octree *node)
{
	if (position.x < (double)(node->center.x / 2))
	{
		if (position.y < (double)(node->center.y / 2))
		{
			if (position.z < (double)(node->center.z / 2))
				node = node->child[0];
			else
				node = node->child[4];
		}
		else
		{
			if (position.z < (double)(node->center.z / 2))
				node = node->child[2];
			else
				node = node->child[6];
		}
	}
	else
	{
		if (position.y < (double)(node->center.y / 2))
		{
			if (position.z < (double)(node->center.z / 2))
				node = node->child[1];
			else
				node = node->child[3];
		}
		else
		{
			if (position.z < (double)(node->center.z / 2))
				node = node->child[5];
			else
				node = node->child[7];
		}
	}
	if (node->leaf == INSIDE)
		return (find_node_to_go_neighboor(position, node));
	return (node);
}

t_octree	*find_node_to_go_parent(t_vec3d position, t_octree *node, int card)
{
	if (card == 1)
	{
		while (node->parent && position.x != node->center.x >> 1)
			node = node->parent;
	}
	else if (card == 2)
	{
		while (node->parent && position.y != node->center.y >> 1)
			node = node->parent;
	}
	else
	{
		while (node->parent && position.z != node->center.z >> 1)
			node = node->parent;
	}
	if (node->parent)
		return (find_node_to_go_neighboor(position, node));
	return (node);
}

unsigned int		ray_intersect(t_vec3d ray, t_vec3d origin, t_octree *node
	, t_doom *data)
{
	int		ret;
	t_vec3d	intersect;
	int		sorted[3];
	int		i;

	sorted[0] = 0;
	sorted[1] = 1;
	sorted[2] = 2;
	max_absolute_between_three(ray.x, ray.y, ray.z, sorted);
	i = 0;
	while (i < 3)
	{
		if ((ret = data->check_intersect[sorted[i]](&intersect, origin, ray
			, &node)) == 1)
			return (add_skybox(intersect));
		else if (ret == 2)
			return (add_texture(intersect));
		else if (ret == 3)
			return (ray_intersect(ray, intersect, node, data));
		i++;
	}
	return (0);
}
