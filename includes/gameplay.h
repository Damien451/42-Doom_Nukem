/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.h											:+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 13:35:56 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/15 13:36:13 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMEPLAY_H
# define GAMEPLAY_H

/*
** ====-* INCLUDES *-====
*/

# include "doom.h"

/*
** ====-* DEFINES *-====
*/

# define DISTANCE_MAX_BLOCK 4.0f

/*
** ====-* TYPEDEFS *-====
*/
typedef struct s_ray		t_ray;

typedef struct s_hit		t_hit;

/*
** ====-* STRUCTURES *-====
*/

struct						s_hit
{
	double					length;
	t_ray					*ray;
	int						face;
};

/*
** ====-* PROTOTYPES *-====
*/

void            			interaction(t_doom *data, unsigned int key);
int							check_if_not_in_map(t_hitbox hitbox,
	char map[64][64][64]);
void						move_hitbox(t_vec3d direction,
	t_hitbox hitbox, char map[64][64][64]);

#endif
