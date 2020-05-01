/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 07:04:23 by smokhtar          #+#    #+#             */
/*   Updated: 2020/03/10 16:52:44 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"
#include "doom.h"
#include "octree.h"

static int		init_tmp_and_sorted(t_ray ray, int sorted[3], t_octree **tmp)
{
	max_absolute_between_three(ray.direction, sorted);
	*tmp = ray.node;
	return (0);
}

static t_ray	ray_colision(t_ray ray, const t_doom *const data)
{
	int				sorted[3];
	int				i;
	t_octree		*tmp;

	i = init_tmp_and_sorted(ray, sorted, &tmp);
	while (i < 3)
	{
		ray.face = data->check_intersect[sorted[i]](&ray.intersect, ray.origin,
			&ray, &ray.node);
		if (ray.face == -1)
			i++;
		else if (ray.face == -3)
		{
			ray.origin = ray.intersect;
			if (ray.node->leaf == BREAKABLE)
				return (ray);
			tmp = ray.node;
			i = 0;
		}
		else if (ray.face >= 0)
			return (ray);
		else
			return (ray);
	}
	return (ray);
}

void			init_interaction(t_doom *data, t_ray *ray)
{
	ray->node = find_actual_position(&data->player.camera.origin, data->octree);
	ray->direction = data->player.camera.direction;
	ray->origin = data->player.camera.origin;
	ray->find_parent[0] = &find_parent_x;
	ray->find_parent[1] = &find_parent_y;
	ray->find_parent[2] = &find_parent_z;
	ray->length = 0;
	*ray = ray_colision(*ray, data);
}

void			update_block(t_vec3d block[2], t_ray ray)
{
	if (ray.face == 0)
		block[0].x += 1;
	else if (ray.face == 1)
		block[0].x -= 1;
	else if (ray.face == 2)
		block[0].y += 1;
	else if (ray.face == 3)
		block[0].y -= 1;
	else if (ray.face == 4)
		block[0].z += 1;
	else if (ray.face == 5)
		block[0].z -= 1;
	block[1].x = block[0].x + 1;
	block[1].y = block[0].y + 1;
	block[1].z = block[0].z + 1;
}

int				update_map_and_octree(t_doom *data, t_vec3d block[2])
{
	data->map_to_save[(int)block[0].x][(int)block[0].y]
		[(int)block[0].z] = 0;
	free_octree(data->octree);
	create_octree(data);
	return (0);
}
