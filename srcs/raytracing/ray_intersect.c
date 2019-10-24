/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:42:40 by roduquen          #+#    #+#             */
/*   Updated: 2019/10/24 18:49:44 by roduquen         ###   ########.fr       */
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
	//	return (0);
		return (tabl[0][a * 512 + b]);
	}
	else if (intersect.x == 0.0)
	{
		percent_a = (64.0 - intersect.y) * 8.0;
		percent_b = (64.0 - intersect.z) * 8.0;
		a = percent_a;
		b = percent_b;
	//	return (0xFFFFFF);
		return (tabl[2][a * 512 + b]);
	}
	else if (intersect.y == 64.0)
	{
		percent_a = intersect.x * 8.0;
		percent_b = intersect.z * 8.0;
		a = percent_a;
		b = percent_b;
	//	return (0xFF);
		return (tabl[4][a * 512 + b]);
	}
	else if (intersect.y == 0.0)
	{
		percent_a = intersect.x * 8.0;
		percent_b = intersect.z * 8.0;
		a = percent_a;
		b = percent_b;
	//	return (0x5555FF);
		return (tabl[5][a * 512 + b]);
	}
	else if (intersect.z == 64.0)
	{
		percent_a = (64.0 - intersect.y) * 8.0;
		percent_b = (64.0 - intersect.x) * 8.0;
		a = percent_a;
		b = percent_b;
	//	return (0xFF00);
		return (tabl[1][a * 512 + b]);
	}
	percent_a = (64.0 - intersect.y) * 8.0;
	percent_b = intersect.x * 8.0;
	a = percent_a;
	b = percent_b;
//	return (0x55FF55);
	return (tabl[3][a * 512 + b]);
	return (16546);
}

unsigned int		ray_intersect(t_vec3d ray, t_vec3d origin, t_octree *node, t_doom *data)
{
	int			ret;
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
//	printf("X intersect = (%.2f|%.2f|%.2f)\n", intersect.x, intersect.y, intersect.z);
	if (intersect.y >= ((node->center.y - (size / 2)) / 2) && intersect.y < ((node->center.y + (size / 2)) / 2)
			&& intersect.z >= ((node->center.z - (size / 2)) / 2) && intersect.z < ((node->center.z + (size / 2)) / 2))
	{
		if (!node->parent)
			return (add_skybox(intersect, data->lib.skybox));
		node = find_node_to_go_parent(intersect, node, 1);
		if (node->leaf == FULL)
		{
			printf("COLORED\n");
			return (0x1234567);
		}
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
//	printf("Y intersect = (%.2f|%.2f|%.2f)\n", intersect.x, intersect.y, intersect.z);
//	printf("min x = %ld, max x = %ld, min z = %ld, max z = %ld\n\n\n",  ((node->center.x - (size / 2)) / 2),  ((node->center.x + (size / 2)) / 2)
//			, ((node->center.z - (size / 2)) / 2), ((node->center.z + (size / 2)) / 2));
	if (intersect.x >= ((node->center.x - (size / 2)) / 2) && intersect.x < ((node->center.x + (size / 2)) / 2)
			&& intersect.z >= ((node->center.z - (size / 2)) / 2) && intersect.z < ((node->center.z + (size / 2)) / 2))
	{
		if (!node->parent)
			return (add_skybox(intersect, data->lib.skybox));
		node = find_node_to_go_parent(intersect, node, 2);
		if (node->leaf == FULL)
		{
			printf("COLORED\n");
			return (0x12345678);
		}
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
//	printf("Z intersect = (%.2f|%.2f|%.2f)\n\n\n", intersect.x, intersect.y, intersect.z);
	if (intersect.x >= ((node->center.x - (size / 2)) / 2) && intersect.x < ((node->center.x + (size / 2)) / 2)
			&& intersect.y >= ((node->center.y - (size / 2)) / 2) && intersect.y < ((node->center.y + (size / 2)) / 2))
	{
		if (!node->parent)
			return (add_skybox(intersect, data->lib.skybox));
		node = find_node_to_go_parent(intersect, node, 3);
		if (node->leaf == FULL)
		{
			printf("COLORED\n");
			return (0x12345678);
		}
		return (ray_intersect(ray, origin, node, data));
	}
	return (0);































































		/*
		   while (1)
		   {
		   test = 0;
		   if (ret == 1)
		   {
		   ret = 2;
		   intersect.x = node->center.x - (size / 2);
		   distance = intersect.x - origin.x;
		   if (distance < 0)
		   distance = -distance;
		   intersect.y = origin.y + distance * ray.y;
		   intersect.z = origin.z + distance * ray.z;
		   if (intersect.y >= ((node->center.y - size) / 2) && intersect.y < ((node->center.y + size) / 2)
		   && intersect.z >= ((node->center.z - size) / 2) && intersect.z < ((node->center.z - size) / 2))
		   {
		   if (!node->parent)
		   return (add_skybox(intersect));
		   else
		   {
		   if (node->parent->center.x == intersect.x)
		   {
		   node = find_node_to_go_neighboor(intersect, node);
		   if (node->leaf == FULL)
		   return (0x651654);
		   origin = intersect;
		   ret = max_absolute_between_three(ray.x, ray.y, ray.z);
		   test = 1;
		   }
		   else
		   {
		   node = find_node_to_go_parent(intersect, node);
		   if (node->leaf == FULL)
		   return (0x98756416);
		   origin = intersect;
		   ret = max_absolute_between_three(ray.x, ray.y, ray.z);
		   test = 1;
		   }
		   }
		   }
		   if (!test)
		   {
		   intersect.x = node->center.x + (size / 2);
		   distance = intersect.x - origin.x;
		   if (distance < 0)
		   distance = -distance;
		   intersect.y = origin.y + distance * ray.y;
		   intersect.z = origin.z + distance * ray.z;
		   if (intersect.y >= ((node->center.y - size) / 2) && intersect.y < ((node->center.y + size) / 2)
		   && intersect.z >= ((node->center.z - size) / 2) && intersect.z < ((node->center.z - size) / 2))
		   {
		   if (!node->parent)
		   return (add_skybox(intersect));
		   else
		   {
		   if (node->parent->center.x == intersect.x)
		   {
		   node = find_node_to_go_neighboor(intersect, node);
		   if (node->leaf == FULL)
		   return (0x984561);
		   origin = intersect;
		   ret = max_absolute_between_three(ray.x, ray.y, ray.z);
		   }
		   else
		   {
		   node = find_node_to_go_parent(intersect, node);
		   if (node->leaf == FULL)
		   return (0x89745132164);
		   origin = intersect;
		   ret = max_absolute_between_three(ray.x, ray.y, ray.z);
		   }
	}
	}
	}
	}
		   else if (ret == 2)
		   {
			   ret = 3;
			   intersect.y = node->center.y - (size / 2);
			   distance = intersect.y - origin.y;
			   if (distance < 0)
				   distance = -distance;
			   intersect.x = origin.x + distance * ray.x;
			   intersect.z = origin.z + distance * ray.z;
			   if (intersect.x >= ((node->center.x - size) / 2) && intersect.x < ((node->center.x + size) / 2)
					   && intersect.z >= ((node->center.z - size) / 2) && intersect.z < ((node->center.z - size) / 2))
			   {
				   if (!node->parent)
					   return (add_skybox(intersect));
				   else
				   {
					   if (node->parent->center.y == intersect.y)
					   {
						   node = find_node_to_go_neighboor(intersect, node);
						   if (node->leaf == FULL)
							   return (0x466415164849);
						   origin = intersect;
						   ret = max_absolute_between_three(ray.x, ray.y, ray.z);
						   test = 1;
					   }
					   else
					   {
						   node = find_node_to_go_parent(intersect, node);
						   if (node->leaf == FULL)
							   return (0x98465302);
						   origin = intersect;
						   ret = max_absolute_between_three(ray.x, ray.y, ray.z);
						   test = 1;
					   }
				   }
			   }
			   if (!test)
			   {
				   intersect.y = node->center.y + (size / 2);
				   distance = intersect.y - origin.y;
				   if (distance < 0)
					   distance = -distance;
				   intersect.x = origin.x + distance * ray.x;
				   intersect.z = origin.z + distance * ray.z;
				   if (intersect.x >= ((node->center.x - size) / 2) && intersect.x < ((node->center.x + size) / 2)
						   && intersect.z >= ((node->center.z - size) / 2) && intersect.z < ((node->center.z - size) / 2))
				   {
					   if (!node->parent)
						   return (add_skybox(intersect));
					   else
					   {
						   if (node->parent->center.y == intersect.y)
						   {
							   node = find_node_to_go_neighboor(intersect, node);
							   if (node->leaf == FULL)
								   return (0x98798456);
							   origin = intersect;
							   ret = max_absolute_between_three(ray.x, ray.y, ray.z);
						   }
						   else
						   {
							   node = find_node_to_go_parent(intersect, node);
							   if (node->leaf == FULL)
								   return (0x98465212302);
							   origin = intersect;
							   ret = max_absolute_between_three(ray.x, ray.y, ray.z);
						   }
					   }
				   }
			   }
		   }
		   else
		   {
			   ret = 1;
			   intersect.z = node->center.z - (size / 2);
			   distance = intersect.z - origin.z;
			   if (distance < 0)
				   distance = -distance;
			   intersect.x = origin.x + distance * ray.x;
			   intersect.y = origin.y + distance * ray.y;
			   if (intersect.x >= ((node->center.x - size) / 2) && intersect.x < ((node->center.x + size) / 2)
					   && intersect.y >= ((node->center.y - size) / 2) && intersect.y < ((node->center.y - size) / 2))
			   {
				   if (!node->parent)
					   return (add_skybox(intersect));
				   else
				   {
					   if (node->parent->center.z == intersect.z)
					   {
						   node = find_node_to_go_neighboor(intersect, node);
						   if (node->leaf == FULL)
							   return (0x7545646);
						   origin = intersect;
						   ret = max_absolute_between_three(ray.x, ray.y, ray.z);
						   test = 1;
					   }
					   else
					   {
						   node = find_node_to_go_parent(intersect, node);
						   if (node->leaf == FULL)
							   return (0x98456115);
						   origin = intersect;
						   ret = max_absolute_between_three(ray.x, ray.y, ray.z);
						   test = 1;
					   }
				   }
			   }
			   if (!test)
			   {
				   intersect.z = node->center.z + (size / 2);
				   distance = intersect.z - origin.z;
				   if (distance < 0)
					   distance = -distance;
				   intersect.x = origin.x + distance * ray.x;
				   intersect.y = origin.y + distance * ray.y;
				   if (intersect.x >= ((node->center.x - size) / 2) && intersect.x < ((node->center.x + size) / 2)
						   && intersect.y >= ((node->center.y - size) / 2) && intersect.y < ((node->center.y - size) / 2))
				   {
					   if (!node->parent)
						   return (add_skybox(intersect));
					   else
					   {
						   if (node->parent->center.z == intersect.z)
						   {
							   node = find_node_to_go_neighboor(intersect, node);
							   if (node->leaf == FULL)
								   return (0x8945161212);
							   origin = intersect;
							   ret = max_absolute_between_three(ray.x, ray.y, ray.z);
						   }
						   else
						   {
							   node = find_node_to_go_parent(intersect, node);
							   if (node->leaf == FULL)
								   return (0x56126310231);
							   origin = intersect;
							   ret = max_absolute_between_three(ray.x, ray.y, ray.z);
						   }
					   }
				   }
			   }
		   }
	}
	*/
	}
