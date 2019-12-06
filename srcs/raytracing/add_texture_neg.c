/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_texture_neg.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 09:09:53 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/02 09:21:35 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "vec3.h"
#include <math.h>

int	add_x_neg(t_vec3d intersect, const t_doom *const data)
{
	return (fill_percent_128(1.0 - (intersect.y - floor(intersect.y))
				, intersect.z - floor(intersect.z)
				, data->lib.textures_block[(int)data->map_to_save
				[(int)intersect.x - 1][(int)intersect.y][(int)intersect.z]
				- 1]));
}

int	add_y_neg(t_vec3d intersect, const t_doom *const data)
{
	return (fill_percent_128(intersect.x - floor(intersect.x)
				, intersect.z - floor(intersect.z)
				, data->lib.textures_block[(int)data->map_to_save
				[(int)intersect.x][(int)intersect.y - 1][(int)intersect.z]
				- 1]));
}

int	add_z_neg(t_vec3d intersect, const t_doom *const data)
{
	return (fill_percent_128(1.0 - (intersect.y - floor(intersect.y))
				, intersect.x - floor(intersect.x)
				, data->lib.textures_block[(int)data->map_to_save
				[(int)intersect.x][(int)intersect.y][(int)intersect.z - 1]
				- 1]));
}
