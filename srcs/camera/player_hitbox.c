/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_hitbox.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:31:51 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/27 14:21:09 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "player.h"

void			add_clipping_for_each_point(t_doom *data, t_player *player)
{
	static double	up = 0.0;
	t_vec3d			new_pos;
	t_vec3d			new_acceleration;
	t_vec3d			hitbox[2];
	double			y;
	if ((data->lib.cam_keys & SQUAT) && up < 0.75)
	{
		up += (0.75 / 10.0);
		y = 0.95 + up;
	}
	else if (data->lib.cam_keys & SQUAT)
	{
		data->lib.cam_keys &= ~SQUAT;
		up = 0.0;
		y = 1.7;
	}
	else if (data->lib.cam_keys & CRAWL)
		y = 0.95;
	else
		y = 1.7;
	camera_event_translate(data);
	new_pos = data->player.camera.origin;
	new_acceleration = player->acceleration;
	if (data->lib.cam_keys & SQUAT)
		new_pos.y += (0.80 / 10.0);
	hitbox[0].y = new_pos.y - y + 0.2;
	hitbox[0].x = data->player.camera.origin.x - 0.2;
	hitbox[0].z = data->player.camera.origin.z - 0.2;
	if (hitbox[0].x < 0.3)
		hitbox[0].x = 0.3;
	if (hitbox[0].y < 0.3)
		hitbox[0].y = 0.3;
	if (hitbox[0].z < 0.3)
		hitbox[0].z = 0.3;
	hitbox[1].x = hitbox[0].x + 0.4;
	hitbox[1].y = hitbox[0].y + y;
	hitbox[1].z = hitbox[0].z + 0.4;
	if (new_acceleration.y < 0)
		check_y_min(data, &new_acceleration, hitbox, y);
	else
		check_y_max(data, &new_acceleration, hitbox, y);
	hitbox[0].x = new_pos.x - 0.2;
	hitbox[1].x = hitbox[0].x + 0.4;
	if (new_acceleration.x < 0)
		check_x_min(data, &new_acceleration, hitbox, 0.4);
	else
		check_x_max(data, &new_acceleration, hitbox, 0.4);
	hitbox[0].z = new_pos.z - 0.2;
	hitbox[1].z = hitbox[0].z + 0.4;
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
