/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave_state_game.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 14:36:05 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/15 14:36:06 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void	leave_state_game(t_player *player)
{
	player->camera.origin.x = -1;
	player->camera.origin.y = -1;
	player->camera.origin.z = -1;
}
