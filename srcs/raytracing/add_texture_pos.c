/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_texture_pos.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 09:10:26 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/27 23:19:54 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "vec3.h"
#include <math.h>

int	add_x_pos(t_vec3d intersect, const t_doom *const data)
{
	return (fill_percent_128(1.0 - (intersect.y - floor(intersect.y))
				, 1.0 - (intersect.z - floor(intersect.z))
				, data->lib.textures[(int)data->map_to_save
				[(int)intersect.x][(int)intersect.y][(int)intersect.z] - 1]));
}

int	add_y_pos(t_vec3d intersect, const t_doom *const data)
{
	return (fill_percent_128(intersect.x - floor(intersect.x)
				, intersect.z - floor(intersect.z)
				, data->lib.textures[(int)data->map_to_save
				[(int)intersect.x][(int)intersect.y][(int)intersect.z] - 1]));
}

int	add_z_pos(t_vec3d intersect, const t_doom *const data)
{
	return (fill_percent_128(1.0 - (intersect.y - floor(intersect.y))
				, 1.0 - (intersect.x - floor(intersect.x))
				, data->lib.textures[(int)data->map_to_save
				[(int)intersect.x][(int)intersect.y][(int)intersect.z] - 1]));
}
