/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 10:28:52 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/02 08:02:00 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "player.h"
#include "thread.h"
#include "octree.h"
#include <pthread.h>
#include <math.h>

static inline void	create_ray_dir_vec(const double x, const double y, const t_doom *data, t_ray *ray)
{
	ray->direction.x = (data->player.camera.right.x * x)
		+ (data->player.camera.up.x * y) + data->player.camera.direction.x;
	ray->direction.y = (data->player.camera.right.y * x)
		+ (data->player.camera.up.y * y) + data->player.camera.direction.y;
	ray->direction.z = (data->player.camera.right.z * x)
		+ (data->player.camera.up.z * y) + data->player.camera.direction.z;
}

static inline void		ray_create(const int pos[2], const t_doom *data, t_ray *ray)
{
	create_ray_dir_vec((2 * (pos[1] - 51 + .5) / WIDTH - 1) * FOV
		, (1 - (2 * (pos[0] - 51 + .5) / HEIGHT)) * POV, data, ray);
	ray->length = 0;
}

static inline void		apply_sampling(unsigned int *image, const unsigned int color
	, const int sampling, const int position)
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
	int				pos[2];

	data = ((t_thread*)ptr)->data;
	pthread_mutex_lock(((t_thread*)ptr)->mutex);
	i = data->actual_i;
	data->actual_i += 2;
	pthread_mutex_unlock(((t_thread*)ptr)->mutex);
	while (i < data->samplingt[data->sampling - 1][0] * 2)
	{
		pos[0] = data->samplingt[data->sampling - 1][i];
		pos[1] = data->samplingt[data->sampling - 1][i + 1];
		ray_create(pos, data, &((t_thread*)ptr)->ray);
		apply_sampling(data->lib.image
				, ray_intersect(((t_thread*)ptr)->ray, data)
				, data->sampling, pos[1] + pos[0] * WIDTH);
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
	t_octree		*position;

	i = 0;
	data->actual_i = 2;
	position = find_actual_position(&data->player.camera.origin, data->octree);
	while (i < NBR_THREAD)
	{
		thread[i].data = data;
		thread[i].mutex = &data->mutex;
		thread[i].ray.node = position;
		thread[i].ray.origin = data->player.camera.origin;
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
	return (0);
}
