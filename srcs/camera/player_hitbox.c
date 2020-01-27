/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_hitbox.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:31:51 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/26 18:39:01 by roduquen         ###   ########.fr       */
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

void			add_clipping_for_each_point(t_doom *data, t_player *player)
{
	t_vec3d	new_pos;
	t_vec3d	new_acceleration;
	t_vec3d	hitbox[2];

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
	new_acceleration = player->acceleration;
	if (new_acceleration.y < 0)
		check_y_min(data, &new_acceleration, hitbox);
	else
		check_y_max(data, &new_acceleration, hitbox);
	if (new_acceleration.z < 0)
		check_z_min(data, &new_acceleration, hitbox);
	else
		check_z_max(data, &new_acceleration, hitbox);
//	if (new_acceleration.x < 0)
//		check_x_min(data, &new_acceleration, hitbox);
//	else
//		check_x_max(data, &new_acceleration, hitbox);
	new_pos.x = hitbox[0].x + 0.2;
	new_pos.y = hitbox[0].y + 1.5;
	new_pos.z = hitbox[0].z + 0.2;
	data->player.physics.acceleration = new_acceleration;
	data->player.physics.origin = new_pos;
}
