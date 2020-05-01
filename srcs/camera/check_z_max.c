/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_z_max.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/20 00:16:21 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/21 18:19:53 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static int		verify_if_clipped(t_doom *data, t_vec3d vec[2], t_vec3d *accel
		, t_vec3d hitbox[2])
{
	if (data->map_to_save[(int)vec[0].x][(int)vec[0].y][(int)vec[0].z])
	{
		accel->z = 0;
		hitbox[1].z = vec[0].z - EPSILON;
		hitbox[0].z = hitbox[1].z - vec[1].x;
		return (1);
	}
	return (0);
}

static void		init_vec(t_vec3d vec[2], t_vec3d hitbox[2], double z
		, t_vec3d *accel)
{
	vec[1].x = z;
	vec[0].x = floor(hitbox[0].x);
	vec[0].z = floor(hitbox[1].z + accel->z);
	vec[0].y = floor(hitbox[0].y);
}

static int		do_the_work_again(t_doom *data, t_vec3d vec[2], t_vec3d *accel
	, t_vec3d hitbox[2])
{
	if (verify_if_clipped(data, vec, accel, hitbox))
		return (1);
	if (floor(hitbox[1].x) != vec[0].x)
	{
		vec[0].x = vec[0].x + 1;
		if (verify_if_clipped(data, vec, accel, hitbox))
			return (1);
		vec[0].x = vec[0].x - 1;
	}
	if (floor(hitbox[1].y) != vec[0].y)
	{
		vec[0].y = vec[0].y + 1;
		if (verify_if_clipped(data, vec, accel, hitbox))
			return (1);
		if (floor(hitbox[1].x) != vec[0].x)
		{
			vec[0].x = vec[0].x + 1;
			if (verify_if_clipped(data, vec, accel, hitbox))
				return (1);
			vec[0].x = vec[0].x - 1;
		}
	}
	return (0);
}

static void		update_hitbox(t_vec3d hitbox[2], t_vec3d *accel, t_vec3d vec[2])
{
	hitbox[0].z += accel->z;
	hitbox[1].z += accel->z;
	if (hitbox[1].z > 63.7)
	{
		accel->z = 0;
		hitbox[1].z = 63.7;
		hitbox[0].z = hitbox[1].z - vec[1].x;
	}
}

void			check_z_max(t_doom *data, t_vec3d *accel
		, t_vec3d hitbox[2], double z)
{
	t_vec3d		vec[2];

	init_vec(vec, hitbox, z, accel);
	if (verify_if_clipped(data, vec, accel, hitbox))
		return ;
	if (floor(hitbox[1].x) != vec[0].x)
	{
		vec[0].x = vec[0].x + 1;
		if (verify_if_clipped(data, vec, accel, hitbox))
			return ;
		vec[0].x = vec[0].x - 1;
	}
	if (floor(hitbox[1].y) != vec[0].y)
	{
		vec[0].y = vec[0].y + 1;
		if (do_the_work_again(data, vec, accel, hitbox))
			return ;
	}
	update_hitbox(hitbox, accel, vec);
}
