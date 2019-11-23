/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raytracing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/21 10:28:52 by roduquen          #+#    #+#             */
/*   Updated: 2019/11/23 16:26:07 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "player.h"
#include "thread.h"
#include "octree.h"
#include <pthread.h>
#include <math.h>

static inline t_ray		ray_create(int y, int x, t_doom *data)
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

static inline int	on_x_higher_than_middle(t_vec3d *position
	, t_vec3l *center, double size)
{
	if (position->y < (double)(center->y >> 1))
	{
		center->y -= (size);
		if (position->z < (double)(center->z >> 1))
		{
			center->z -= (size);
			return (6);
		}
		else
		{
			center->z += size;
			return (2);
		}
	}
	else
	{
		center->y += (size);
		if (position->z < (double)(center->z >> 1))
		{
			center->z -= (size);
			return (4);
		}
		else
		{
			center->z += size;
			return (0);
		}
	}
}

static inline int	on_x_lower_than_middle(t_vec3d *position
		, t_vec3l *center, double size)
{
	if (position->y < (double)(center->y >> 1))
	{
		center->y -= (size);
		if (position->z < (double)(center->z >> 1))
		{
			center->z -= (size);
			return (7);
		}
		else
		{
			center->z += size;
			return (3);
		}
	}
	else
	{
		center->y += (size);
		if (position->z < (double)(center->z >> 1))
		{
			center->z -= (size);
			return (5);
		}
		else
		{
			center->z += size;
			return (1);
		}
	}
}

int				find_ac_position(t_vec3d *position, unsigned int *octree_v2, int *value)
{
	t_vec3l		center;
	double		size;
	int			new;
	int			i;
	int			j;
	int			count;
	unsigned int	tmp;
	unsigned int	tmp2;

	center = vec3l(64, 64, 64);
	i = 0;
	size = 32;
	while (1)
	{
		if (position->x < (double)(center.x >> 1))
		{
			center.x -= size;
			j = on_x_lower_than_middle(position, &center, size);
		}
		else
		{
			center.x += size;
			j = on_x_higher_than_middle(position, &center, size);
		}
		tmp = octree_v2[i] ^ 0xFFFF0000;
		tmp >>= 16;
		tmp2 = INSIDE << (j << 1);
		printf("octree = %#6x | inside = %#6x | octree clean = %#6x\n", octree_v2[i], tmp2, tmp);
		if (!(tmp ^ tmp2))
		{
			new = 0;
			count = 1;
			j = 7 - j;
			while (new <= j)
			{
				tmp2 = INSIDE << (new << 1);
				if (!(tmp ^ tmp2))
					count++;
				new++;
			}
			i = octree_v2[i];
			while (count)
			{
				if ((octree_v2[i] & 0xFFFF0000) == 0xFFFF0000)
				{
					i++;
					count--;
				}
				else
					i++;
			}
		}
		else
		{
			*value = 7 - j;
			printf("INT center = (%ld|%ld|%ld), size = %.2f\n", center.x, center.y, center.z, size);
			return (i);
		}
		size /= 2;
	}
	return (0);
}

void					*launch_rays(void *ptr)
{
	t_doom			*data;
	int				i;
	int				j;
	t_octree		*position;

	data = ((t_thread*)ptr)->data;
	position = find_actual_position(&data->player.camera.origin, data->octree);
//	printf("OCTREE center = (%ld|%ld|%ld), size = %d\n", position->center.x, position->center.y, position->center.z, position->size);
//	find_ac_position(&data->player.camera.origin, data->octree_v2, &i);
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
		data->sun.z += 0.01;
		data->sun.x += 0.01;
		if (data->sun.z > 64.0)
		{
			data->sun.z = -64.0;
			data->sun.x = -64.0;
			frame = -3200;
		}
	}
//	data->sun = data->player.camera.origin;
	frame++;
}

int						raytracing(t_doom *data)
{
	t_thread		thread[NBR_THREAD];
	int				i;
	static int		frame = 0;

	i = 0;
//	if (frame == 4)
//	{
		data->torch = 50 + (rand() & 15);
//		frame = 0;
//	}
	frame++;
//	if (data->ball)
//		light_gun(data);
//	else
		sun(data);
	SDL_RenderClear(data->lib.renderer);
	data->sampling = 6;
	if (data->lib.cam_keys & COURSE)
		data->sampling = 1;
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
