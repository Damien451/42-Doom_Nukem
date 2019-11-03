/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <roduquen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 10:28:52 by roduquen          #+#    #+#             */
/*   Updated: 2019/11/03 00:57:31 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "player.h"
#include "thread.h"
#include "octree.h"
#include <pthread.h>
#include <math.h>

static inline t_vec3d	ray_create(int y, int x, t_doom *data)
{
	double	pixel_x;
	double	pixel_y;
	t_vec3d	dir;

	pixel_x = (2 * (x + .5) / WIDTH - 1) * FOV;
	pixel_y = (1 - (2 * (y + .5) / HEIGHT)) * POV;
	dir = vec3d_scalar(data->player.camera.right, pixel_x);
	dir = vec3d_add(dir, vec3d_scalar(data->player.camera.up, pixel_y));
	dir = vec3d_add(dir, data->player.camera.direction);
	return (vec3d_unit(dir));
}

static inline void		apply_sampling(unsigned int *image, unsigned int color
	, int sampling, int position)
{
	int				i;
	int				j;
	int				tmp;

	i = 0;
	while (i < sampling)
	{
		tmp = position + i - sampling / 2;
		j = 0;
		while (j < sampling)
		{
			image[tmp + (j - sampling / 2) * WIDTH] = color;
			j++;
		}
		i++;
	}
}

void					*launch_rays(void *ptr)
{
	t_doom			*data;
	int				i;
	int				j;
	t_octree		*position;

	data = ((t_thread*)ptr)->data;
	position = find_actual_position(&data->player.camera.origin, data->octree);
	i = 51 + ((t_thread*)ptr)->num + data->sampling / 2;
	while (i < WIDTH - 51)
	{
		j = 51 + data->sampling / 2;
		while (j < 829)
		{
			apply_sampling(data->lib.image
				, ray_intersect(ray_create(j - 51, i - 51, data)
				, data->player.camera.origin, position, data)
				, data->sampling, i + j * WIDTH);
			j += data->sampling;
		}
		i += NBR_THREAD * data->sampling;
	}
	pthread_exit(0);
}

int						raytracing(t_doom *data)
{
	t_thread		thread[NBR_THREAD];
	int				i;

	i = 0;
	SDL_RenderClear(data->lib.renderer);
	if (!data->lib.cam_keys && data->sampling != 1)
		data->sampling = 1;
	data->sampling = 5;
	while (i < NBR_THREAD)
	{
		thread[i].data = data;
		thread[i].image = data->lib.image;
		thread[i].num = data->sampling * (i);
		thread[i].frame = i;
		thread[i].total_frame = i;
		if (pthread_create(&thread[i].thread, NULL, (*launch_rays)
			, &thread[i]) < 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < NBR_THREAD)
		pthread_join(thread[i++].thread, NULL);
	return (0);
}
