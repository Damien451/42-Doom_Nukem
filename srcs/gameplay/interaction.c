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

void			init_player_and_block(t_doom *data, t_vec3d player[2]
	, t_vec3d block[2], t_ray ray)
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
}

int				interaction(t_doom *data, unsigned int key)
{
	t_ray		ray;
	t_vec3d		player[2];
	t_vec3d		block[2];

	init_interaction(data, &ray);
	if (data->state == PLAYING && key & LEFT_CLICK)
		shot(data, &data->player);
	if (ray.length > DISTANCE_MAX_BLOCK || !ray.node)
		return (0);
	else if (ray.face >= 0 && data->state == EDITION_MODE)
	{
		init_player_and_block(data, player, block, ray);
		if (key & LEFT_CLICK)
			return (update_map_and_octree(data, block));
		update_block(block, ray);
		if (clipping_between_hitbox_and_voxels(block, player))
			return (0);
		if (key & RIGHT_CLICK)
			data->map_to_save[(int)block[0].x][(int)block[0].y]
				[(int)block[0].z] = data->player.inventory.selected + 1;
		free_octree(data->octree);
		create_octree(data);
	}
	return (0);
}
