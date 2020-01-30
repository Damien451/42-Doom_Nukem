/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_hitbox.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:31:51 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/30 15:13:51 by roduquen         ###   ########.fr       */
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
	static double	up = 0.0;
	t_vec3d			new_pos;
	t_vec3d			new_acceleration;
	t_vec3d			hitbox[2];
	double			y;

	if ((data->lib.cam_keys & SQUAT) && up < 1.0 && data->player.camera.origin.y  < 63.0 && !data->map_to_save[(int)data->player.camera.origin.x][(int)data->player.camera.origin.y + 1][(int)data->player.camera.origin.z])
	{
		up += (1.0 / 10.0);
		y = 0.7 + up;
	}
	else if (data->lib.cam_keys & SQUAT && data->player.camera.origin.y < 63.0 && !data->map_to_save[(int)data->player.camera.origin.x][(int)data->player.camera.origin.y + 1][(int)data->player.camera.origin.z])
	{
		data->lib.cam_keys &= ~SQUAT;
		up = 0.0;
		y = 1.7;
	}
	else if (data->lib.cam_keys & CRAWL)
		y = 0.7;
	else
		y = 1.7;
	camera_event_translate(data);
	new_pos = data->player.camera.origin;
	if (data->lib.cam_keys & SQUAT && data->player.camera.origin.y  < 63.0 && !data->map_to_save[(int)data->player.camera.origin.x][(int)data->player.camera.origin.y + 1][(int)data->player.camera.origin.z])
		new_pos.y += (1.1 / 10.0);
	hitbox[0].x = new_pos.x - 0.2;
	hitbox[0].y = new_pos.y - y + 0.2;
	hitbox[0].z = new_pos.z - 0.2;
	if (hitbox[0].x < 0.3)
		hitbox[0].x = 0.3;
	if (hitbox[0].y < 0.3)
		hitbox[0].y = 0.3;
	if (hitbox[0].z < 0.3)
		hitbox[0].z = 0.3;
	hitbox[1].x = hitbox[0].x + 0.4;
	hitbox[1].y = hitbox[0].y + y;
	hitbox[1].z = hitbox[0].z + 0.4;
	new_acceleration = player->acceleration;
	if (new_acceleration.y < 0)
		check_y_min(data, &new_acceleration, hitbox, y);
	else
		check_y_max(data, &new_acceleration, hitbox, y);
	if (new_acceleration.x < 0)
		check_x_min(data, &new_acceleration, hitbox, 0.4);
	else
		check_x_max(data, &new_acceleration, hitbox, 0.4);
	if (new_acceleration.z < 0)
		check_z_min(data, &new_acceleration, hitbox, 0.4);
	else
		check_z_max(data, &new_acceleration, hitbox, 0.4);
	new_pos.x = hitbox[0].x + 0.2;
	new_pos.z = hitbox[0].z + 0.2;
	new_pos.y = hitbox[0].y + y - 0.2;
	if (data->lib.cam_keys & SQUAT)
		new_pos.y = hitbox[1].y - 0.2;
	if (new_pos.y < y - 0.2)
		new_pos.y = y - 0.2;
	data->player.physics.acceleration = new_acceleration;
	data->player.physics.origin = new_pos;
}
