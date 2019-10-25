/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <roduquen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 10:28:52 by roduquen          #+#    #+#             */
/*   Updated: 2019/10/22 11:54:41 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "player.h"
#include "thread.h"
#include "octree.h"
#include <pthread.h>

t_octree	*find_actual_position(t_vec3d *position, t_octree *node)
{
	while (node)
	{
		if (node->leaf == EMPTY)
			return (node);
		else if (node->leaf == INSIDE)
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
	return (NULL);
}


void		*launch_rays(void *ptr)
{
	t_doom		*data;
	int			i;
	int			j;

	data = ((t_thread*)ptr)->data;
	i = 51 + ((t_thread*)ptr)->num;
	while (i < WIDTH - 51)
	{
		j = 51;
		while (j < 829)
		{
			data->lib.image[i + j * WIDTH] = j * i;
			j++;
		}
		i += NBR_THREAD;
	}
	pthread_exit(0);
}

int			raytracing(t_doom *data)
{
	t_thread		thread[NBR_THREAD];
	int				i;
	t_octree		*node;

	i = 0;
	while (i < NBR_THREAD)
	{
		thread[i].data = data;
		thread[i].image = data->lib.image;
		thread[i].num = i;
		thread[i].frame = i;
		thread[i].total_frame = i;
		if (pthread_create(&thread[i].thread, NULL, (*launch_rays), &thread[i]) < 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < NBR_THREAD)
		pthread_join(thread[i++].thread, NULL);
	if ((node = find_actual_position(&data->player.camera.origin, data->octree)))
	printf("player pos = (%.2f|%.2f|%.2f)    octree center = (%ld|%ld|%ld)\n", data->player.camera.origin.x, data->player.camera.origin.y, data->player.camera.origin.z, node->center.x >> 1, node->center.y >> 1, node->center.z >> 1);
	return (0);
}
