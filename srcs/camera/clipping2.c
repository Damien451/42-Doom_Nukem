/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 00:16:21 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/20 01:33:40 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int				clipping_between_hitbox_and_voxels(t_vec3d voxel[2]
	, t_vec3d hitbox[2])
{
	if (voxel[0].x <= hitbox[1].x && voxel[1].x >= hitbox[0].x)
		if (voxel[0].y <= hitbox[1].y && voxel[1].y >= hitbox[0].y)
			if (voxel[0].z <= hitbox[1].z && voxel[1].z >= hitbox[0].z)
				return (1);
	return (0);
}

void			check_y_min(t_doom *data, t_vec3d *accel, t_vec3d hitbox[2])
{
	int			i;
	int			j;
	t_vec3d		vox[2];

	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 2)
		{
			if (hitbox[0].x + i < 64.0 && hitbox[0].z + j < 64.0)
			{
				if (data->map_to_save[(int)hitbox[0].x + i]
						[(int)hitbox[0].y][(int)hitbox[0].z + j])
				{
					vox[0].x = (int)hitbox[0].x + i;
					vox[0].y = (int)hitbox[0].y;
					vox[0].z = (int)hitbox[0].z + j;
					vox[1].x = vox[0].x + 1;
					vox[1].y = vox[0].y + 1;
					vox[1].z = vox[0].z + 1;
					if (clipping_between_hitbox_and_voxels(vox, hitbox))
					{
						hitbox[0].y = vox[1].y + EPSILON;
						hitbox[1].y = hitbox[0].y + 1.7;
						accel->y = 0;
						return ;
					}
				}
			}
			j++;
		}
		i++;
	}
}

void			check_y_max(t_doom *data, t_vec3d *accel, t_vec3d hitbox[2])
{
	int			i;
	int			j;
	t_vec3d		vox[2];

	i = 0;
	while (i < 2)
	{
		j = 0;
		while (j < 2)
		{
			if (hitbox[0].x + i < 64.0 && hitbox[0].z + j < 64.0)
			{
				if (data->map_to_save[(int)hitbox[0].x + i]
						[(int)hitbox[1].y][(int)hitbox[0].z + j])
				{
					vox[0].x = (int)hitbox[0].x + i;
					vox[0].y = (int)hitbox[1].y;
					vox[0].z = (int)hitbox[0].z + j;
					vox[1].x = vox[0].x + 1;
					vox[1].y = vox[0].y + 1;
					vox[1].z = vox[0].z + 1;
					if (clipping_between_hitbox_and_voxels(vox, hitbox))
					{
						hitbox[1].y = vox[0].y - EPSILON;
						hitbox[0].y = hitbox[1].y - 1.7;
						accel->y = 0;
						return ;
					}
				}
			}
			j++;
		}
		i++;
	}
}

void			check_x_min(t_doom *data, t_vec3d *accel, t_vec3d hitbox[2])
{
	int			i;
	int			j;
	t_vec3d		vox[2];

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 2)
		{
			if (hitbox[0].y + i < 64.0 && hitbox[0].z + j < 64.0)
			{
				if (data->map_to_save[(int)hitbox[0].x]
						[(int)hitbox[0].y + i][(int)hitbox[0].z + j])
				{
					vox[0].x = (int)hitbox[0].x;
					vox[0].y = (int)hitbox[0].y + i;
					vox[0].z = (int)hitbox[0].z + j;
					vox[1].x = vox[0].x + 1;
					vox[1].y = vox[0].y + 1;
					vox[1].z = vox[0].z + 1;
					if (clipping_between_hitbox_and_voxels(vox, hitbox))
					{
						hitbox[0].x = vox[1].x + EPSILON;
						hitbox[1].x = hitbox[0].x + 0.4;
						accel->x = 0;
						return ;
					}
				}
			}
			j++;
		}
		i++;
	}
}

void			check_x_max(t_doom *data, t_vec3d *accel, t_vec3d hitbox[2])
{
	int			i;
	int			j;
	t_vec3d		vox[2];

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 2)
		{
			if (hitbox[0].y + i < 64.0 && hitbox[0].z + j < 64.0)
			{
				if (data->map_to_save[(int)hitbox[1].x]
						[(int)hitbox[0].y + i][(int)hitbox[0].z + j])
				{
					vox[0].x = (int)hitbox[1].x;
					vox[0].y = (int)hitbox[0].y + i;
					vox[0].z = (int)hitbox[0].z + j;
					vox[1].x = vox[0].x + 1;
					vox[1].y = vox[0].y + 1;
					vox[1].z = vox[0].z + 1;
					if (clipping_between_hitbox_and_voxels(vox, hitbox))
					{
						hitbox[1].x = vox[0].x - EPSILON;
						hitbox[0].x = hitbox[1].x - 0.4;
						accel->x = 0;
						return ;
					}
				}
			}
			j++;
		}
		i++;
	}
}

void			check_z_min(t_doom *data, t_vec3d *accel, t_vec3d hitbox[2])
{
	int			i;
	int			j;
	t_vec3d		vox[2];

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 2)
		{
			if (hitbox[0].y + i < 64.0 && hitbox[0].x + j < 64.0)
			{
				if (data->map_to_save[(int)hitbox[0].x + j]
						[(int)hitbox[0].y + i][(int)hitbox[0].z])
				{
					vox[0].x = (int)hitbox[0].x + j;
					vox[0].y = (int)hitbox[0].y + i;
					vox[0].z = (int)hitbox[0].z;
					vox[1].x = vox[0].x + 1;
					vox[1].y = vox[0].y + 1;
					vox[1].z = vox[0].z + 1;
					if (clipping_between_hitbox_and_voxels(vox, hitbox))
					{
						hitbox[0].z = vox[1].z;
						hitbox[1].z = hitbox[0].z + 0.4;
						accel->z = 0;
						return ;
					}
				}
			}
			j++;
		}
		i++;
	}
}

void			check_z_max(t_doom *data, t_vec3d *accel, t_vec3d hitbox[2])
{
	int			i;
	int			j;
	t_vec3d		vox[2];

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (j < 2)
		{
			if (hitbox[0].y + i < 64.0 && hitbox[0].x + j < 64.0)
			{
				if (data->map_to_save[(int)hitbox[0].x + j]
						[(int)hitbox[0].y + j][(int)hitbox[1].z])
				{
					vox[0].x = (int)hitbox[0].x + j;
					vox[0].y = (int)hitbox[0].y + i;
					vox[0].z = (int)hitbox[1].z;
					vox[1].x = vox[0].x + 1;
					vox[1].y = vox[0].y + 1;
					vox[1].z = vox[0].z + 1;
					if (clipping_between_hitbox_and_voxels(vox, hitbox))
					{
						hitbox[1].z = vox[0].z;
						hitbox[0].z = hitbox[1].z - 0.4;
						accel->z = 0;
						return ;
					}
				}
			}
			j++;
		}
		i++;
	}
}
