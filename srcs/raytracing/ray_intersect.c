/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_intersect.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 17:42:40 by roduquen          #+#    #+#             */
/*   Updated: 2019/11/23 09:49:48 by roduquen         ###   ########.fr       */
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
		if (position.x < (double)(node->center.x >> 1))
		{
			if (position.y < (double)(node->center.y >> 1))
			{
				if (position.z < (double)(node->center.z >> 1))
					node = node->child[0];
				else
					node = node->child[4];
			}
			else
			{
				if (position.z < (double)(node->center.z >> 1))
					node = node->child[2];
				else
					node = node->child[6];
			}
		}
		else
		{
			if (position.y < (double)(node->center.y >> 1))
			{
				if (position.z < (double)(node->center.z >> 1))
					node = node->child[1];
				else
					node = node->child[5];
			}
			else
			{
				if (position.z < (double)(node->center.z >> 1))
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

unsigned int		launch_ray_to_light(t_ray *ray_inf, t_light *light, int ret, t_vec3d ray, t_vec3d origin, t_octree *node, t_doom *data)
{
	t_vec3d			intersect;
	double			length;
	int				i;
	int				sorted[3];

	if (light->type == SUN)
		light->position = data->sun;
	if (ret == -2 && origin.x < light->position.x)
		return (0);
	if (ret == -1 && origin.x > light->position.x)
		return (0);
	if (ret == -4 && origin.y < light->position.y)
		return (0);
	if (ret == -3 && origin.y > light->position.y)
		return (0);
	if (ret == -6 && origin.z < light->position.z)
		return (0);
	if (ret == -5 && origin.z > light->position.z)
		return (0);
	if ((length = vec3d_length2(vec3d_sub(light->position, origin))) > (light->type == SUN ? 10000 : data->torch))
		return (0);
	length = 1.0 - length / (light->type == SUN ? 5000 : data->torch);
	intersect = origin;
	sorted[0] = 0;
	sorted[1] = 1;
	sorted[2] = 2;
	ray_inf->direction = vec3d_unit(vec3d_sub(light->position, origin));
	max_absolute_between_three(ray_inf->direction.x, ray_inf->direction.y, ray_inf->direction.z, sorted);
	i = 0;
	while (i < 3)
	{
		ret = data->check_intersect[sorted[i]](&intersect, origin
				, ray_inf, &node);
		if (ret == 1)
		{
			ray_inf->length += length;
			return (0);
		}
		else if (ret < 0)
		{
			if (ret == -2 && intersect.x < light->position.x)
				return (0);
			if (ret == -1 && intersect.x > light->position.x)
				return (0);
			if (ret == -4 && intersect.y < light->position.y)
				return (0);
			if (ret == -3 && intersect.y > light->position.y)
				return (0);
			if (ret == -6 && intersect.z < light->position.z)
				return (0);
			if (ret == -5 && intersect.z > light->position.z)
				return (0);
			ray_inf->length += length;
			return (0);
		}
		else if (ret == 3)
		{
			origin = intersect;
			i = -1;
		}
		i++;
	}
	return (0);
}

unsigned int		print_octree(t_vec3d intersect)
{

	if (intersect.x == floor(intersect.x) && ((intersect.y <= floor(intersect.y)
		+ 0.05 && intersect.y >= floor(intersect.y) - 0.05)
		|| (intersect.z <= floor(intersect.z) + 0.05
		&& intersect.z >= floor(intersect.z) - 0.05)))
		return (127 | 127 << 16 | 127 << 8);
	if (intersect.y == floor(intersect.y) && ((intersect.x <= floor(intersect.x)
		+ 0.05 && intersect.x >= floor(intersect.x) - 0.05)
		|| (intersect.z <= floor(intersect.z) + 0.05
		&& intersect.z >= floor(intersect.z) - 0.05)))
		return (127 | 127 << 16 | 127 << 8);
	if (intersect.z == floor(intersect.z) && ((intersect.y <= floor(intersect.y)
		+ 0.05 && intersect.y >= floor(intersect.y) - 0.05)
		|| (intersect.x <= floor(intersect.x) + 0.05
		&& intersect.x >= floor(intersect.x) - 0.05)))
		return (127 | 127 << 16 | 127 << 8);
	return (0);
}

unsigned int		ray_intersect(t_ray ray, t_vec3d origin, t_octree *node
		, t_doom *data)
{
	int				ret;
	t_vec3d			intersect;
	int				sorted[3];
	int				i;
	t_octree		*tmp;
	t_light			*light;
	unsigned int	new_ret;

	sorted[0] = 0;
	sorted[1] = 1;
	sorted[2] = 2;
	max_absolute_between_three(ray.direction.x, ray.direction.y, ray.direction.z, sorted);
	i = 0;
	while (i < 3)
	{
		tmp = node;
		if ((ret = data->check_intersect[sorted[i]](&intersect, origin, &ray
						, &node)) == 1)
			return (add_skybox(intersect));
		else if (ret < 0)
		{
			node = tmp;
			origin = intersect;
			light = data->light;
			ray.color = add_texture(origin, node, ret, data);
			ray.black = (ray.color & 0xF8F8F8) >> 3;
//			printf("%#x\n", ray.color);
			while (light)
			{
				launch_ray_to_light(&ray, light, ret, ray.direction, origin, node, data);
				if (ray.length >= 1.0)
					return (ray.color);
				light = light->next;
			}
			ray.c_color[2] = ((ray.color >> 16) & 255);
			ray.c_color[1] = ((ray.color >> 8) & 255);
			ray.c_color[0] = ((ray.color) & 255);
			if ((new_ret = ray.c_color[2] * ray.length + ((ray.black >> 16) & 255)) < ((ray.color >> 16) & 255))
				ray.c_color[2] = new_ret;
			if ((new_ret = ray.c_color[1] * ray.length + ((ray.black >> 8) & 255)) < ((ray.color >> 8) & 255))
				ray.c_color[1] = new_ret;
			if ((new_ret = ray.c_color[0] * ray.length + ((ray.black) & 255)) < ((ray.color) & 255))
				ray.c_color[0] = new_ret;
			return (*((unsigned int*)&ray.c_color));
		}
		else if (ret == 3)
		{
	//		if ((ret = print_octree(intersect)))
	//			return (ret);
			origin = intersect;
			i = -1;
		}
		i++;
	}
	return (0);
}
