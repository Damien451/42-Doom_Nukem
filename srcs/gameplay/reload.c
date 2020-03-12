/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reload.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 16:02:05 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/10 17:48:54 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "player.h"
#include "gameplay.h"

void		reload(t_player *player)
{
	int		ammo_needed;

    ammo_needed = 8 - player->inventory.ammo;
	player->inventory.ammo = (ammo_needed > player->inventory.ammo_stock ?
		player->inventory.ammo + player->inventory.ammo_stock
		: player->inventory.ammo + ammo_needed);
	player->inventory.ammo_stock = (player->inventory.ammo_stock
		- ammo_needed < 0 ? 0 : player->inventory.ammo_stock - ammo_needed);
}