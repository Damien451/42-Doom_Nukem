/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:42:40 by roduquen          #+#    #+#             */
/*   Updated: 2019/11/03 01:14:00 by roduquen         ###   ########.fr       */
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

static inline t_octree	*on_x_higher_than_middle(t_vec3d *position
	, t_octree *node)
{
	if (position->y < (double)(node->center.y >> 1))
	{
		if (position->z < (double)(node->center.z >> 1))
			return (node->child[1]);
		else
			return (node->child[5]);
	}
	else
	{
		if (position->z < (double)(node->center.z >> 1))
			return (node->child[3]);
		else
			return (node->child[7]);
	}
}

static inline t_octree	*on_x_lower_than_middle(t_vec3d *position
		, t_octree *node)
{
	if (position->y < (double)(node->center.y >> 1))
	{
		if (position->z < (double)(node->center.z >> 1))
			return (node->child[0]);
		else
			return (node->child[4]);
	}
	else
	{
		if (position->z < (double)(node->center.z >> 1))
			return (node->child[2]);
		else
			return (node->child[6]);
	}
}

t_octree				*find_position(t_vec3d *position, t_octree *node)
{
	while (node->leaf == INSIDE)
	{
		if (position->x < (double)(node->center.x >> 1))
			node = on_x_lower_than_middle(position, node);
		else
			node = on_x_higher_than_middle(position, node);
	}
	return (node);
}

unsigned int		ray_intersect(t_vec3d ray, t_vec3d origin, t_octree *node
		, t_doom *data)
{
	int				ret;
	t_vec3d			intersect;
	int				sorted[3];
	int				i;
	unsigned int	color;
	unsigned char	c_color[4];
	unsigned char	test_color[4];
	t_octree		*tmp;
	double			test;

	sorted[0] = 0;
	sorted[1] = 1;
	sorted[2] = 2;
	test_color[0] = 0;
	c_color[0] = 0;
	max_absolute_between_three(ray.x, ray.y, ray.z, sorted);
	i = 0;
	while (i < 3)
	{
		tmp = node;
		if ((ret = data->check_intersect[sorted[i]](&intersect, origin, ray
						, &node)) == 1)
			return (add_skybox(intersect));
		else if (ret < 0)
		{
			ray = vec3d_unit(vec3d_sub(data->light.position, intersect));
			color = add_texture(intersect, node, ret);
			c_color[1] = (color >> 16 & 255) >> 2;
			c_color[2] = (color >> 8 & 255) >> 2;
			c_color[3] = (color & 255) >> 2;
			if (ret == -2 && intersect.x < data->light.position.x)
				return (*((unsigned int*)&c_color));
			if (ret == -1 && intersect.x > data->light.position.x)
				return (*((unsigned int*)&c_color));
			if (ret == -4 && intersect.y < data->light.position.y)
				return (*((unsigned int*)&c_color));
			if (ret == -3 && intersect.y > data->light.position.y)
				return (*((unsigned int*)&c_color));
			if (ret == -6 && intersect.z < data->light.position.z)
				return (*((unsigned int*)&c_color));
			if (ret == -5 && intersect.z > data->light.position.z)
				return (*((unsigned int*)&c_color));
			if ((test = vec3d_length2(vec3d_sub(data->light.position, intersect))) > data->light.power)
				return (*((unsigned int*)&c_color));
			test_color[1] = (color >> 16 & 255) - c_color[1];
			test_color[2] = (color >> 8 & 255) - c_color[2];
			test_color[3] = (color & 255) - c_color[3];
			test = 1.0 - test / data->light.power;
			test_color[1] *= test;
			test_color[2] *= test;
			test_color[3] *= test;
			test_color[1] = c_color[1] + test_color[1];
			test_color[2] = c_color[2] + test_color[2];
			test_color[3] = c_color[3] + test_color[3];
			sorted[0] = 0;
			sorted[1] = 1;
			sorted[2] = 2;
			node = tmp;
			origin = intersect;
			max_absolute_between_three(ray.x, ray.y, ray.z, sorted);
			i = 0;
			while (i < 3)
			{
				ret = data->check_intersect[sorted[i]](&intersect, origin
						, ray, &node);
				if (ret == 1)
					return (*((unsigned int*)&test_color));
				else if (ret < 0)
				{
					if (ret == -2 && intersect.x < data->light.position.x)
						return (*((unsigned int*)&c_color));
					if (ret == -1 && intersect.x > data->light.position.x)
						return (*((unsigned int*)&c_color));
					if (ret == -4 && intersect.y < data->light.position.y)
						return (*((unsigned int*)&c_color));
					if (ret == -3 && intersect.y > data->light.position.y)
						return (*((unsigned int*)&c_color));
					if (ret == -6 && intersect.z < data->light.position.z)
						return (*((unsigned int*)&c_color));
					if (ret == -5 && intersect.z > data->light.position.z)
						return (*((unsigned int*)&c_color));
					return (*((unsigned int*)&test_color));
				}
				else if (ret == 3)
				{
					origin = intersect;
					i = -1;
				}
				i++;
			}
		}
		else if (ret == 3)
		{
			/*	if (intersect.x == floor(intersect.x) && ((intersect.y <= floor(intersect.y) + 0.05 && intersect.y >= floor(intersect.y) - 0.05) || (intersect.z <= floor(intersect.z) + 0.05 && intersect.z >= floor(intersect.z) - 0.05)))
				return (127 | 127 << 16 | 127 << 8);
				if (intersect.y == floor(intersect.y) && ((intersect.x <= floor(intersect.x) + 0.05 && intersect.x >= floor(intersect.x) - 0.05) || (intersect.z <= floor(intersect.z) + 0.05 && intersect.z >= floor(intersect.z) - 0.05)))
				return (127 | 127 << 16 | 127 << 8);
				if (intersect.z == floor(intersect.z) && ((intersect.y <= floor(intersect.y) + 0.05 && intersect.y >= floor(intersect.y) - 0.05) || (intersect.x <= floor(intersect.x) + 0.05 && intersect.x >= floor(intersect.x) - 0.05)))
				return (127 | 127 << 16 | 127 << 8);
			 */		origin = intersect;
			i = -1;
		}
		i++;
	}
	return (0);
}
