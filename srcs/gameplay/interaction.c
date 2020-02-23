/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 07:04:23 by smokhtar          #+#    #+#             */
/*   Updated: 2020/02/23 14:22:38 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"
#include "doom.h"
#include "octree.h"

int				clipping_between_hitbox_and_voxels(t_vec3d voxel[2]
	, t_vec3d hitbox[2])
{
	if (voxel[0].x <= hitbox[1].x && voxel[1].x >= hitbox[0].x)
		if (voxel[0].y <= hitbox[1].y && voxel[1].y >= hitbox[0].y)
			if (voxel[0].z <= hitbox[1].z && voxel[1].z >= hitbox[0].z)
				return (1);
	return (0);
}

t_ray		ray_colision(t_ray ray, const t_doom *const data)
{
	int				sorted[3];
	int				i;
	t_octree		*tmp;
	double			length;

	max_absolute_between_three(ray.direction, sorted);
	tmp = ray.node;
	i = 0;
	while (i < 3)
	{
		ray.face = data->check_intersect[sorted[i]](&ray.intersect, ray.origin
				, &ray, &ray.node);
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

void			interaction(t_doom *data)
{
	t_ray		ray;
	t_vec3d		player[2];
	t_vec3d		block[2];

	ray.node = find_actual_position(&data->player.camera.origin, data->octree);
	ray.direction = data->player.camera.direction;
	ray.origin = data->player.camera.origin;
	ray.find_parent[0] = &find_parent_x;
	ray.find_parent[1] = &find_parent_y;
	ray.find_parent[2] = &find_parent_z;
	ray.length = 0;
	ray = ray_colision(ray, data);
	if (ray.length > DISTANCE_MAX_BLOCK)
		return ;
	else if (!ray.node)
		return ;
	else if (ray.face >= 0 || ray.node->leaf == BREAKABLE)
	{
		player[0].x = data->player.camera.origin.x - 0.25;
		player[1].x = data->player.camera.origin.x + 0.25;
		player[0].z = data->player.camera.origin.z - 0.25;
		player[1].z = data->player.camera.origin.z + 0.25;
		player[0].y = data->player.camera.origin.y - 1.55;
		player[1].y = data->player.camera.origin.y + 0.25;
		block[0].x = floor(ray.intersect.x);
		block[0].y = floor(ray.intersect.y);
		block[0].z = floor(ray.intersect.z);
		if (ray.node->leaf == BREAKABLE)
			return ;
		if (ray.face == 0)
			block[0].x -= 1;
		else if (ray.face == 2)
			block[0].y -= 1;
		else if (ray.face == 4)
			block[0].z -= 1;
		if (ray.face == 1)
			block[0].x -= 1;
		else if (ray.face == 0)
			block[0].x += 1;
		else if (ray.face == 3)
			block[0].y -= 1;
		else if (ray.face == 2)
			block[0].y += 1;
		else if (ray.face == 5)
			block[0].z -= 1;
		else
			block[0].z += 1;
		block[1].x = block[0].x + 1;
		block[1].y = block[0].y + 1;
		block[1].z = block[0].z + 1;
		if (clipping_between_hitbox_and_voxels(block, player))
			return ;
		data->map_to_save[(int)block[0].x][(int)block[0].y][(int)block[0].z] = data->player.inventory.selected_block;
		free_octree(data->octree);
		create_octree(data);
	}
}
