/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_hitbox.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:31:51 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/12 13:10:01 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "player.h"

void		check_if_inside_map(t_doom *data, t_vec3d *position)
{
	if (position->x > 63.5)
	{
		data->player.acceleration.x = 0;
		position->x = 63.5;
	}
	else if (position->x < 0.5)
	{
		data->player.acceleration.x = 0;
		position->x = 0.5;
	}
	if (position->y > 63.5)
	{
		data->player.acceleration.y = 0;
		position->y = 63.5;
	}
	else if (position->y < 0.5)
	{
		data->player.acceleration.y = 0;
		data->player.health = 0;
		position->y = 0.5;
	}
	if (position->z > 63.5)
	{
		data->player.acceleration.z = 0;
		position->z = 63.5;
	}
	else if (position->z < 0.5)
	{
		data->player.acceleration.z = 0;
		position->z = 0.5;
	}
}

int				clipping_between_hitbox_and_voxels(t_vec3d voxel[2]
	, t_vec3d hitbox[2])
{
	if (voxel[0].x <= hitbox[1].x && voxel[1].x >= hitbox[0].x)
		if (voxel[0].y <= hitbox[1].y && voxel[1].y >= hitbox[0].y)
			if (voxel[0].z <= hitbox[1].z && voxel[1].z >= hitbox[0].z)
				return (1);
	return (0);
}

void			add_clipping_for_each_point(t_doom *data, t_player *player)
{
	int		i;
	int		j;
	int		k;
	t_vec3d	new_pos;
	t_vec3d	new_acceleration;
	t_vec3d		hitbox[2];
	t_vec3l		voxels;
	t_vec3d		vox[2];
	int			tmp;

	i = 0;
	camera_event_translate(data);
	new_pos = vec3d_add(data->player.camera.origin, data->player.acceleration);
	check_if_inside_map(data, &new_pos);
	hitbox[0].x = new_pos.x - 0.2;
	hitbox[0].y = new_pos.y - 1.5;
	hitbox[0].z = new_pos.z - 0.2;
	if (hitbox[0].x < 0)
		hitbox[0].x = 0;
	if (hitbox[0].y < 0)
		hitbox[0].y = 0;
	if (hitbox[0].z < 0)
		hitbox[0].z = 0;
	hitbox[1].x = hitbox[0].x + 0.4;
	hitbox[1].y = hitbox[0].y + 1.7;
	hitbox[1].z = hitbox[0].z + 0.4;
	voxels.x = hitbox[0].x;
	voxels.y = hitbox[0].y;
	voxels.z = hitbox[0].z;
	new_acceleration = player->acceleration;
	while (i < 3)
	{
		j = 0;
		while (j < 3)
		{
			k = 0;
			while (k < 3)
			{
				if (data->map_to_save[voxels.x + i][voxels.y + j][voxels.z + k])
				{
					tmp = 0;
					vox[0].x = voxels.x + i;
					vox[0].y = voxels.y + j;
					vox[0].z = voxels.z + k;
					vox[1].x = vox[0].x + 1;
					vox[1].y = vox[0].y + 1;
					vox[1].z = vox[0].z + 1;
					if (clipping_between_hitbox_and_voxels(vox, hitbox))
					{
						if (vox[1].y > hitbox[0].y && j == 0)
						{
							new_acceleration.y = 0;
							hitbox[0].y = vox[1].y;
							hitbox[1].y = hitbox[0].y + 1.7;
							tmp = 1;
						}
						if (vox[0].y < hitbox[1].y && j == 2)
						{
							new_acceleration.y = 0;
							hitbox[1].y = vox[0].y;
							hitbox[0].y = hitbox[1].y - 1.7;
							tmp = 1;
						}
						if (vox[1].x > hitbox[0].x && i == 0)
						{
							new_acceleration.x = 0;
							hitbox[0].x = vox[1].x;
							hitbox[1].x = hitbox[0].x + 0.4;
							tmp = 1;
						}
						if (vox[0].x < hitbox[1].x && i == 2)
						{
							new_acceleration.x = 0;
							hitbox[1].x = vox[0].x;
							hitbox[0].x = hitbox[1].x - 0.4;
							tmp = 1;
						}
						if (vox[1].z > hitbox[0].z && k == 0)
						{
							new_acceleration.z = 0;
							hitbox[0].z = vox[1].z;
							hitbox[1].z = hitbox[0].z + 0.4;
							tmp = 1;
						}
						if (vox[0].z < hitbox[1].z && k == 2)
						{
							new_acceleration.z = 0;
							hitbox[1].z = vox[0].z;
							hitbox[0].z = hitbox[1].z - 0.4;
							tmp = 1;
						}
						if (tmp)
						{
							k = k;
						}
					}
				}
				k++;
			}
			j++;
		}
		i++;
	}
	new_pos.x = hitbox[0].x + 0.2;
	new_pos.y = hitbox[0].y + 1.5;
	new_pos.z = hitbox[0].z + 0.2;
	data->player.physics.acceleration = new_acceleration;
	data->player.physics.origin = new_pos;
}
