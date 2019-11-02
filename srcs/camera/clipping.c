/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 21:07:09 by roduquen          #+#    #+#             */
/*   Updated: 2019/11/02 22:32:31 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "doom.h"
#include "vec3.h"
#include <math.h>

int			check_player_clipping(t_vec3d *acceleration, t_vec3d *new_pos
	, char map[64][64][64], t_vec3d position)
{
	if (map[(int)(new_pos->x)][(int)position.y][(int)position.z])
	{
		if (new_pos->x < position.x)
			new_pos->x = floor(new_pos->x) + 1.001;
		else
			new_pos->x = floor(new_pos->x) - 0.001;
		acceleration->x = 0;
	}
	if (map[(int)new_pos->x][(int)(new_pos->y)][(int)position.z])
	{
		if (new_pos->y < position.y)
			new_pos->y = floor(new_pos->y) + 1.001;
		else
			new_pos->y = floor(new_pos->y) - 0.001;
		acceleration->y = 0;
	}
	if (map[(int)new_pos->x][(int)(new_pos->y)][(int)new_pos->z])
	{
		if (new_pos->z < position.z)
			new_pos->z = floor(new_pos->z) + 1.001;
		else
			new_pos->z = floor(new_pos->z) - 0.001;
		acceleration->z = 0;
	}
	return (0);
}

int			check_camera_clipping(t_vec3d *acceleration, t_vec3d *new_pos
	, char map[64][64][64], t_vec3d position)
{
	if (map[(int)(new_pos->x)][(int)(position.y)][(int)position.z])
	{
		if (new_pos->x < position.x)
			new_pos->x = floor(new_pos->x) + 1.001;
		else
			new_pos->x = floor(new_pos->x) - 0.001;
	}
	if (map[(int)new_pos->x][(int)(new_pos->y)][(int)position.z])
	{
		new_pos->y = floor(new_pos->y) - 0.001;
		acceleration->y = -0.01;
	}
	if (map[(int)new_pos->x][(int)(new_pos->y)][(int)new_pos->z])
	{
		if (new_pos->z < position.z)
			new_pos->z = floor(new_pos->z) + 1.001;
		else
			new_pos->z = floor(new_pos->z) - 0.001;
	}
	return (0);
}
