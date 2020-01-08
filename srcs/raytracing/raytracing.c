/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 10:28:52 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/08 18:54:49 by roduquen         ###   ########.fr       */
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
	//z_buffer(data->entities, data->player, (t_zbuf*)&(data->zbuf));
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
	static double	value = 0.125;

	if (data->power[TORCH] <= 2)
	{
		value = 0.125;
		data->power[TORCH] = 2;
	}
	if (data->power[TORCH] >= 5)
	{
		value = -0.125;
		data->power[TORCH] = 5;
	}
	data->power[TORCH] += value;
}

static void			event_loop(t_doom *data)
{
	data->player.physics.camera.direction = data->player.camera.direction;
	data->player.physics.camera.right = data->player.camera.right;
	data->player.physics.camera.up = data->player.camera.up;
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN
			&& data->lib.event.key.keysym.sym == SDLK_ESCAPE)
			switch_state(data, PLAYING, PAUSE);
		else if (data->lib.event.type == SDL_MOUSEMOTION)
			camera_mouse_motion(&data->player.physics.camera
					, &data->lib.event.motion.xrel
					, &data->lib.event.motion.yrel
					, &data->player.sensitivity);
		else if (data->lib.event.type == SDL_MOUSEBUTTONDOWN)
			data->lib.cam_keys |= DESTROY;
		camera_press_key(&data->lib.event, &data->tabinputs, data);
	}
}

int					raytracing(t_doom *data)
{
	int				i;
//	unsigned long	time;
//	long			wait;

	data->actual_i = 2;
	sun(data);
	data->sampling = 4;
	if (init_thread_structure(data) == 1)
		return (1);
//	time = SDL_GetTicks();
	event_loop(data);
	add_clipping_for_each_point(data, &data->player);
	minimap(data->map_to_save, &data->player, &data->lib);
	actualize_torch(data);
//	printf("time to compute non-image during the frame = %ld\n", (wait = SDL_GetTicks() - time));
	i = 0;
	while (i < NBR_THREAD)
		pthread_join(data->thread[i++].thread, NULL);
//	printf("time to finish the frame = %lu\n", SDL_GetTicks() - time);
	if (data->lib.cam_keys & DESTROY)
	{
		interaction(data, vec3d_add(data->player.camera.origin
					, vec3d_scalar(data->player.camera.direction, 2)));
		data->lib.cam_keys &= ~DESTROY;
		free_octree(data->octree);
		create_octree(data);
	}
	return (0);
}
