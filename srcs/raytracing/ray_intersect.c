/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:42:40 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/02 08:06:28 by roduquen         ###   ########.fr       */
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

void	max_absolute_between_three(double a, double b, double c, int tab[3])
{
	int		ax;
	int		bx;
	int		cx;

	ax = 0;
	bx = 1;
	cx = 2;
	if (a < 0)
	{
		a = -a;
		ax = 3;
	}
	if (b < 0)
	{
		b = -b;
		bx = 4;
	}
	if (c < 0)
	{
		c = -c;
		cx = 5;
	}
	tab[0] = ax;
	tab[1] = bx;
	tab[2] = cx;
	if (a <= b && a <= c)
	{
		if (c < b)
		{
			tab[1] = cx;
			tab[2] = bx;
		}
		return ;
	}
	if (b <= a && b <= c)
	{
		tab[0] = bx;
		tab[1] = ax;
		if (c < a)
		{
			tab[1] = cx;
			tab[2] = ax;
		}
		return ;
	}
	tab[0] = cx;
	tab[2] = ax;
	if (a < b)
	{
		tab[1] = ax;
		tab[2] = bx;
	}
}

t_octree		*find_node_to_go_neighboor(t_vec3d position, t_octree *node)
{
	int			child;

	while (node->leaf == INSIDE)
	{
		child = 0;
		if (position.x >= (double)(node->center.x >> 1))
			child |= 1;
		if (position.y >= (double)(node->center.y >> 1))
			child |= 2;
		if (position.z >= (double)(node->center.z >> 1))
			child |= 4;
		node = node->child[child];
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

unsigned int		print_octree(t_vec3d intersect)
{
	unsigned int color = 0;

	if (intersect.x == floor(intersect.x) && ((intersect.y <= floor(intersect.y)
		+ 0.05 && intersect.y >= floor(intersect.y) - 0.05)
		|| (intersect.z <= floor(intersect.z) + 0.05
		&& intersect.z >= floor(intersect.z) - 0.05)))
		color = 127 | 127 << 16 | 127 << 8;
	else if (intersect.y == floor(intersect.y) && ((intersect.x <= floor(intersect.x)
		+ 0.05 && intersect.x >= floor(intersect.x) - 0.05)
		|| (intersect.z <= floor(intersect.z) + 0.05
		&& intersect.z >= floor(intersect.z) - 0.05)))
		color = 127 | 127 << 16 | 127 << 8;
	else if (intersect.z == floor(intersect.z) && ((intersect.y <= floor(intersect.y)
		+ 0.05 && intersect.y >= floor(intersect.y) - 0.05)
		|| (intersect.x <= floor(intersect.x) + 0.05
		&& intersect.x >= floor(intersect.x) - 0.05)))
		color = 127 | 127 << 16 | 127 << 8;
	return (color);
}

unsigned int		ray_intersect(t_ray ray, const t_doom * const data)
{
	int				sorted[3];
	int				i;
	t_octree		*tmp;
	t_light			*light;

	max_absolute_between_three(ray.direction.x, ray.direction.y, ray.direction.z, sorted);
	tmp = ray.node;
	i = 0;
	while (i < 3)
	{
		ray.face = data->check_intersect[sorted[i]](&ray.intersect, ray.origin, &ray
						, &ray.node);
		if (ray.face == -1)
			i++;
		else if (ray.face == -3)
		{
	//		if ((ray.face = print_octree(ray.intersect, ray.node)))
	//			return (ray.face);
			tmp = ray.node;
			ray.origin = ray.intersect;
			i = 0;
		}
		else if (ray.face >= 0)
		{
			ray.node = tmp;
			ray.origin = ray.intersect;
			light = data->light;
			ray.color = data->add_texture[ray.face](ray.origin, data);
			ray.black = (ray.color & 0xF8F8F8) >> 3;
			ray.normal = data->normal[ray.face];
			ray.length = launch_ray_to_sun(ray, data);
			if (ray.length >= 1.0)
				return (ray.color);
			while (light)
			{
				ray.length += launch_ray_to_light(ray, light, data);
				if (ray.length >= 1.0)
					return (ray.color);
				light = light->next;
			}
			ray.c_color[2] = ((ray.color >> 16) & 255) * ray.length;
			ray.c_color[1] = ((ray.color >> 8) & 255) * ray.length;
			ray.c_color[0] = ((ray.color) & 255) * ray.length;
			return (ray.black + *((unsigned int*)&ray.c_color));
		}
		else
			return (add_skybox(ray.intersect));
	}
	return (0);
}
