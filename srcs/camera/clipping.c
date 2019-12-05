/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clipping.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 21:07:09 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/05 12:12:59 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include "doom.h"
#include "vec3.h"
#include <math.h>

int			add_vertex_clipping_z_min(t_vec3d *acceleration, t_vec3d *new_pos
	, char map[64][64][64], t_vec3d position)
{
	if (map[(int)(position.x)][(int)position.y][(int)new_pos->z])
	{
		new_pos->z = floor(new_pos->z) + 1.001;
		acceleration->z = 0;
		return (1);
	}
	return (0);
}

int			add_vertex_clipping_z_max(t_vec3d *acceleration, t_vec3d *new_pos
	, char map[64][64][64], t_vec3d position)
{
	if (map[(int)(position.x)][(int)position.y][(int)new_pos->z])
	{
		new_pos->z = floor(new_pos->z) - 0.001;
		acceleration->z = 0;
		return (1);
	}
	return (0);
}

int			add_vertex_clipping_x_min(t_vec3d *acceleration, t_vec3d *new_pos
	, char map[64][64][64], t_vec3d position)
{
	if (map[(int)(new_pos->x)][(int)position.y][(int)position.z])
	{
		new_pos->x = floor(new_pos->x) + 1.001;
		acceleration->x = 0;
		return (1);
	}
	return (0);
}

int			add_vertex_clipping_x_max(t_vec3d *acceleration, t_vec3d *new_pos
	, char map[64][64][64], t_vec3d position)
{
	if (map[(int)(new_pos->x)][(int)position.y][(int)position.z])
	{
		new_pos->x = floor(new_pos->x) - 0.001;
		acceleration->x = 0;
		return (1);
	}
	return (0);
}

int			add_vertex_clipping_y_min(t_vec3d *acceleration, t_vec3d *new_pos
	, char map[64][64][64], t_vec3d position)
{
	if (map[(int)position.x][(int)(new_pos->y)][(int)position.z])
	{
		new_pos->y = floor(new_pos->y) + 1.001;
		acceleration->y = 0;
		return (1);
	}
	return (0);
}

int			add_vertex_clipping_y_max(t_vec3d *acceleration, t_vec3d *new_pos
	, char map[64][64][64], t_vec3d position)
{
	if (map[(int)position.x][(int)(new_pos->y)][(int)position.z])
	{
		new_pos->y = floor(new_pos->y) - 0.001;
		acceleration->y = 0;
		return (1);
	}
	return (0);
}

int			add_vertex_clipping(t_vec3d *acceleration, t_vec3d *new_pos
	, char map[64][64][64], t_vec3d position)
{
	int		check;

	check = 0;
	if (map[(int)(new_pos->x)][(int)position.y][(int)position.z])
	{
	//	if (new_pos->x < position.x)
			new_pos->x = floor(new_pos->x) + 1.001;
	//	else
	//		new_pos->x = floor(new_pos->x) - 0.001;
		acceleration->x = 0;
		check = 1;
	}
//	if (map[(int)new_pos->x][(int)(new_pos->y)][(int)position.z])
//	{
//		if (new_pos->y < position.y)
//			new_pos->y = floor(new_pos->y) + 1.001;
//		else
//			new_pos->y = floor(new_pos->y) - 0.001;
//		acceleration->y = 0;
//		check = 1;
//	}
//	if (map[(int)new_pos->x][(int)(new_pos->y)][(int)new_pos->z])
//	{
//		if (new_pos->z < position.z)
//			new_pos->z = floor(new_pos->z) + 1.001;
//		else
//			new_pos->z = floor(new_pos->z) - 0.001;
//		acceleration->z = 0;
//		check = 1;
//	}
	return (check);
}
