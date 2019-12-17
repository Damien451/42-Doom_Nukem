/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 10:28:52 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/16 23:37:28 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "player.h"
#include "thread.h"
#include "octree.h"
#include <pthread.h>
#include <math.h>

static inline int	init_thread_structure(t_doom *data)
{
	t_octree		*position;
	int				i;

	i = 0;
	position = find_actual_position(&data->player.camera.origin, data->octree);
	z_buffer(data->entities, data->player, (t_zbuf*)&(data->zbuf));
	while (i < NBR_THREAD)
	{
		data->thread[i].data = data;
		data->thread[i].frame = data->samplingt[data->sampling - 1][0] * 2 - 4;
		data->thread[i].mutex = &data->mutex;
		data->thread[i].ray.node = position;
		data->thread[i].ray.origin = data->player.camera.origin;
		data->thread[i].ray.find_parent[0] = &find_parent_x;
		data->thread[i].ray.find_parent[1] = &find_parent_y;
		data->thread[i].ray.find_parent[2] = &find_parent_z;
		if (pthread_create(&data->thread[i].thread, NULL, (*launch_rays)
					, &data->thread[i]) < 0)
			return (1);
		i++;
	}
	return (0);
}

void				interaction(t_doom *data, t_vec3d pos)
{
	int			new[3];

	new[0] = (int)floor(pos.x);
	new[1] = (int)floor(pos.y);
	new[2] = (int)floor(pos.z);
	if (new[0] >= 0 && new[0] < 64)
	{
		if (data->map_to_save[new[0]][new[1]][new[2]])
			data->map_to_save[new[0]][new[1]][new[2]] = 0;
		else
			data->map_to_save[new[0]][new[1]][new[2]]
				= data->player.inventory.selected_block;
	}
}

void				actualize_torch(t_doom *data)
{
	static int	frame[4] = {0};
	static int	nbr_frame[4] = {0};
	int			i;

	i = 0;
	while (i < 4)
	{
		if (frame[i] == nbr_frame[i])
		{
			data->power[TORCH + i] = 2 + (rand() & 3);
			frame[i] = 0;
			nbr_frame[i] = data->power[TORCH + i] + (rand() & 3);
		}
		else
			frame[i]++;
		i++;
	}
}

int					raytracing(t_doom *data)
{
	int				i;

	data->actual_i = 2;
	data->sampling = 4;
	if (data->lib.cam_keys & COURSE)
		data->sampling = 1;
	sun(data);
	SDL_RenderClear(data->lib.renderer);
	if (init_thread_structure(data) == 1)
		return (1);
	add_clipping_for_each_point(data, &data->player);
	actualize_torch(data);
	i = 0;
	while (i < NBR_THREAD)
		pthread_join(data->thread[i++].thread, NULL);
	if (data->lib.cam_keys & DESTROY)
	{
		interaction(data, vec3d_add(data->player.camera.origin
			, vec3d_scalar(data->player.camera.direction, 2)));
		data->lib.cam_keys &= ~DESTROY;
	}
	free_octree(data->octree);
	create_octree(data);
	return (0);
}
