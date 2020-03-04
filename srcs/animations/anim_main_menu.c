/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   anim_main_menu.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 13:39:10 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/03 15:29:52 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "thread.h"
#include <pthread.h>

static int	create_charac_anim(const unsigned int character[500 * 350], unsigned int *image, int move)
{
	int			i;
	int			j;

	i = 0;
	while (i < 200)
	{
		j = 0;
		while (j < 200)
		{
			if (character[(i >> 2) * 500 + move + (j >> 2)])
				image[i * WIDTH + j + 525 * WIDTH + (WIDTH >> 4)] =
					character[(i >> 2) * 500 + move + (j >> 2)];
			j++;
		}
		i++;
	}
	return (0);
}

static void	choose_animation_part2(const unsigned int character[500 * 350],
	unsigned int *image, int frame)
{
	int			ret;

	if (frame >= 960)
	{
		if ((ret = (frame >> 4) & 3) == 0)
			create_charac_anim(character, image, 350 + 125000);
		else if (ret == 1 || ret == 3)
			create_charac_anim(character, image, 400 + 125000);
		else
			create_charac_anim(character, image, 450 + 125000);
	}
	else if ((ret = (frame >> 4) & 3) == 0)
		create_charac_anim(character, image, 150);
	else if (ret == 1 || ret == 3)
		create_charac_anim(character, image, 200);
	else
		create_charac_anim(character, image, 250);
}

static void	choose_animation_part1(const unsigned int character[500 * 350],
	unsigned int *image, int frame)
{
	int			ret;

	if (frame >= 160 && frame <= 256)
	{
		if ((ret = (frame >> 4) & 3) == 0)
			create_charac_anim(character, image, 150 + 25000);
		else if (ret == 1 || ret == 3)
			create_charac_anim(character, image, 200 + 25000);
		else
			create_charac_anim(character, image, 250 + 25000);
	}
	else if (frame >= 448 && frame <= 512)
	{
		if ((ret = (frame >> 4) & 3) == 0)
			create_charac_anim(character, image, 100 + 100000);
		else if (ret == 1)
			create_charac_anim(character, image, 150 + 100000);
		else if (ret == 2)
			create_charac_anim(character, image, 200 + 100000);
		else
			create_charac_anim(character, image, 250 + 100000);
	}
	else
		choose_animation_part2(character, image, frame);
}

void		*thread_main_anim(void *thread)
{
	t_doom		*data;
	int			total_frame;
	int			i;
	int			j;

	data = ((t_thread*)thread)->data;
	total_frame = ((t_thread*)thread)->total_frame + 1;
	i = ((t_thread*)thread)->num - NBR_THREAD;
	while ((i += NBR_THREAD) < WIDTH)
	{
		j = -1;
		while (++j < (1 << 7))
		{
			data->lib.image[i + j * WIDTH + (1 << 9) * WIDTH] =
			data->lib.bg_anim_menu[((i + total_frame) >> 8) & 1]
			[(i + total_frame) % 192 + j * 192];
			if (j < (1 << 6))
			{
				data->lib.image[i + j * (WIDTH - 2) + 640 * WIDTH] =
				data->lib.bg_anim_menu[((i + total_frame) >> 8) & 1]
				[((i + total_frame) >> 1) % 192 + j * 192 * 2] + 18;
			}
		}
	}
	pthread_exit(0);
}

int			anim_main_menu(t_doom *data, int total_frame, int frame)
{
	int				i;
	t_thread		thread[NBR_THREAD];

	i = 0;
	while (i < NBR_THREAD)
	{
		thread[i].data = data;
		thread[i].image = data->lib.image;
		thread[i].num = i;
		thread[i].total_frame = total_frame;
		thread[i].frame = frame;
		if (pthread_create(&thread[i].thread, NULL, (*thread_main_anim)
			, &thread[i]) < 0)
			return (1);
		i++;
	}
	i = 0;
	while (i < NBR_THREAD)
		pthread_join(thread[i++].thread, NULL);
	choose_animation_part1(data->lib.character, data->lib.image, frame);
	return (0);
}
