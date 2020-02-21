/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 00:16:21 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/21 18:19:53 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"


void			check_y_min(t_doom *data, t_vec3d *accel
	, t_vec3d hitbox[2], double y)
{
	int			x;
	int			z;
	t_vec3d		vec;

	x = floor(hitbox[0].x);
	z = floor(hitbox[0].z);
	vec.y = floor(hitbox[0].y + accel->y);
	if (data->map_to_save[x][(int)vec.y][z])
	{
		accel->y = 0;
		hitbox[0].y = floor(hitbox[0].y);
		hitbox[1].y = hitbox[0].y + y;
		return ;
	}
	if (floor(hitbox[1].z) != z)
	{
		z = z + 1;
		if (data->map_to_save[x][(int)vec.y][z])
		{
				accel->y = 0;
				hitbox[0].y = floor(hitbox[0].y);
				hitbox[1].y = hitbox[0].y + y;
				return ;
		}
		z = z - 1;
	}
	if (floor(hitbox[1].x) != x)
	{
		x = x + 1;
		if (data->map_to_save[x][(int)vec.y][z])
		{
			accel->y = 0;
			hitbox[0].y = floor(hitbox[0].y);
			hitbox[1].y = hitbox[0].y + y;
			return ;
		}
		if (floor(hitbox[1].z) != z)
		{
			z = z + 1;
			if (data->map_to_save[x][(int)vec.y][z])
			{
				accel->y = 0;
				hitbox[0].y = floor(hitbox[0].y);
				hitbox[1].y = hitbox[0].y + y;
				return ;
			}
		}
	}
	hitbox[0].y += accel->y;
	hitbox[1].y += accel->y;
	if (hitbox[0].y < 0.3)
	{
		accel->y = 0;
		hitbox[0].y = 0.3;
		hitbox[1].y = hitbox[0].y + y;
		return ;
	}
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
	if (data->map_to_save[x][(int)vec.y][z])
	{
		accel->y = -0.045;
		hitbox[1].y = vec.y - EPSILON;
		hitbox[0].y = hitbox[1].y - y;
		return ;
	}
	if (floor(hitbox[1].z) != z)
	{
		z = z + 1;
		if (data->map_to_save[x][(int)vec.y][z])
		{
			accel->y = -0.045;
			hitbox[1].y = vec.y - EPSILON;
			hitbox[0].y = hitbox[1].y - y;
			return ;
		}
		z = z - 1;
	}
	if (floor(hitbox[1].x) != x)
	{
		x = x + 1;
		if (data->map_to_save[x][(int)vec.y][z])
		{
			accel->y = -0.045;
			hitbox[1].y = vec.y - EPSILON;
			hitbox[0].y = hitbox[1].y - y;
			return ;
		}
		if (floor(hitbox[1].z) != z)
		{
			z = z + 1;
			if (data->map_to_save[x][(int)vec.y][z])
			{
				accel->y = -0.045;
				hitbox[1].y = vec.y - EPSILON;
				hitbox[0].y = hitbox[1].y - y;
				return ;
			}
		}
	}
	hitbox[0].y += accel->y;
	hitbox[1].y += accel->y;
	if (hitbox[1].y > 63.7)
	{
		accel->y = 0;
		hitbox[1].y = 63.7;
		hitbox[0].y = hitbox[1].y - y;
		return ;
	}
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
	if (data->map_to_save[(int)vec.x][y][z])
	{
		accel->x = 0;
		hitbox[0].x = floor(hitbox[0].x) + EPSILON;
		hitbox[1].x = hitbox[0].x + x;
		return ;
	}
	if (floor(hitbox[1].z) != z)
	{
		z = z + 1;
		if (data->map_to_save[(int)vec.x][y][z])
		{
			accel->x = 0;
			hitbox[0].x = floor(hitbox[0].x) + EPSILON;
			hitbox[1].x = hitbox[0].x + x;
			return ;
		}
		z = z - 1;
	}
	if (floor(hitbox[1].y) != y)
	{
		y = y + 1;
		if (data->map_to_save[(int)vec.x][y][z])
		{
			accel->x = 0;
			hitbox[0].x = floor(hitbox[0].x) + EPSILON;
			hitbox[1].x = hitbox[0].x + x;
			return ;
		}
		if (floor(hitbox[1].z) != z)
		{
			z = z + 1;
			if (data->map_to_save[(int)vec.x][y][z])
			{
				accel->x = 0;
				hitbox[0].x = floor(hitbox[0].x) + EPSILON;
				hitbox[1].x = hitbox[0].x + x;
				return ;
			}
			z = z - 1;
		}
		if (floor(hitbox[1].y) != y)
		{
			y = y + 1;
			if (data->map_to_save[(int)vec.x][y][z])
			{
				accel->x = 0;
				hitbox[0].x = floor(hitbox[0].x) + EPSILON;
				hitbox[1].x = hitbox[0].x + x;
				return ;
			}
			if (floor(hitbox[1].z) != z)
			{
				z = z + 1;
				if (data->map_to_save[(int)vec.x][y][z])
				{
					accel->x = 0;
					hitbox[0].x = floor(hitbox[0].x) + EPSILON;
					hitbox[1].x = hitbox[0].x + x;
					return ;
				}
				z = z - 1;
			}
		}
	}
	hitbox[0].x += accel->x;
	hitbox[1].x += accel->x;
	if (hitbox[0].x < 0.3)
	{
		accel->x = 0;
		hitbox[0].x = 0.3 + EPSILON;
		hitbox[1].x = hitbox[0].x + x;
		return ;
	}
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
	if (data->map_to_save[(int)vec.x][y][z])
	{
		accel->x = 0;
		hitbox[1].x = vec.x - EPSILON;
		hitbox[0].x = hitbox[1].x - x;
		return ;
	}
	if (floor(hitbox[1].z) != z)
	{
		z = z + 1;
		if (z < 64)
		{
			if (data->map_to_save[(int)vec.x][y][z])
			{
				accel->x = 0;
				hitbox[1].x = vec.x - EPSILON;
				hitbox[0].x = hitbox[1].x - x;
				return ;
			}
		}
		z = z - 1;
	}
	if (floor(hitbox[1].y) != y)
	{
		y = y + 1;
		if (data->map_to_save[(int)vec.x][y][z])
		{
			accel->x = 0;
			hitbox[1].x = vec.x - EPSILON;
			hitbox[0].x = hitbox[1].x - x;
			return ;
		}
		if (floor(hitbox[1].z) != z)
		{
			z = z + 1;
			if (data->map_to_save[(int)vec.x][y][z])
			{
				accel->x = 0;
				hitbox[1].x = vec.x - EPSILON;
				hitbox[0].x = hitbox[1].x - x;
				return ;
			}
			z = z - 1;
		}
		if (floor(hitbox[1].y) != y)
		{
			y = y + 1;
			if (data->map_to_save[(int)vec.x][y][z])
			{
				accel->x = 0;
				hitbox[1].x = vec.x - EPSILON;
				hitbox[0].x = hitbox[1].x - x;
				return ;
			}
			if (floor(hitbox[1].z) != z)
			{
				z = z + 1;
				if (data->map_to_save[(int)vec.x][y][z])
				{
					accel->x = 0;
					hitbox[1].x = vec.x - EPSILON;
					hitbox[0].x = hitbox[1].x - x;
					return ;
				}
				z = z - 1;
			}
		}
	}
	hitbox[0].x += accel->x;
	hitbox[1].x += accel->x;
	if (hitbox[1].x > 63.7)
	{
		accel->x = 0;
		hitbox[1].x = 63.7;
		hitbox[0].x = hitbox[1].x - x;
		return ;
	}
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
	if (data->map_to_save[x][y][(int)vec.z])
	{
		accel->z = 0;
		hitbox[0].z = floor(hitbox[0].z) + EPSILON;
		hitbox[1].z = hitbox[0].z + z;
		return ;
	}
	if (floor(hitbox[1].x) != x)
	{
		x = x + 1;
		if (data->map_to_save[x][y][(int)vec.z])
		{
			accel->z = 0;
			hitbox[0].z = floor(hitbox[0].z) + EPSILON;
			hitbox[1].z = hitbox[0].z + z;
			return ;
		}
		x = x - 1;
	}
	if (floor(hitbox[1].y) != y)
	{
		y = y + 1;
		if (data->map_to_save[x][y][(int)vec.z])
		{
			accel->z = 0;
			hitbox[0].z = floor(hitbox[0].z) + EPSILON;
			hitbox[1].z = hitbox[0].z + z;
			return ;
		}
		if (floor(hitbox[1].x) != x)
		{
			x = x + 1;
			if (data->map_to_save[x][y][(int)vec.z])
			{
				accel->z = 0;
				hitbox[0].z = floor(hitbox[0].z) + EPSILON;
				hitbox[1].z = hitbox[0].z + z;
				return ;
			}
			x = x - 1;
		}
		if (floor(hitbox[1].y) != y)
		{
			y = y + 1;
			if (data->map_to_save[x][y][(int)vec.z])
			{
				accel->z = 0;
				hitbox[0].z = floor(hitbox[0].z) + EPSILON;
				hitbox[1].z = hitbox[0].z + z;
				return ;
			}
			if (floor(hitbox[1].x) != x)
			{
				x = x + 1;
				if (data->map_to_save[x][y][(int)vec.z])
				{
					accel->z = 0;
					hitbox[0].z = floor(hitbox[0].z) + EPSILON;
					hitbox[1].z = hitbox[0].z + z;
					return ;
				}
				x = x - 1;
			}
		}
	}
	hitbox[0].z += accel->z;
	hitbox[1].z += accel->z;
	if (hitbox[0].z < 0.3)
	{
		accel->z = 0;
		hitbox[0].z = 0.3;
		hitbox[1].z = hitbox[0].z + z;
		return ;
	}
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
	if (data->map_to_save[x][y][(int)vec.z])
	{
		accel->z = 0;
		hitbox[1].z = vec.z - EPSILON;
		hitbox[0].z = hitbox[1].z - z;
		return ;
	}
	if (floor(hitbox[1].x) != x)
	{
		x = x + 1;
		if (data->map_to_save[x][y][(int)vec.z])
		{
			accel->z = 0;
			hitbox[1].z = vec.z - EPSILON;
			hitbox[0].z = hitbox[1].z - z;
			return ;
		}
		x = x - 1;
	}
	if (floor(hitbox[1].y) != y)
	{
		y = y + 1;
		if (data->map_to_save[x][y][(int)vec.z])
		{
			accel->z = 0;
			hitbox[1].z = vec.z - EPSILON;
			hitbox[0].z = hitbox[1].z - z;
			return ;
		}
		if (floor(hitbox[1].x) != x)
		{
			x = x + 1;
			if (data->map_to_save[x][y][(int)vec.z])
			{
				accel->z = 0;
				hitbox[1].z = vec.z - EPSILON;
				hitbox[0].z = hitbox[1].z - z;
				return ;
			}
			x = x - 1;
		}
		if (floor(hitbox[1].y) != y)
		{
			y = y + 1;
			if (data->map_to_save[x][y][(int)vec.z])
			{
				accel->z = 0;
				hitbox[1].z = vec.z - EPSILON;
				hitbox[0].z = hitbox[1].z - z;
				return ;
			}
			if (floor(hitbox[1].x) != x)
			{
				x = x + 1;
				if (data->map_to_save[x][y][(int)vec.z])
				{
					accel->z = 0;
					hitbox[1].z = vec.z - EPSILON;
					hitbox[0].z = hitbox[1].z - z;
					return ;
				}
				x = x - 1;
			}
		}
	}
	hitbox[0].z += accel->z;
	hitbox[1].z += accel->z;
	if (hitbox[1].z > 63.7)
	{
		accel->z = 0;
		hitbox[1].z = 63.7;
		hitbox[0].z = hitbox[1].z - z;
		return ;
	}
}
