/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sun_animation.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:01:29 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/03 12:02:34 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "vec3.h"

void					sun(t_doom *data)
{
	static int			frame = 0;

	if (frame == 0)
	{
		data->sun_light->position.x = 0;
		data->sun_light->position.y = 63 + EPSILON;
		data->sun_light->position.z = 0;
	}
	else
	{
		data->sun_light->position.z += 0.05;
		data->sun_light->position.x += 0.05;
		if (data->sun_light->position.z > 64.0)
		{
			data->sun_light->position.z = 0.0;
			data->sun_light->position.x = 0.0;
			frame = 0;
		}
	}
	frame++;
}
