/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   launch_rays.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/03 12:04:19 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/05 17:31:55 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "player.h"
#include "thread.h"
#include "octree.h"
#include <pthread.h>
#include <math.h>

static inline void		ray_create(const int pos[2], const t_camera camera
		, t_ray *ray)
{
	double	x;
	double	y;

	x = (2 * (pos[1] - 51 + .5) / WIDTH - 1) * FOV;
	y = (1 - (2 * (pos[0] - 51 + .5) / HEIGHT)) * POV;
	ray->direction.x = (camera.right.x * x) + (camera.up.x * y)
		+ camera.direction.x;
	ray->direction.y = (camera.right.y * x) + (camera.up.y * y)
		+ camera.direction.y;
	ray->direction.z = (camera.right.z * x) + (camera.up.z * y)
		+ camera.direction.z;
}

static inline void		apply_sampling(unsigned int *image
		, const unsigned int color, const int sampling, const int position)
{
	int				i;
	int				j;
	int				tmp;
	int				sampl;

	i = 0;
	sampl = sampling >> 1;
	while (i < sampling)
	{
		tmp = position + i - sampl;
		j = 0;
		while (j < sampling)
		{
			image[tmp + (j - sampl) * WIDTH] = color;
			j++;
		}
		i++;
	}
}

static inline int		catch_next_pixel_to_compute(t_doom *data, void *ptr)
{
	int		i;

	pthread_mutex_lock(((t_thread*)ptr)->mutex);
	i = data->actual_i;
	data->actual_i += (32);
	pthread_mutex_unlock(((t_thread*)ptr)->mutex);
	return (i);
}

void					*launch_rays(void *ptr)
{
	t_doom			*data;
	int				i;
	int				pos[2];
	int				j;

	data = ((t_thread*)ptr)->data;
	i = catch_next_pixel_to_compute(data, ptr);
	while (i < ((t_thread*)ptr)->frame)
	{
		j = -2;
		while ((j += 2) < 32)
		{
			pos[0] = data->samplingt[data->sampling - 1][i + j];
			pos[1] = data->samplingt[data->sampling - 1][i + 1 + j];
			ray_create(pos, data->player.camera, &((t_thread*)ptr)->ray);
			apply_sampling(data->lib.image, ray_intersect(((t_thread*)ptr)->ray
				, data), data->sampling, pos[1] + pos[0] * WIDTH);
		}
		i = catch_next_pixel_to_compute(data, ptr);
	}
	pthread_exit(0);
}
