/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_gun.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 11:51:25 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/03 11:52:30 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include "doom.h"

void					light_gun(t_doom *data)
{
	static t_vec3d	position = {-5, 0, 0};
	static t_vec3d	direction = {0, 0, 0};

	if (position.x < 0)
	{
		position = data->player.camera.origin;
		direction = data->player.camera.direction;
	}
	else
	{
		position = vec3d_add(position, direction);
		data->light.position = position;
		if (position.x > 64.0 || position.x < 0.0 || position.y > 64.0
				|| position.y < 0.0 || position.z > 64.0 || position.z < 0.0)
		{
			position.x = -1;
			data->ball = 0;
		}
	}
}
