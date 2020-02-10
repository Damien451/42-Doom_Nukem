/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapons.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 13:35:56 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/15 13:36:13 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WEAPONS_H
# define WEAPONS_H

/*
** ====-* INCLUDES *-====
*/

/*
** ====-* DEFINES *-====
*/

# define CUT				0x1l
# define DEAGLE				0x2l
# define AK-47				0x4l

/*
** ====-* TYPEDEFS *-====
*/

typedef struct s_weapon		t_weapon;

/*
** ====-* STRUCTURES *-====
*/

struct						s_weapon
{
	long					weapons;
};

#endif
