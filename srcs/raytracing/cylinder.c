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

static int		initialize_cylinder(t_ray *ray, const t_doom *const data
	, t_quad *quad, double value[2])
{
	quad->node = vec3d(ray->node->center.x / 2.0, ray->node->center.y / 2.0
		, ray->node->center.z / 2.0);
	quad->position = vec3d_sub(data->player.camera.origin, quad->node);
	value[0] = vec3d_dot(ray->direction, vec3d(0, 1, 0));
	value[1] = vec3d_dot(quad->position, vec3d(0, 1, 0));
	quad->quad.x = vec3d_dot(ray->direction, ray->direction) - value[0]
		* value[0];
	quad->quad.y = 2 * (vec3d_dot(ray->direction, quad->position) - value[1]
		* value[0]);
	quad->quad.z = vec3d_dot(quad->position, quad->position) - value[1]
		* value[1] - 0.1;
	quad->delta = (quad->quad.y * quad->quad.y) - 4 * quad->quad.x
		* quad->quad.z;
	if (quad->delta < 0)
		return (1);
	ray->color = 0xefefef;
	quad->quad.x *= 2.0;
	quad->delta = sqrt(quad->delta);
	quad->quad.z = (-quad->quad.y - quad->delta) / quad->quad.x;
	quad->delta = (-quad->quad.y + quad->delta) / quad->quad.x;
	return (0);
}

double			hit_cylinder(t_ray *ray, const t_doom *const data)
{
	t_quad		quad;
	double		value[2];

	if (initialize_cylinder(ray, data, &quad, value))
		return (200);
	value[0] = data->player.camera.origin.y + quad.delta * ray->direction.y;
	if (quad.quad.z < 0)
	{
		if (quad.delta < 0)
			return (200);
		if ((int)quad.node.y == (int)value[0])
			return (quad.delta);
		return (200);
	}
	if (quad.delta >= 0 && quad.delta < quad.quad.z)
	{
		if ((int)quad.node.y == (int)value[0])
			return (quad.delta);
		return (200);
	}
	quad.delta = quad.quad.z;
	value[0] = data->player.camera.origin.y + quad.delta * ray->direction.y;
	if ((int)quad.node.y == (int)value[0])
		return (quad.delta);
	return (200);
}
