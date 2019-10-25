/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:06:01 by roduquen          #+#    #+#             */
/*   Updated: 2019/10/22 11:09:27 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "libft.h"
#include <time.h>
#include "vec3.h"

int					color_percent(int color1, int color2, int percent)
{
	double		c1;

	if (color1 < color2)
	{
		c1 = 1.0 - (color1 / (double)color2);
		c1 = color1 + ((c1 * percent / 100.0) * 255.0);
	}
	else
	{
		c1 = color1 / (double)color2;
		c1 = color1 - ((c1 * percent / 100.0) * 255.0);
	}
	return ((int)c1);
}

void				lightning_flash(unsigned int *image, int percent)
{
	unsigned int	ok[4];
	int				i;

	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		ok[0] = (image[i] >> 24) & 255;
		ok[1] = (image[i] >> 16) & 255;
		ok[2] = (image[i] >> 8) & 255;
		ok[3] = image[i] & 255;
		ok[0] = color_percent(ok[0], 255, percent);
		ok[1] = color_percent(ok[1], 255, percent);
		ok[2] = color_percent(ok[2], 255, percent);
		ok[3] = color_percent(ok[3], 255, percent);
		image[i++] = (ok[1] << 16) | (ok[2] << 8) | ok[3];
	}
}

static inline void	print_autor(t_doom *data, unsigned int *image, int color)
{
	t_bubble			*tmp;

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
	t_bubble *tmp;

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

static inline void	draw_on_texture(t_doom *data, unsigned int *image)
{
	int			i;
	static int	frame = 0;
	static int	type = 1;

	i = -1;
	ft_memcpy(image, data->lib.start_bg->pixels, (WIDTH * HEIGHT) << 2);
	print_autor(data, image, frame << 16);
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
	{
		lightning(data, image, (((frame + 50) << 16) | ((frame + 50) << 8))
			+ frame + 75, frame);
		play_sound(data->mix->sounds[3]);
	}
	frame += type;
	if (frame == 255 || frame == 0)
		type *= -1;
}

static inline void	create_start_renderer(t_doom *data)
{
	draw_on_texture(data, data->lib.image);
	if (!data->load_page[0])
	{
		ft_memset(data->lib.image, 0, ((WIDTH * HEIGHT) << 1)
				- data->load_page[1] * WIDTH);
		ft_memset(data->lib.image + ((((WIDTH * HEIGHT) << 1)
				+ data->load_page[1] * WIDTH) >> 2), 0, ((WIDTH * HEIGHT) << 1)
				- (data->load_page[1] * (WIDTH)));
		data->load_page[1] += 32;
		if (data->load_page[1] >= HEIGHT << 1)
			data->load_page[0] = 1;
	}
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	SDL_RenderPresent(data->lib.renderer);
}

int					state_start(t_doom *data)
{
	static int flag = 0;

	if (flag == 0)
	{
		loop_sound(data->mix->sounds[2]);
		flag = 1;
	}
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
		{
			data->load_page[0] = 0;
			data->load_page[1] = 0;
			switch_state(data, START, MAIN_MENU);
		}
	}
	create_start_renderer(data);
	return (0);
}
