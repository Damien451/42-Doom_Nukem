/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 10:28:52 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/05 18:46:30 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "player.h"
#include "thread.h"
#include "octree.h"
#include "gameplay.h"
#include <pthread.h>
#include <math.h>
#include <sys/time.h>


static void	update_physics(t_doom *data)
{
	data->player.acceleration = data->player.physics.acceleration;
	data->player.camera.origin = data->player.physics.origin;
	data->player.camera.direction = data->player.physics.camera.direction;
	data->player.camera.up = data->player.physics.camera.up;
	data->player.camera.right = data->player.physics.camera.right;
}

static inline int	init_thread_structure(t_doom *data, t_octree *position)
{
	int				i;

	i = 0;
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
			&& data->lib.event.key.keysym.sym == SDLK_ESCAPE
			&& data->state == PLAYING)
			switch_state(data, PLAYING, PAUSE);
		else if(data->lib.event.type == SDL_KEYDOWN
			&& data->lib.event.key.keysym.sym == SDLK_ESCAPE)
		{
			leave_game(data, &data->player);
			switch_state(data, EDITION_MODE, EDITOR);
		}
		else if (data->lib.event.type == SDL_MOUSEMOTION)
			camera_mouse_motion(&data->player.physics.camera
					, &data->lib.event.motion.xrel
					, &data->lib.event.motion.yrel
					, &data->player.sensitivity);
		else if (data->lib.event.type == SDL_MOUSEBUTTONDOWN
			&& data->lib.event.button.button == SDL_BUTTON_RIGHT)
			data->lib.cam_keys |= RIGHT_CLICK;
		else if (data->lib.event.type == SDL_MOUSEBUTTONUP
			&& data->lib.event.button.button == SDL_BUTTON_RIGHT)
				data->lib.cam_keys &= ~RIGHT_CLICK;
		else if (data->lib.event.type == SDL_MOUSEBUTTONDOWN
			&& data->lib.event.button.button == SDL_BUTTON_LEFT)
			data->lib.cam_keys |= LEFT_CLICK;
		else if (data->lib.event.type == SDL_MOUSEBUTTONUP
			&& data->lib.event.button.button == SDL_BUTTON_LEFT)
				data->lib.cam_keys &= ~LEFT_CLICK;
		camera_press_key(&data->lib.event, &data->tabinputs, data);
	}
}

int					raytracing(t_doom *data)
{
	t_octree		*position;
	t_thread		thread;
	struct timeval	time;
	long			wait;
	int				i;
	static long		max = 0;
	double			tmp;

//	gettimeofday(&time, NULL);
//	wait = time.tv_sec * 1000000 + time.tv_usec;
	position = find_actual_position(&data->player.camera.origin, data->octree);
	data->player_light.position = data->player.camera.origin;
	data->player_light.position.y -= 0.375;
	data->player_light.position = vec3d_add(data->player_light.position, vec3d_scalar(data->player.camera.right, 0.2));
	tmp = vec3d_length2(data->player.acceleration);
	data->oriented_light = vec3d_add(data->player.camera.direction, vec3d_add(vec3d_scalar(data->player.camera.up, data->oriented[2] - 0.125), vec3d_scalar(data->player.camera.right, data->oriented[3])));
	data->oriented[2] += (data->oriented[0] * tmp / 30);
	if (data->oriented[2] > 0.05 || data->oriented[2] < -0.05)
		data->oriented[0] *= -1;
	data->oriented[3] += (data->oriented[1] * tmp / 30);
	if (data->oriented[3] > 0.05 || data->oriented[3] < -0.05)
		data->oriented[1] *= -1;
	data->actual_i = 2;
	sun(data);
	if (data->lib.cam_keys & BEST_SAMPLING)
		data->sampling = 1;
	else
		data->sampling = 4;
	if (init_thread_structure(data, position) == 1)
		return (1);
	event_loop(data);
	add_clipping_for_each_point(data, &data->player);
	actualize_torch(data);
//	thread.data = data;
//	thread.frame = data->samplingt[data->sampling - 1][0] * 2 - 4;
//	thread.mutex = &data->mutex;
//	thread.ray.node = position;
//	thread.ray.origin = data->player.camera.origin;
//	thread.ray.find_parent[0] = &find_parent_x;
///	thread.ray.find_parent[1] = &find_parent_y;
//	thread.ray.find_parent[2] = &find_parent_z;
//	launch_rays2(&thread);
//	gettimeofday(&time, NULL);
//	wait = time.tv_sec * 1000000 + time.tv_usec - wait;
//	if (wait > max)
//	{
//		printf("time to compute everything = %ld microseconds\n", wait);
//		max = wait;
//	}
	i = 0;
	while (i < NBR_THREAD)
		pthread_join(data->thread[i++].thread, NULL);
	update_physics(data);
	if ((data->lib.cam_keys & RIGHT_CLICK) || (data->lib.cam_keys & LEFT_CLICK))
	{
		interaction(data, data->lib.cam_keys);
		if (data->lib.cam_keys & RIGHT_CLICK)
			data->lib.cam_keys &= ~RIGHT_CLICK;
		else if (data->lib.cam_keys & LEFT_CLICK)
			data->lib.cam_keys &= ~LEFT_CLICK;
	}
	return (0);
}
