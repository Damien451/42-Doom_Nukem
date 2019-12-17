/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 02:04:23 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/17 05:22:41 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "vec3.h"
#include "octree.h"

double			hit_sphere(t_ray *ray, t_doom *data)
{
	t_vec3d		quad;
	double		delta;
	t_vec3d		position;
	double		size;
	t_vec3d		node;

	node = vec3d(ray->node->center.x / 2.0, ray->node->center.y / 2.0, ray->node->center.z / 2.0);
	size = data->light_array[(int)node.x][(int)node.y][(int)node.z].type;
	size = data->power[(int)size];
	if (size == 2)
		size = 0.015625;
	else if (size == 3)
		size = 0.03125;
	else if (size == 4)
		size = 0.0625;
	else
		size = 0.125;
	position = vec3d_sub(data->player.camera.origin, node);
	quad.x = vec3d_length2(ray->direction);
	quad.y = 2 * vec3d_dot(position, ray->direction);
	quad.z = vec3d_length2(position) - size;
	delta = (quad.y * quad.y) - 4 * quad.x * quad.z;
	if (delta < 0)
		return (200);
	quad.z = (-quad.y - sqrt(delta)) / (2 * quad.x);
	delta = (-quad.y + sqrt(delta)) / (2 * quad.x);
	ray->color = 0x7f7f7f;
	if (quad.z < 0)
	{
		if (delta < 0)
			return (200);
		return (delta);
	}
	if (delta >= 0 && delta < quad.z)
		return (delta);
	delta = quad.z;
	return (delta);
}
