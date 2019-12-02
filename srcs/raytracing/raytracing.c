/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 10:28:52 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/02 13:20:29 by roduquen         ###   ########.fr       */
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

void					*launch_rays(void *ptr)
{
	t_doom			*data;
	int				i;
	int				pos[2];
	int				j;

	data = ((t_thread*)ptr)->data;
	pthread_mutex_lock(((t_thread*)ptr)->mutex);
	i = data->actual_i;
	data->actual_i += (8);
	pthread_mutex_unlock(((t_thread*)ptr)->mutex);
	while (i < ((t_thread*)ptr)->frame)
	{
		j = 0;
		while (j < 8)
		{
			pos[0] = data->samplingt[data->sampling - 1][i + j];
			pos[1] = data->samplingt[data->sampling - 1][i + 1 + j];
			ray_create(pos, data->player.camera, &((t_thread*)ptr)->ray);
			apply_sampling(data->lib.image
					, ray_intersect(((t_thread*)ptr)->ray, data)
					, data->sampling, pos[1] + pos[0] * WIDTH);
			j += 2;
		}
		pthread_mutex_lock(((t_thread*)ptr)->mutex);
		i = data->actual_i;
		data->actual_i += (8);
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
  if (position.x > 64.0 || position.x < 0.0 || position.y > 64.0
  || position.y < 0.0 || position.z > 64.0 || position.z < 0.0)
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

int						raytracing(t_doom *data)
{
	t_thread		thread[NBR_THREAD];
	int				i;
	static int		frame = 0;
	t_octree		*position;

	i = 0;
	data->actual_i = 2;
	position = find_actual_position(&data->player.camera.origin, data->octree);
	data->sampling = 4;
	if (data->lib.cam_keys & COURSE)
		data->sampling = 1;
	while (i < NBR_THREAD)
	{
		thread[i].data = data;
		thread[i].frame = data->samplingt[data->sampling - 1][0] * 2 - 4;
		thread[i].mutex = &data->mutex;
		thread[i].ray.node = position;
		thread[i].ray.origin = data->player.camera.origin;
		if (pthread_create(&thread[i].thread, NULL, (*launch_rays)
					, &thread[i]) < 0)
			return (1);
		i++;
	}
	SDL_RenderClear(data->lib.renderer);
	if (frame == 4)
	{
		data->power[TORCH] = 50 + (rand() & 15);
		frame = 0;
	}
	sun(data);
	frame++;
	i = 0;
	while (i < NBR_THREAD)
		pthread_join(thread[i++].thread, NULL);
	return (0);
}
