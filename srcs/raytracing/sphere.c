/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 02:04:23 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/06 16:54:42 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "vec3.h"
#include "octree.h"

static void		initialize_sphere(t_quad *quad, t_ray *ray
	, const t_doom *const data)
{
	double	size;
	int		type;

	quad->node = vec3d(ray->node->center.x / 2.0, ray->node->center.y / 2.0
		, ray->node->center.z / 2.0);
	type = data->light_array[(int)quad->node.x][(int)quad->node.y]
		[(int)quad->node.z].type;
	size = data->power[type] / 100.0;
	quad->position = vec3d_sub(data->player.camera.origin, quad->node);
	quad->quad.x = vec3d_length2(ray->direction);
	quad->quad.y = 2 * vec3d_dot(quad->position, ray->direction);
	quad->quad.z = vec3d_length2(quad->position) - size;
	quad->delta = (quad->quad.y * quad->quad.y) - 4 * quad->quad.x
		* quad->quad.z;
}

double			hit_sphere(t_ray *ray, const t_doom *const data)
{
	t_quad		quad;

	initialize_sphere(&quad, ray, data);
	if (quad.delta < 0)
		return (200);
	ray->color = 0xefefef;
	quad.quad.x *= 2.0;
	quad.delta = sqrt(quad.delta);
	quad.quad.z = (-quad.quad.y - quad.delta) / quad.quad.x;
	quad.delta = (-quad.quad.y + quad.delta) / quad.quad.x;
	if (quad.quad.z < 0)
	{
		if (quad.delta < 0)
			return (200);
		return (quad.delta);
	}
	if (quad.delta >= 0 && quad.delta < quad.quad.z)
		return (quad.delta);
	quad.delta = quad.quad.z;
	return (quad.delta);
}
