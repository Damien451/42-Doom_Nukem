/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave_state_game.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 14:36:05 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/17 14:35:30 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		leave_state_game(t_doom *data, t_player *player)
{
	player->camera.origin.x = -1;
	player->camera.origin.y = -1;
	player->camera.origin.z = -1;
	player->acceleration.x = 0;
	player->acceleration.y = 0;
	player->acceleration.z = 0;
	player->speed = 0;
	player->health = 1000;
	data->lib.cam_keys = 0;
}
