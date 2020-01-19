/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/08 22:19:59 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/08 22:43:02 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "vec3.h"
#include "octree.h"

double			hit_plane(t_ray *ray, const t_doom *const data)
{
	t_vec3d		node;
	t_vec3d		position;
	double		t;

	node = vec3d(ray->node->center.x / 2.0, ray->node->center.y / 2.0
		, ray->node->center.z / 2.0);
	position = vec3d_sub(data->player.camera.origin, node);
	t = -1 * vec3d_dot(position, vec3d_unit(vec3d(1.5, 2.0, 3.0)))
		/ vec3d_dot(data->player.camera.direction, vec3d_unit(vec3d(1.5, 2.0, 3.0)));
	if (t >= 0)
		return (t);
	return (200);
}
