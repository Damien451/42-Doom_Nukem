/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_textures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 10:36:11 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/09 17:40:50 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "vec3.h"

static inline unsigned int	fill_percent_512(double a, double b
		, unsigned int tab[512 * 512])
{
	return (tab[(int)(a * 512) * 512 + (int)(b * 512)]);
}

unsigned int				fill_percent_128(double a, double b
		, unsigned int tab[128 * 128])
{
	return (tab[(int)(a * 128) * 128 + (int)(b * 128)]);
}

unsigned int				add_skybox(t_vec3d intersect, unsigned int **skybox)
{
	if (intersect.x == 64.0)
		return ((fill_percent_512((64.0 - intersect.y) / 64.0
					, intersect.z / 64.0, skybox[0]) & 0xFEFEFE) >> 1);
	else if (intersect.x == 0.0)
		return ((fill_percent_512((64.0 - intersect.y) / 64.0
					, (64.0 - intersect.z) / 64.0, skybox[2]) & 0xFEFEFE) >> 1);
	else if (intersect.y == 64.0)
		return ((fill_percent_512(intersect.x / 64.0
					, intersect.z / 64.0, skybox[4]) & 0xFEFEFE) >> 1);
	else if (intersect.y == 0.0)
		return ((fill_percent_512(intersect.x / 64.0
					, intersect.z / 64.0, skybox[5]) & 0xFEFEFE) >> 1);
	else if (intersect.z == 64.0)
	{
		return ((fill_percent_512((64.0 - intersect.y) / 64.0
					, (64.0 - intersect.x) / 64.0, skybox[1]) & 0xFEFEFE) >> 1);
	}
	return ((fill_percent_512((64.0 - intersect.y) / 64.0
				, intersect.x / 64.0, skybox[3]) & 0xFEFEFE) >> 1);
}
