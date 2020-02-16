/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 14:36:05 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/10 21:14:57 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		leave_game(t_doom *data, t_player *player)
{
	player->camera.origin.x = -1;
	player->camera.origin.y = -1;
	player->camera.origin.z = -1;
	player->camera.direction = vec3d(0, 0, 1);
	player->camera.right = vec3d(1, 0, 0);
	player->camera.up = vec3d(0, 1, 0);
	player->acceleration.x = 0;
	player->acceleration.y = 0;
	player->acceleration.z = 0;
	player->speed = 0;
	player->health = 1000;
	data->player.camera.x_angle = 0;
	data->lib.cam_keys = 0;
}
