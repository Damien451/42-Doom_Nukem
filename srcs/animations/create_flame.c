/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flame.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 21:58:10 by roduquen          #+#    #+#             */
/*   Updated: 2019/10/20 22:22:17 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include <time.h>
#include <pthread.h>
#include "thread.h"

static inline int	average(unsigned int *image, int i)
{
	int				average;

/*	average = (image[i + WIDTH]) + (image[i + WIDTH - 1]);
		average += (image[i + (WIDTH << 1)]);
		average += (image[i + WIDTH + 1]);
	average >>= 2;*/
	average = image[i + WIDTH] + image[i + (WIDTH << 1)] + image[i + WIDTH - 1] + image[i + WIDTH + 1];
	average >>= 2;
	return (average);
}

static inline void	*create_thread(void *thread)
{
	int				i;
	int				randomizer;
	unsigned int	*image;

	i = ((t_thread*)thread)->num;
	image = ((t_thread*)thread)->image;
	while (i < WIDTH << 1)
	{
		randomizer = (rand() & 127) + 128;
//		randomizer |= (randomizer << 16) | (randomizer << 8);
		image[HEIGHT * WIDTH - (WIDTH << 1) + i] = randomizer;
	//	image[HEIGHT * WIDTH - (WIDTH << 4) + i] = rand() & 255;
		i += NBR_THREAD;
	}
	i = HEIGHT * WIDTH - (WIDTH << 1) - 1 - ((t_thread*)thread)->num;
	while (i > ((HEIGHT - 50) * WIDTH))
	{
		image[i] = average(image, i);
		i -= NBR_THREAD;
	}
	pthread_exit(0);
}

int					create_flame(t_doom *data, unsigned int *image)
{
	int				i;
	t_thread		thread[NBR_THREAD];

	(void)data;
	i = 0;
	while (i < NBR_THREAD)
	{
		thread[i].image = image;
		thread[i].num = i;
		if (pthread_create(&thread[i].thread, NULL, (*create_thread), &thread[i]) < 0)
			return (1);
			i++;
	}
	i = 0;
	while (i < NBR_THREAD)
		pthread_join(thread[i++].thread, NULL);
	return (0);
}
