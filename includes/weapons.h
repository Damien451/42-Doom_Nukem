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
#include "doom.h"

/*
** ====-* DEFINES *-====
*/

# define CUT				0x1l
# define DEAGLE				0x2l
# define AK47				0x4l
# define AWP				0x8l
# define M4					0x16l

# define D_CUT				50
# define D_DEAGLE			35
# define D_AK47				34
# define D_AWP				119
# define D_M4				31

/*
** ====-* TYPEDEFS *-====
*/
typedef struct s_ray			t_ray;

typedef struct s_weapon		t_weapon;
typedef struct s_hit		t_hit;

t_ray       				*send_bullet(const t_camera camera, const t_doom *const data);

/*
** ====-* STRUCTURES *-====
*/

struct						s_weapon
{
	long					name;
};

struct						s_hit
{
	double					length;
};

#endif
