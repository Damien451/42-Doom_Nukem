/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_hitbox.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 13:31:51 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/06 16:27:52 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "player.h"

static void		set_up_and_y(double *y, double *up, t_doom *data)
{
	if ((data->lib.cam_keys & SQUAT) && *up < 0.75)
	{
		*up += (0.75 / 10.0);
		*y = 0.95 + *up;
		data->player.acceleration = vec3d(0, 0, 0);
	}
	else if (data->lib.cam_keys & SQUAT)
	{
		data->lib.cam_keys &= ~SQUAT;
		*up = 0.0;
		*y = 1.7;
		data->player.acceleration = vec3d(0, 0, 0);
	}
	else if (data->lib.cam_keys & CRAWL)
		*y = 0.95;
	else
		*y = 1.7;
}

static void		init_hitbox(t_vec3d hitbox[2], t_vec3d new_pos, double y)
{
	hitbox[0].y = new_pos.y - y + 0.2;
	hitbox[0].x = new_pos.x - 0.2;
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
}

static void		perform_clipping(t_vec3d *accel, t_doom *data, t_vec3d hitbox[2]
	, double y)
{
	if (accel->y < 0)
		check_y_min(data, accel, hitbox, y);
	else
		check_y_max(data, accel, hitbox, y);
	if (accel->x < 0)
		check_x_min(data, accel, hitbox, 0.4);
	else
		check_x_max(data, accel, hitbox, 0.4);
	if (accel->z < 0)
		check_z_min(data, accel, hitbox, 0.4);
	else
		check_z_max(data, accel, hitbox, 0.4);
}

static void		update_position(t_doom *data, t_vec3d *new_pos
	, t_vec3d hitbox[2], double y)
{
	new_pos->x = hitbox[0].x + 0.2;
	new_pos->z = hitbox[0].z + 0.2;
	new_pos->y = hitbox[0].y + y - 0.2;
	if (data->lib.cam_keys & SQUAT)
		new_pos->y = hitbox[1].y - 0.2;
	if (new_pos->y < y - 0.2)
		new_pos->y = y - 0.2;
}

void			add_clipping_for_each_point(t_doom *data, t_player *player)
{
	static double	up = 0.0;
	t_vec3d			new_pos;
	t_vec3d			new_acceleration;
	t_vec3d			hitbox[2];
	double			y;

	set_up_and_y(&y, &up, data);
	camera_event_translate(data);
	new_pos = data->player.camera.origin;
	new_acceleration = player->acceleration;
	if (data->lib.cam_keys & SQUAT)
		new_pos.y += (0.80 / 10.0);
	init_hitbox(hitbox, new_pos, y);
	perform_clipping(&new_acceleration, data, hitbox, y);
	update_position(data, &new_pos, hitbox, y);
	data->player.physics.acceleration = new_acceleration;
	data->player.physics.origin = new_pos;
}
