/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reset_game_values.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/04 15:53:40 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/05 11:51:41 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "gameplay.h"

int			reset_game_values(t_doom *data, t_player *player)
{
	data->lib.cam_keys = 0;
	player->health = 1000;
	player->camera.x_angle = 0;
	player->physics.camera.x_angle = 0;
	player->camera.direction = vec3d(0, 0, 1);
	player->camera.right = vec3d(1, 0, 0);
	player->camera.up = vec3d(0, 1, 0);
	player->acceleration.x = 0;
	player->acceleration.y = 0;
	player->acceleration.z = 0;
	player->speed = 0;
	set_player_spawn(data->map_to_save, &data->player.camera.origin);
	return (0);
}