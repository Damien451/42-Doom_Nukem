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

static int		clipping_between_hitbox_and_voxels(t_vec3d voxel[2]
	, t_vec3d hitbox[2])
{
	if (voxel[0].x <= hitbox[1].x && voxel[1].x >= hitbox[0].x)
		if (voxel[0].y <= hitbox[1].y && voxel[1].y >= hitbox[0].y)
			if (voxel[0].z <= hitbox[1].z && voxel[1].z >= hitbox[0].z)
				return (1);
	return (0);
}

static t_ray	ray_colision(t_ray ray, const t_doom *const data)
{
	int				sorted[3];
	int				i;
	t_octree		*tmp;

	max_absolute_between_three(ray.direction, sorted);
	tmp = ray.node;
	i = 0;
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

static void		shot(t_doom *data, t_player *player)
{
	if (!player->inventory.lag && player->inventory.ammo)
	{
		data->player.inventory.weapon_state = WEAPON_SHOT;
		Mix_PlayChannel(CHANNEL_SOUNDS2, data->mix.sounds[11], 0);
		player->inventory.ammo--;
		player->inventory.lag = 20;
	}
}

void			interaction(t_doom *data, unsigned int key)
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
	if (data->state == PLAYING && key & LEFT_CLICK)
		shot(data, &data->player);
	if (ray.length > DISTANCE_MAX_BLOCK || !ray.node)
		return ;
	else if (ray.face >= 0 && data->state == EDITION_MODE)
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
		if (key & LEFT_CLICK)
		{
			data->map_to_save[(int)block[0].x][(int)block[0].y][(int)block[0].z] = 0;
			free_octree(data->octree);
			create_octree(data);
			return ;
		}
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
		if (clipping_between_hitbox_and_voxels(block, player))
			return ;
		if (key & RIGHT_CLICK)
			data->map_to_save[(int)block[0].x][(int)block[0].y][(int)block[0].z] = data->player.inventory.selected + 1;
		free_octree(data->octree);
		create_octree(data);
	}
}
