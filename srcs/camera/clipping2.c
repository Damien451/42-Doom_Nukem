/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 00:16:21 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/28 17:10:45 by roduquen         ###   ########.fr       */
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

void			check_y_min(t_doom *data, t_vec3d *accel
	, t_vec3d hitbox[2], double y)
{
	int			x;
	int			z;
	t_vec3d		vec;

	x = floor(hitbox[0].x);
	z = floor(hitbox[0].z);
	vec.y = floor(hitbox[0].y + accel->y);
	if ((vec.x = data->map_to_save[x][(int)vec.y][z]))
	{
		if (vec.x < 41)
		{
			accel->y = 0;
			hitbox[0].y = floor(hitbox[0].y);
			hitbox[1].y = hitbox[0].y + y;
			return ;
		}
		else
		{
			if ((vec.y = floor(hitbox[0].y) - 0.5
						+ sqrt(data->power[TORCH] / 100.0)) - accel->y > hitbox[0].y)
			{
				accel->y = 0;
				hitbox[0].y = vec.y;
				hitbox[1].y = hitbox[1].y + y;
				return ;
			}
		}
	}
	if (hitbox[0].z - z >= 0.1)
	{
		z = z + 1;
		if ((vec.x = data->map_to_save[(int)x][(int)vec.y][(int)z]))
		{
			if (vec.x < 41)
			{
				accel->y = 0;
				hitbox[0].y = floor(hitbox[0].y);
				hitbox[1].y = hitbox[0].y + y;
				return ;
			}
			else
			{
				if ((vec.y = floor(hitbox[0].y) - 0.5
							+ sqrt(data->power[TORCH] / 100.0)) - accel->y > hitbox[0].y)
				{
					accel->y = 0;
					hitbox[0].y = vec.y;
					hitbox[1].y = hitbox[0].y + y;
					return ;
				}
			}
		}
	}
	if (hitbox[0].x - x >= 0.1)
	{
		x += 1;
		z = floor(hitbox[0].z);
		if ((vec.x = data->map_to_save[(int)x][(int)vec.y][(int)z]))
		{
			if (vec.x < 41)
			{
				accel->y = 0;
				hitbox[0].y = floor(hitbox[0].y);
				hitbox[1].y = hitbox[0].y + y;
				return ;
			}
			else
			{
				if ((vec.y = floor(hitbox[0].y) - 0.5
							+ sqrt(data->power[TORCH] / 100.0)) - accel->y > hitbox[0].y)
				{
					accel->y = 0;
					hitbox[0].y = vec.y;
					hitbox[1].y = hitbox[0].y + y;
					return ;
				}
			}
		}
		if (hitbox[0].z - z >= 0.1)
		{
			z = z + 1;
			if ((vec.x = data->map_to_save[(int)x][(int)vec.y][(int)z]))
			{
				if (vec.x < 41)
				{
					accel->y = 0;
					hitbox[0].y = floor(hitbox[0].y);
					hitbox[1].y = hitbox[0].y + y;
					return ;
				}
				else
				{
					if ((vec.y = floor(hitbox[0].y) - 0.5
								+ sqrt(data->power[TORCH] / 100.0)) - accel->y > hitbox[0].y)
					{
						accel->y = 0;
						hitbox[0].y = vec.y;
						hitbox[1].y = hitbox[0].y + y;
						return ;
					}
				}
			}
		}
	}
	hitbox[0].y += accel->y;
	hitbox[1].y += accel->y;
}

void			check_y_max(t_doom *data, t_vec3d *accel
		, t_vec3d hitbox[2], double y)
{
	int			x;
	int			z;
	t_vec3d		vec;

	x = floor(hitbox[0].x);
	z = floor(hitbox[0].z);
	vec.y = floor(hitbox[1].y + accel->y);
	if ((vec.x = data->map_to_save[x][(int)vec.y][z]))
	{
		accel->y = -0.045;
		hitbox[1].y = vec.y;
		hitbox[0].y = hitbox[1].y - y;
		return ;
	}
	if (hitbox[0].z - z >= 0.1)
	{
		z = z + 1;
		if ((vec.x = data->map_to_save[(int)x][(int)vec.y][(int)z]))
		{
			accel->y = -0.045;
			hitbox[1].y = vec.y;
			hitbox[0].y = hitbox[1].y - y;
			return ;
		}
	}
	if (hitbox[0].x - x >= 0.1)
	{
		x += 1;
		z = floor(hitbox[0].z);
		if ((vec.x = data->map_to_save[(int)x][(int)vec.y][(int)z]))
		{
			accel->y = -0.045;
			hitbox[1].y = vec.y;
			hitbox[0].y = hitbox[1].y - y;
			return ;
		}
		if (hitbox[0].z - z >= 0.1)
		{
			z = z + 1;
			if ((vec.x = data->map_to_save[(int)x][(int)vec.y][(int)z]))
			{
				accel->y = -0.045;
				hitbox[0].y = floor(hitbox[0].y);
				hitbox[1].y = hitbox[0].y + y;
				return ;
			}
		}
	}
	hitbox[0].y += accel->y;
	hitbox[1].y += accel->y;
}

void			check_x_min(t_doom *data, t_vec3d *accel
	, t_vec3d hitbox[2], double x)
{
	int			y;
	int			z;
	t_vec3d		vec;

	y = floor(hitbox[0].y);
	z = floor(hitbox[0].z);
	vec.x = floor(hitbox[0].x + accel->x);
	if ((vec.y = data->map_to_save[(int)vec.x][y][z]))
	{
		if (vec.y < 41)
		{
			accel->x = 0;
			hitbox[0].x = floor(hitbox[0].x);
			hitbox[1].x = hitbox[0].x + x;
			return ;
		}
		else
		{
			if ((vec.x = floor(hitbox[0].x) - 0.5
						+ sqrt(data->power[TORCH] / 100.0)) - accel->x > hitbox[0].x)
			{
				accel->x = 0;
				hitbox[0].x = vec.x;
				hitbox[1].x = hitbox[1].x + x;
				return ;
			}
		}
	}
	if (hitbox[0].z - z >= 0.1)
	{
		z = z + 1;
		if ((vec.y = data->map_to_save[(int)vec.x][y][z]))
		{
			if (vec.y < 41)
			{
				accel->x = 0;
				hitbox[0].x = floor(hitbox[0].x);
				hitbox[1].x = hitbox[0].x + x;
				return ;
			}
			else
			{
				if ((vec.x = floor(hitbox[0].x) - 0.5
							+ sqrt(data->power[TORCH] / 100.0)) - accel->x > hitbox[0].x)
				{
					accel->x = 0;
					hitbox[0].x = vec.x;
					hitbox[1].x = hitbox[0].x + x;
					return ;
				}
			}
		}
	}
	if (hitbox[0].y - y >= 0.1)
	{
		y += 1;
		z = floor(hitbox[0].z);
		if ((vec.y = data->map_to_save[(int)vec.x][y][z]))
		{
			if (vec.y < 41)
			{
				accel->x = 0;
				hitbox[0].x = floor(hitbox[0].x);
				hitbox[1].x = hitbox[0].x + x;
				return ;
			}
			else
			{
				if ((vec.x = floor(hitbox[0].x) - 0.5
							+ sqrt(data->power[TORCH] / 100.0)) - accel->x > hitbox[0].x)
				{
					accel->x = 0;
					hitbox[0].x = vec.x;
					hitbox[1].x = hitbox[0].x + x;
					return ;
				}
			}
		}
		if (hitbox[0].z - z >= 0.1)
		{
			z = z + 1;
			if ((vec.y = data->map_to_save[(int)vec.x][y][z]))
			{
				if (vec.y < 41)
				{
					accel->x = 0;
					hitbox[0].x = floor(hitbox[0].x);
					hitbox[1].x = hitbox[0].x + x;
					return ;
				}
				else
				{
					if ((vec.x = floor(hitbox[0].x) - 0.5
								+ sqrt(data->power[TORCH] / 100.0)) - accel->x > hitbox[0].x)
					{
						accel->x = 0;
						hitbox[0].x = vec.x;
						hitbox[1].x = hitbox[0].x + x;
						return ;
					}
				}
			}
		}
	}
	hitbox[0].x += accel->x;
	hitbox[1].x += accel->x;
}

void			check_x_max(t_doom *data, t_vec3d *accel
	, t_vec3d hitbox[2], double x)
{
	int			y;
	int			z;
	t_vec3d		vec;

	y = floor(hitbox[0].y);
	z = floor(hitbox[0].z);
	vec.x = floor(hitbox[1].x + accel->x);
	if ((vec.y = data->map_to_save[(int)vec.x][y][z]))
	{
		if (vec.y < 41)
		{
			accel->x = 0;
			hitbox[1].x = floor(hitbox[1].x) + 0.99999;
			hitbox[0].x = hitbox[1].x - x;
			return ;
		}
		else
		{
			if ((vec.x = floor(hitbox[1].x) - 0.5
						+ sqrt(data->power[TORCH] / 100.0)) - accel->x > hitbox[1].x)
			{
				accel->x = 0;
				hitbox[1].x = vec.x + 0.99999;
				hitbox[0].x = hitbox[1].x - x;
				return ;
			}
		}
	}
	if (hitbox[0].z - z >= 0.1)
	{
		z = z + 1;
		if ((vec.y = data->map_to_save[(int)vec.x][y][z]))
		{
			if (vec.y < 41)
			{
				accel->x = 0;
				hitbox[1].x = floor(hitbox[1].x) + 0.99999;
				hitbox[0].x = hitbox[1].x - x;
				return ;
			}
			else
			{
				if ((vec.x = floor(hitbox[1].x) - 0.5
							+ sqrt(data->power[TORCH] / 100.0)) - accel->x > hitbox[1].x)
				{
					accel->x = 0;
					hitbox[1].x = vec.x + 0.99999;
					hitbox[0].x = hitbox[0].x - x;
					return ;
				}
			}
		}
	}
	if (hitbox[0].y - y >= 0.1)
	{
		y += 1;
		z = floor(hitbox[0].z);
		if ((vec.y = data->map_to_save[(int)vec.x][y][z]))
		{
			if (vec.y < 41)
			{
				accel->x = 0;
				hitbox[1].x = floor(hitbox[1].x) + 0.99999;
				hitbox[0].x = hitbox[1].x - x;
				return ;
			}
			else
			{
				if ((vec.x = floor(hitbox[1].x) - 0.5
							+ sqrt(data->power[TORCH] / 100.0)) - accel->x > hitbox[1].x)
				{
					accel->x = 0;
					hitbox[1].x = vec.x + 0.99999;
					hitbox[0].x = hitbox[1].x - x;
					return ;
				}
			}
		}
		if (hitbox[0].z - z >= 0.1)
		{
			z = z + 1;
			if ((vec.y = data->map_to_save[(int)vec.x][y][z]))
			{
				if (vec.y < 41)
				{
					accel->x = 0;
					hitbox[1].x = floor(hitbox[1].x) + 0.99999;
					hitbox[0].x = hitbox[1].x - x;
					return ;
				}
				else
				{
					if ((vec.x = floor(hitbox[0].x) - 0.5
								+ sqrt(data->power[TORCH] / 100.0)) - accel->x > hitbox[0].x)
					{
						accel->x = 0;
						hitbox[1].x = vec.x + 0.99999;
						hitbox[0].x = hitbox[1].x - x;
						return ;
					}
				}
			}
		}
	}
	hitbox[0].x += accel->x;
	hitbox[1].x += accel->x;
}

void			check_z_min(t_doom *data, t_vec3d *accel
	, t_vec3d hitbox[2], double z)
{
	int			y;
	int			x;
	t_vec3d		vec;

	y = floor(hitbox[0].y);
	x = floor(hitbox[0].x);
	vec.z = floor(hitbox[0].z + accel->z);
	if ((vec.y = data->map_to_save[x][y][(int)vec.z]))
	{
		if (vec.y < 41)
		{
			accel->z = 0;
			hitbox[0].z = floor(hitbox[0].z);
			hitbox[1].z = hitbox[0].z + z;
			return ;
		}
		else
		{
			if ((vec.z = floor(hitbox[0].z) - 0.5
						+ sqrt(data->power[TORCH] / 100.0)) - accel->z > hitbox[0].z)
			{
				accel->z = 0;
				hitbox[0].z = vec.z;
				hitbox[1].z = hitbox[1].z + z;
				return ;
			}
		}
	}
	if (hitbox[0].x - x >= 0.1)
	{
		x = x + 1;
		if ((vec.y = data->map_to_save[x][y][(int)vec.z]))
		{
			if (vec.y < 41)
			{
				accel->z = 0;
				hitbox[0].z = floor(hitbox[0].z);
				hitbox[1].z = hitbox[0].z + z;
				return ;
			}
			else
			{
				if ((vec.z = floor(hitbox[0].z) - 0.5
							+ sqrt(data->power[TORCH] / 100.0)) - accel->z > hitbox[0].z)
				{
					accel->z = 0;
					hitbox[0].z = vec.z;
					hitbox[1].z = hitbox[0].z + z;
					return ;
				}
			}
		}
	}
	if (hitbox[0].y - y >= 0.1)
	{
		y += 1;
		x = floor(hitbox[0].x);
		if ((vec.y = data->map_to_save[x][y][(int)vec.z]))
		{
			if (vec.y < 41)
			{
				accel->z = 0;
				hitbox[0].z = floor(hitbox[0].z);
				hitbox[1].z = hitbox[0].z + z;
				return ;
			}
			else
			{
				if ((vec.z = floor(hitbox[0].z) - 0.5
							+ sqrt(data->power[TORCH] / 100.0)) - accel->z > hitbox[0].z)
				{
					accel->z = 0;
					hitbox[0].z = vec.z;
					hitbox[1].z = hitbox[0].z + z;
					return ;
				}
			}
		}
		if (hitbox[0].x - x >= 0.1)
		{
			x = x + 1;
			if ((vec.y = data->map_to_save[x][y][(int)vec.z]))
			{
				if (vec.y < 41)
				{
					accel->z = 0;
					hitbox[0].z = floor(hitbox[0].z);
					hitbox[1].z = hitbox[0].z + z;
					return ;
				}
				else
				{
					if ((vec.z = floor(hitbox[0].z) - 0.5
								+ sqrt(data->power[TORCH] / 100.0)) - accel->z > hitbox[0].z)
					{
						accel->z = 0;
						hitbox[0].z = vec.z;
						hitbox[1].z = hitbox[0].z + z;
						return ;
					}
				}
			}
		}
	}
	hitbox[0].z += accel->z;
	hitbox[1].z += accel->z;
}

void			check_z_max(t_doom *data, t_vec3d *accel
	, t_vec3d hitbox[2], double z)
{
	int			y;
	int			x;
	t_vec3d		vec;

	y = floor(hitbox[0].y);
	x = floor(hitbox[0].x);
	vec.z = floor(hitbox[1].z + accel->z);
	if ((vec.y = data->map_to_save[x][y][(int)vec.z]))
	{
		if (vec.y < 41)
		{
			accel->z = 0;
			hitbox[1].z = floor(hitbox[1].z) + 0.99999;
			hitbox[0].z = hitbox[1].z - z;
			return ;
		}
		else
		{
			if ((vec.z = floor(hitbox[1].z) - 0.5
						+ sqrt(data->power[TORCH] / 100.0)) - accel->z > hitbox[1].z)
			{
				accel->z = 0;
				hitbox[1].z = vec.z + 0.99999;
				hitbox[0].z = hitbox[1].z - z;
				return ;
			}
		}
	}
	if (hitbox[0].x - x >= 0.1)
	{
		x = x + 1;
		if ((vec.y = data->map_to_save[x][y][(int)vec.z]))
		{
			if (vec.y < 41)
			{
				accel->z = 0;
				hitbox[1].z = floor(hitbox[1].z) + 0.99999;
				hitbox[0].z = hitbox[1].z - z;
				return ;
			}
			else
			{
				if ((vec.z = floor(hitbox[1].z) - 0.5
							+ sqrt(data->power[TORCH] / 100.0)) - accel->z > hitbox[1].z)
				{
					accel->z = 0;
					hitbox[1].z = vec.z + 0.99999;
					hitbox[0].z = hitbox[0].z - z;
					return ;
				}
			}
		}
	}
	if (hitbox[0].y - y >= 0.1)
	{
		y += 1;
		x = floor(hitbox[0].x);
		if ((vec.y = data->map_to_save[x][y][(int)vec.z]))
		{
			if (vec.y < 41)
			{
				accel->z = 0;
				hitbox[1].z = floor(hitbox[1].z) + 0.99999;
				hitbox[0].z = hitbox[1].z - z;
				return ;
			}
			else
			{
				if ((vec.z = floor(hitbox[1].z) - 0.5
							+ sqrt(data->power[TORCH] / 100.0)) - accel->z > hitbox[1].z)
				{
					accel->z = 0;
					hitbox[1].z = vec.z + 0.99999;
					hitbox[0].z = hitbox[1].z - z;
					return ;
				}
			}
		}
		if (hitbox[0].x - x >= 0.1)
		{
			x = x + 1;
			if ((vec.y = data->map_to_save[x][y][(int)vec.z]))
			{
				if (vec.y < 41)
				{
					accel->z = 0;
					hitbox[1].z = floor(hitbox[1].z) + 0.99999;
					hitbox[0].z = hitbox[1].z - z;
					return ;
				}
				else
				{
					if ((vec.z = floor(hitbox[0].z) - 0.5
								+ sqrt(data->power[TORCH] / 100.0)) - accel->z > hitbox[0].z)
					{
						accel->z = 0;
						hitbox[1].z = vec.z + 0.99999;
						hitbox[0].z = hitbox[1].z - z;
						return ;
					}
				}
			}
		}
	}
	hitbox[0].z += accel->z;
	hitbox[1].z += accel->z;
}
