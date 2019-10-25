/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <roduquen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 10:28:52 by roduquen          #+#    #+#             */
/*   Updated: 2019/10/25 12:09:20 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "player.h"
#include "thread.h"
#include "octree.h"
#include <pthread.h>
#include <math.h>

t_octree	*find_actual_position(t_vec3d *position, t_octree *node)
{
	while (node->leaf != EMPTY)
	{
		if (node->leaf == INSIDE)
		{
			if (position->x < (double)(node->center.x >> 1))
			{
				if (position->y < (double)(node->center.y >> 1))
				{
					if (position->z < (double)(node->center.z >> 1))
						node = node->child[0];
					else
						node = node->child[4];
				}
				else
				{
					if (position->z < (double)(node->center.z >> 1))
						node = node->child[2];
					else
						node = node->child[6];
				}
			}
			else
			{
				if (position->y < (double)(node->center.y >> 1))
				{
					if (position->z < (double)(node->center.z >> 1))
						node = node->child[1];
					else
						node = node->child[3];
				}
				else
				{
					if (position->z < (double)(node->center.z >> 1))
						node = node->child[5];
					else
						node = node->child[7];
				}
			}
		}
	}
	return (node);
}

t_vec3d		ray_create(int y, int x, t_doom *data)
{
	double	pixel_x;
	double	pixel_y;
	t_vec3d	dir;

	pixel_x = (2 * (x + .5) / WIDTH - 1) * FOV;
	pixel_y = (1 - (2 * (y + .5) / HEIGHT)) * FOV;
	dir = vec3d_scalar(data->player.camera.right, pixel_x);
	dir = vec3d_add(dir, vec3d_scalar(data->player.camera.up, pixel_y));
	dir = vec3d_add(dir, data->player.camera.direction);
	return (vec3d_unit(dir));
}

void		*launch_rays(void *ptr)
{
	t_doom			*data;
	int				i;
	int				j;
	t_vec3d			ray;
	t_octree		*position;
	int				count[3];
	int				color;

	data = ((t_thread*)ptr)->data;
	position = find_actual_position(&data->player.camera.origin, data->octree);
	i = 51 + ((t_thread*)ptr)->num;
	while (i < WIDTH - 51)
	{
		j = 51;
		while (j < 829)
		{
			ray = ray_create(j - 51, i - 51, data);
			color = ray_intersect(ray
				, data->player.camera.origin, position, data);
			count[0] = 0;
			while (count[0] < data->sampling)
			{
				count[1] = 0;
				count[2] = i + count[0] + j * WIDTH;
				while (count[1] < data->sampling)
				{
					data->lib.image[count[2] + count[1] * WIDTH] = color;
					count[1]++;
				}
				count[0]++;
			}
			j += data->sampling;
		}
		i += NBR_THREAD * data->sampling;
	}
	pthread_exit(0);
}

int			raytracing(t_doom *data)
{
	t_thread		thread[NBR_THREAD];
	int				i;

	i = 0;
	SDL_RenderClear(data->lib.renderer);
	if (!data->lib.cam_keys && data->sampling != 1)
		data->sampling = 1;
	while (i < NBR_THREAD)
	{
		thread[i].data = data;
		thread[i].image = data->lib.image;
		thread[i].num = data->sampling * i;
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
