/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   damage.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smokhtar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 14:58:08 by smokhtar          #+#    #+#             */
/*   Updated: 2020/01/29 14:58:10 by smokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "weapons.h"

void    damages(t_player *victim, t_player *raper, double speed)
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