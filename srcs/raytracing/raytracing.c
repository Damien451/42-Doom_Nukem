/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 10:28:52 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/01 22:31:10 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "player.h"
#include "thread.h"
#include "octree.h"
#include <pthread.h>
#include <math.h>

static inline t_ray		ray_create(int y, int x, t_doom *data, t_octree *position)
{
	double	pixel_x;
	double	pixel_y;
	t_vec3d	dir;
	t_ray	ray;

	pixel_x = (2 * (x + .5) / WIDTH - 1) * FOV;
	pixel_y = (1 - (2 * (y + .5) / HEIGHT)) * POV;
	dir = vec3d_scalar(data->player.camera.right, pixel_x);
	dir = vec3d_add(dir, vec3d_scalar(data->player.camera.up, pixel_y));
	dir = vec3d_add(dir, data->player.camera.direction);
	ray.direction = dir;
	ray.origin = data->player.camera.origin;
	ray.node = position;
	return (ray);
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
		tmp = position + i - (sampling >> 1);
		j = 0;
		while (j < sampling)
		{
			image[tmp + (j - (sampling >> 1)) * WIDTH] = color;
			j++;
		}
		i++;
	}
}

void					*launch_rays(void *ptr)
{
	t_doom			*data;
	int				i;
	t_octree		*position;

	data = ((t_thread*)ptr)->data;
	position = find_actual_position(&data->player.camera.origin, data->octree);
	pthread_mutex_lock(((t_thread*)ptr)->mutex);
	i = data->actual_i;
	data->actual_i += 2;
	pthread_mutex_unlock(((t_thread*)ptr)->mutex);
	while (i < data->samplingt[data->sampling - 1][0] * 2)
	{
		apply_sampling(data->lib.image
				, ray_intersect(ray_create(data->samplingt[data->sampling - 1][i] - 51, data->samplingt[data->sampling - 1][i + 1] - 51, data, position)
					, data)
				, data->sampling, data->samplingt[data->sampling - 1][i + 1] + data->samplingt[data->sampling - 1][i] * WIDTH);
		pthread_mutex_lock(((t_thread*)ptr)->mutex);
		i = data->actual_i;
		data->actual_i += 2;
		pthread_mutex_unlock(((t_thread*)ptr)->mutex);
	}
	pthread_exit(0);
}

/*void					light_gun(t_doom *data)
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
  if (position.x > 64.0 || position.x < 0.0 || position.y > 64.0 || position.y < 0.0 || position.z > 64.0 || position.z < 0.0)
  {
  position.x = -1;
  data->ball = 0;
  }
  }
  }*/

void					sun(t_doom *data)
{
	static int			frame = 0;

	if (frame == 0)
	{
		data->sun.x = 0;
		data->sun.y = 63 + EPSILON;
		data->sun.z = 0;
	}
	else
	{
		data->sun.z += 0.05;
		data->sun.x += 0.05;
		if (data->sun.z > 64.0)
		{
			data->sun.z = 0.0;
			data->sun.x = 0.0;
			frame = 0;
		}
	}
	frame++;
}

int						raytracing(t_doom *data)
{
	t_thread		thread[NBR_THREAD];
	int				i;
	static int		frame = 0;
	pthread_mutex_t	mutex;

	i = 0;
	pthread_mutex_init(&mutex, NULL);
	data->actual_i = 2;
	while (i < NBR_THREAD)
	{
		thread[i].data = data;
		thread[i].mutex = &mutex;
		if (pthread_create(&thread[i].thread, NULL, (*launch_rays)
					, &thread[i]) < 0)
			return (1);
		i++;
	}
	SDL_RenderClear(data->lib.renderer);
	data->sampling = 4;
	if (data->lib.cam_keys & COURSE)
		data->sampling = 1;
	if (frame == 4)
	{
		data->torch = 50 + (rand() & 15);
		frame = 0;
	}
	sun(data);
	frame++;
	i = 0;
	while (i < NBR_THREAD)
		pthread_join(thread[i++].thread, NULL);
	pthread_mutex_destroy(&mutex);
	return (0);
}
