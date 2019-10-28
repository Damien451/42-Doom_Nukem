/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:42:40 by roduquen          #+#    #+#             */
/*   Updated: 2019/10/28 09:03:43 by roduquen         ###   ########.fr       */
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
		return ;
	}
	if (b <= a && b <= c)
	{
		tab[0] = 1;
		tab[1] = 0;
		if (c < a)
		{
			tab[1] = 2;
			tab[2] = 0;
		}
		return ;
	}
	tab[0] = 2;
	tab[2] = 0;
	if (a < b)
	{
		tab[1] = 0;
		tab[2] = 1;
	}
}

t_octree		*find_node_to_go_neighboor(t_vec3d position, t_octree *node)
{
	while (node->leaf == INSIDE)
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
					node = node->child[5];
			}
			else
			{
				if (position.z < (double)(node->center.z / 2))
					node = node->child[3];
				else
					node = node->child[7];
			}
		}
	}
	return (node);
}

t_octree	*find_node_to_go_parent(t_vec3d position, t_octree *node, int card
		, t_vec3d origin)
{
	static int	i = 0;

	if (card == 1)
	{
		while (node && position.x != node->center.x / 2.0)
			node = node->parent;
		if (origin.x <= position.x)
			position.x += 0.5;
		else
			position.x -= 0.5;
		position.y = floor(position.y) + 0.5;
		position.z = floor(position.z) + 0.5;
	}
	else if (card == 2)
	{
		while (node && position.y != node->center.y / 2.0)
			node = node->parent;
		if (origin.y <= position.y)
			position.y += 0.5;
		else
			position.y -= 0.5;
		position.x = floor(position.x) + 0.5;
		position.z = floor(position.z) + 0.5;
	}
	else
	{
		while (node && position.z != node->center.z / 2.0)
			node = node->parent;
		if (origin.z <= position.z)
			position.z += 0.5;
		else
			position.z -= 0.5;
		position.y = floor(position.y) + 0.5;
		position.x = floor(position.x) + 0.5;
	}
	if (node)
		return (find_node_to_go_neighboor(position, node));
	return (NULL);
}

unsigned int		ray_intersect(t_vec3d ray, t_vec3d origin, t_octree *node
		, t_doom *data)
{
	int		ret;
	t_vec3d	intersect;
	int		sorted[3];
	int		i;
	static int	lol = 0;
	static int	sky = 0;

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
			return (add_texture(intersect, node));
		else if (ret == 3)
		{
			origin = intersect;
			i = -1;
		}
		i++;
	}
	return (0);
}
