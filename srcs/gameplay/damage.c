/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 23:37:39 by dacuvill          #+#    #+#             */
/*   Updated: 2020/02/26 00:24:19 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "weapons.h"

void	damages(t_player *victim, t_player *raper, double speed)
{
	if (raper.inventory.weapon & CUT)
		victim.health -= speed * D_CUT;
	else if (raper.inventory.weapon & DEAGLE)
		victim.health -= speed * D_DEAGLE;
	else if (raper.inventory.weapon & AK47)
		victim.health -= speed * D_AK47;
	else if (raper.inventory.weapon & AWP)
		victim.health -= speed * D_AWP;
	else if (raper.inventory.weapon & M4)
		victim.health -= speed * D_M4;
}
