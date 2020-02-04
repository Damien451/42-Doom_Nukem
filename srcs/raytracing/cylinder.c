/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/03 18:41:55 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/04 23:00:48 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "vec3.h"
#include "octree.h"

double			hit_cylinder(t_ray *ray, const t_doom *const data)
{
	t_vec3d		quad;
	double		delta;
	t_vec3d		position;
	t_vec3d		node;
	double		value[2];

	node = vec3d(ray->node->center.x / 2.0, ray->node->center.y / 2.0, ray->node->center.z / 2.0);
	position = vec3d_sub(data->player.camera.origin, node);
	value[0] = vec3d_dot(ray->direction, vec3d(0, 1, 0));
	value[1] = vec3d_dot(position, vec3d(0, 1, 0));
	quad.x = vec3d_dot(ray->direction, ray->direction) - value[0] * value[0];
	quad.y = 2 * (vec3d_dot(ray->direction, position) - value[1] * value[0]);
	quad.z = vec3d_dot(position, position) - value[1] * value[1] - 0.1;
	delta = (quad.y * quad.y) - 4 * quad.x * quad.z;
	if (delta < 0)
		return (200);
	ray->color = 0xefefef;
	quad.x *= 2.0;
	delta = sqrt(delta);
	quad.z = (-quad.y - delta) / quad.x;
	delta = (-quad.y + delta) / quad.x;
	if (quad.z < 0)
	{
		if (delta < 0)
			return (200);
		value[0] = data->player.camera.origin.y + delta * ray->direction.y;
		if ((int)node.y == (int)value[0])
			return (delta);
		return (200);
	}
	if (delta >= 0 && delta < quad.z)
	{
		value[0] = data->player.camera.origin.y + delta * ray->direction.y;
		if ((int)node.y == (int)value[0])
			return (delta);
		return (200);
	}
	delta = quad.z;
	value[0] = data->player.camera.origin.y + delta * ray->direction.y;
	if ((int)node.y == (int)value[0])
		return (delta);
	return (200);
}
