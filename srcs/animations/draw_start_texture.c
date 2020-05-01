/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_start_texture.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: damien <dacuvill@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/21 15:58:15 by damien            #+#    #+#             */
/*   Updated: 2020/04/21 16:14:25 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "libft.h"
#include <time.h>
#include "vec3.h"
#include <unistd.h>

static inline void	print_autor(t_doom *data, unsigned int *image, int color)
{
	t_bubble	*tmp;

	tmp = data->bubble_list;
	while (tmp)
	{
		image[tmp->pos] = color;
		tmp = tmp->next;
	}
}

static inline void	lightning(t_doom *data, unsigned int *image, int color
	, int frame)
{
	t_bubble	*tmp;

	tmp = data->lightning_list;
	while (tmp)
	{
		image[tmp->pos] = color;
		tmp = tmp->next;
	}
	tmp = data->lightning_list2;
	color = 0xFF;
	while (tmp)
	{
		image[tmp->pos] = color;
		tmp = tmp->next;
	}
	if (frame == 125)
		ft_memset(image, 255, (WIDTH * HEIGHT) << 2);
	else if (frame > 125 && frame <= 130)
		ft_memset(image, 255 - frame + 125, (WIDTH * HEIGHT) << 2);
	else if (frame > 120 && frame <= 125)
		ft_memset(image, 255 - frame + 125, (WIDTH * HEIGHT) << 2);
}

static inline void	randomize_new_bubble(t_start *bubble)
{
	srand(time(NULL) + rand());
	bubble->pos = rand() % WIDTH;
	bubble->speed = rand() % 10 + 1;
	bubble->size = rand() % 10 + 4;
	bubble->color = (rand() & 255) << 16;
}

void				draw_start_texture(t_doom *data, unsigned int *image)
{
	int				i;
	static int		frame = 0;
	static int		type = 1;

	i = -1;
	ft_memcpy(image, data->lib.start_bg, (WIDTH * HEIGHT) << 2);
	print_autor(data, image, ((frame >> 1) << 16));
	i = 0;
	srand(time(NULL));
	while (i < NB_BUBBLE)
	{
		start_drawing_circle(data, i, image);
		if (data->tab[i].pos >= WIDTH * HEIGHT)
			randomize_new_bubble(&data->tab[i]);
		i++;
	}
	if (type > 0 && frame >= 120 && frame <= 135)
		lightning(data, image, (((frame + 50) << 16) | ((frame + 50) << 8))
			+ frame + 75, frame);
	if (type > 0 && frame == 120)
		play_sound(data->mix.sounds[1]);
	frame += type;
	if (frame == 255 || frame == 0)
		type *= -1;
}
