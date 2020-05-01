/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   leave_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 14:36:05 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/04 16:01:22 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

void		leave_game(t_doom *data, t_player *player)
{
	reset_game_values(data, player);
	player->speed = 0;
	player->health = 1000;
}
