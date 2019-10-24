/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:42:40 by roduquen          #+#    #+#             */
/*   Updated: 2019/10/24 21:14:25 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "player.h"
#include "thread.h"
#include "octree.h"
#include <pthread.h>
#include <math.h>

int			max_absolute_between_three(double a, double b, double c)
{
	a = a < 0 ? -a : a;
	b = b < 0 ? -b : b;
	c = c < 0 ? -c : c;
	if (a >= c && a >= b)
		return (1);
	else if (b >= a && b >= c)
		return (2);
	return (3);
}

t_octree	 *find_node_to_go_neighboor(t_vec3d position, t_octree *node)
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

t_octree	 *find_node_to_go_parent(t_vec3d position, t_octree *node, int card)
{
	node = node->parent;
	if (card == 1)
	{
		while (node->parent)
		{
			if (position.x == (node->center.x - (node->size / 2)) / 2 || position.x == (node->center.x + (node->size / 2)) / 2)
				node = node->parent;
		}
	}
	else if (card == 2)
	{
		while (node->parent)
		{
			if (position.y == (node->center.y - (node->size / 2)) / 2 || position.y == (node->center.y + (node->size / 2)) / 2)
				node = node->parent;
		}
	}
	else
	{
		while (node->parent)
		{
			if (position.z == (node->center.z - (node->size / 2)) / 2 || position.z == (node->center.z + (node->size / 2)) / 2)
				node = node->parent;
		}
	}
	if (node->parent)
		return (find_node_to_go_neighboor(position, node));
	return (node);
}

#include <fcntl.h>
#include <unistd.h>

unsigned int		add_skybox(t_vec3d intersect, SDL_Surface *skybox[6])
{
	double		percent_a;
	double		percent_b;
	int			a;
	int			b;
	int			fd;
	static unsigned int	tabl[6][512 * 512];

	if (tabl[0][0] == 0)
	{
		fd = open("test.binary", O_RDONLY);
		read(fd, tabl[0], 512*512*4);
		close(fd);
		fd = open("test2.binary", O_RDONLY);
		read(fd, tabl[1], 512*512*4);
		close(fd);
		fd = open("test3.binary", O_RDONLY);
		read(fd, tabl[2], 512*512*4);
		close(fd);
		fd = open("test4.binary", O_RDONLY);
		read(fd, tabl[3], 512*512*4);
		close(fd);
		fd = open("test5.binary", O_RDONLY);
		read(fd, tabl[4], 512*512*4);
		close(fd);
		fd = open("test6.binary", O_RDONLY);
		read(fd, tabl[5], 512*512*4);
		close(fd);
	}
	if (intersect.x == 64.0)
	{
		percent_a = (64.0 - intersect.y) * 8.0;
		percent_b = intersect.z * 8.0;
		a = percent_a;
		b = percent_b;
		return (tabl[0][a * 512 + b]);
	}
	else if (intersect.x == 0.0)
	{
		percent_a = (64.0 - intersect.y) * 8.0;
		percent_b = (64.0 - intersect.z) * 8.0;
		a = percent_a;
		b = percent_b;
		return (tabl[2][a * 512 + b]);
	}
	else if (intersect.y == 64.0)
	{
		percent_a = intersect.x * 8.0;
		percent_b = intersect.z * 8.0;
		a = percent_a;
		b = percent_b;
		return (tabl[4][a * 512 + b]);
	}
	else if (intersect.y == 0.0)
	{
		percent_a = intersect.x * 8.0;
		percent_b = intersect.z * 8.0;
		a = percent_a;
		b = percent_b;
		return (tabl[5][a * 512 + b]);
	}
	else if (intersect.z == 64.0)
	{
		percent_a = (64.0 - intersect.y) * 8.0;
		percent_b = (64.0 - intersect.x) * 8.0;
		a = percent_a;
		b = percent_b;
		return (tabl[1][a * 512 + b]);
	}
	percent_a = (64.0 - intersect.y) * 8.0;
	percent_b = intersect.x * 8.0;
	a = percent_a;
	b = percent_b;
	return (tabl[3][a * 512 + b]);
}

unsigned int		ray_intersect(t_vec3d ray, t_vec3d origin, t_octree *node, t_doom *data)
{
	t_vec3d		intersect;
	double		distance;
	int			size;

	size = node->size;
//	ret = max_absolute_between_three(ray.x, ray.y, ray.z);
	intersect.x = (node->center.x - (size / 2)) / 2;
	distance = (intersect.x - origin.x) / ray.x;
	if (distance < 0)
	{
		intersect.x = (node->center.x + (size / 2)) / 2;
		distance = (intersect.x - origin.x) / ray.x;
	}
	intersect.y = origin.y + distance * ray.y;
	intersect.z = origin.z + distance * ray.z;
	if (intersect.y >= ((node->center.y - (size / 2)) / 2) && intersect.y < ((node->center.y + (size / 2)) / 2)
			&& intersect.z >= ((node->center.z - (size / 2)) / 2) && intersect.z < ((node->center.z + (size / 2)) / 2))
	{
		if (!node->parent)
			return (add_skybox(intersect, data->lib.skybox));
		node = find_node_to_go_parent(intersect, node, 1);
		if (node->leaf == FULL)
			return (0x1234567);
		return (ray_intersect(ray, origin, node, data));
	}
	intersect.y = (node->center.y - (size / 2)) / 2;
	distance = (intersect.y - origin.y) / ray.y;
	if (distance < 0)
	{
		intersect.y = (node->center.y + (size / 2)) / 2;
		distance = (intersect.y - origin.y) / ray.y;
	}
	intersect.x = origin.x + distance * ray.x;
	intersect.z = origin.z + distance * ray.z;
	if (intersect.x >= ((node->center.x - (size / 2)) / 2) && intersect.x < ((node->center.x + (size / 2)) / 2)
			&& intersect.z >= ((node->center.z - (size / 2)) / 2) && intersect.z < ((node->center.z + (size / 2)) / 2))
	{
		if (!node->parent)
			return (add_skybox(intersect, data->lib.skybox));
		node = find_node_to_go_parent(intersect, node, 2);
		if (node->leaf == FULL)
			return (0x12345678);
		return (ray_intersect(ray, origin, node, data));
	}
	intersect.z = (node->center.z - (size / 2)) / 2;
	distance = (intersect.z - origin.z) / ray.z;
	if (distance < 0)
	{
		intersect.z = (node->center.z + (size / 2)) / 2;
		distance = (intersect.z - origin.z) / ray.z;
	}
	intersect.x = origin.x + distance * ray.x;
	intersect.y = origin.y + distance * ray.y;
	if (intersect.x >= ((node->center.x - (size / 2)) / 2) && intersect.x < ((node->center.x + (size / 2)) / 2)
			&& intersect.y >= ((node->center.y - (size / 2)) / 2) && intersect.y < ((node->center.y + (size / 2)) / 2))
	{
		if (!node->parent)
			return (add_skybox(intersect, data->lib.skybox));
		node = find_node_to_go_parent(intersect, node, 3);
		if (node->leaf == FULL)
			return (0x12345678);
		return (ray_intersect(ray, origin, node, data));
	}
	return (0);
}
