/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_octree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:09:19 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/17 19:03:01 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include <math.h>

unsigned int		print_octree(t_vec3d intersect)
{
	unsigned int color;

	color = 0;
	if (intersect.x == floor(intersect.x) && ((intersect.y <= floor(intersect.y)
		+ 0.05 && intersect.y >= floor(intersect.y) - 0.05)
		|| (intersect.z <= floor(intersect.z) + 0.05
		&& intersect.z >= floor(intersect.z) - 0.05)))
		color = 127 | 127 << 16 | 127 << 8;
	else if (intersect.y == floor(intersect.y) && ((intersect.x <=
		floor(intersect.x) + 0.05 && intersect.x >= floor(intersect.x) - 0.05)
		|| (intersect.z <= floor(intersect.z) + 0.05
		&& intersect.z >= floor(intersect.z) - 0.05)))
		color = 127 | 127 << 16 | 127 << 8;
	else if (intersect.z == floor(intersect.z) && ((intersect.y <=
		floor(intersect.y) + 0.05 && intersect.y >= floor(intersect.y) - 0.05)
		|| (intersect.x <= floor(intersect.x) + 0.05
		&& intersect.x >= floor(intersect.x) - 0.05)))
		color = 127 | 127 << 16 | 127 << 8;
	return (color);
}
