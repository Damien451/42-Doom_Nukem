/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_weapon.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/08 18:38:43 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/09 19:54:13 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "player.h"

static int	anim_weapon2(int *typeanim)
{
	static int	texture = 2;
	static int	frame = 27;

	printf("reload = %d\n", *typeanim);
	if (frame > 0)
	{
		if (frame % 2 == 0)
			texture++;
		frame--;
	}
	else if (frame == 0)
	{
		frame = 27;
		texture = 2;
		*typeanim = WEAPON_NEUTRAL;
	}
	return (texture);
}

int			anim_weapon(int *typeanim)
{
	static int	texture = 0;
	static int	frame = 0;

	frame = (frame > 0 ? frame - 1 : frame);
	if (*typeanim == WEAPON_SHOT)
	{
		frame = 2;
		texture = 1;
		*typeanim = WEAPON_RECOIL;
	}
	else if (*typeanim == WEAPON_RELOAD)
		return (anim_weapon2(typeanim));
	if (frame == 0)
	{
		texture = 0;
		if (*typeanim != WEAPON_RECOIL)
			*typeanim = WEAPON_NEUTRAL;
		else
		{
			texture = -1;
			*typeanim = WEAPON_NEUTRAL;
		}
	}
	return (texture);
}
