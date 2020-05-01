/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_y_min.c                                      :+:      :+:    :+:   */
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
		accel->y = 0;
		hitbox[0].y = floor(hitbox[0].y);
		hitbox[1].y = hitbox[0].y + vec[1].x;
		return (1);
	}
	return (0);
}

static void		init_vec(t_vec3d vec[2], t_vec3d hitbox[2], double y
	, t_vec3d *accel)
{
	vec[1].x = y;
	vec[0].x = floor(hitbox[0].x);
	vec[0].z = floor(hitbox[0].z);
	vec[0].y = floor(hitbox[0].y + accel->y);
}

static void		update_hitbox(t_vec3d hitbox[2], t_vec3d *accel, t_vec3d vec[2])
{
	hitbox[0].y += accel->y;
	hitbox[1].y += accel->y;
	if (hitbox[0].y < 0.3)
	{
		accel->y = 0;
		hitbox[0].y = 0.3;
		hitbox[1].y = hitbox[0].y + vec[1].x;
	}
}

void			check_y_min(t_doom *data, t_vec3d *accel
		, t_vec3d hitbox[2], double y)
{
	t_vec3d		vec[2];

	init_vec(vec, hitbox, y, accel);
	if (verify_if_clipped(data, vec, accel, hitbox))
		return ;
	if (floor(hitbox[1].z) != vec[0].z)
	{
		vec[0].z = vec[0].z + 1.0;
		if (verify_if_clipped(data, vec, accel, hitbox))
			return ;
		vec[0].z = vec[0].z - 1;
	}
	if (floor(hitbox[1].x) != vec[0].x)
	{
		vec[0].x = vec[0].x + 1;
		if (verify_if_clipped(data, vec, accel, hitbox))
			return ;
		if (floor(hitbox[1].z) != vec[0].z)
		{
			vec[0].z = vec[0].z + 1;
			if (verify_if_clipped(data, vec, accel, hitbox))
				return ;
		}
	}
	update_hitbox(hitbox, accel, vec);
}
