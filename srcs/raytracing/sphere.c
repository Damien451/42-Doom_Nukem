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

double			hit_sphere(t_ray *ray, const t_doom *const data)
{
	t_vec3d		quad;
	double		delta;
	t_vec3d		position;
	double		size;
	t_vec3d		node;
	int			type;

	node = vec3d(ray->node->center.x / 2.0, ray->node->center.y / 2.0, ray->node->center.z / 2.0);
	type = data->light_array[(int)node.x][(int)node.y][(int)node.z].type;
	size = data->power[type] / 100.0;
	position = vec3d_sub(data->player.camera.origin, node);
	quad.x = vec3d_length2(ray->direction);
	quad.y = 2 * vec3d_dot(position, ray->direction);
	quad.z = vec3d_length2(position) - size;
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
		return (delta);
	}
	if (delta >= 0 && delta < quad.z)
		return (delta);
	delta = quad.z;
	return (delta);
}
