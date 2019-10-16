/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:06:01 by roduquen          #+#    #+#             */
/*   Updated: 2019/10/16 17:10:05 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "libft.h"
#include <time.h>
#include "vec3.h"

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
/*
static inline int	color_percent(int color1, int color2, int percent)
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

static inline void	lightning_flash(unsigned int *image, int percent)
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
*/
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
		ft_memset(image, 255, WIDTH * HEIGHT * 4);
	else if (frame > 125 && frame <= 130)
		ft_memset(image, 255 - frame + 125, WIDTH * HEIGHT * 4);
	else if (frame > 120 && frame <= 125)
		ft_memset(image, 255 - frame + 125, WIDTH * HEIGHT * 4);
}

static inline void	randomize_new_bubble(t_start *bubble)
{
	srand(time(NULL) + rand());
	bubble->pos = rand() % WIDTH;
	bubble->speed = rand() % 10 + 1;
	bubble->size = rand() % 10 + 4;
	bubble->color = (rand() % 256) << 16;
}

static inline void	draw_on_texture(t_doom *data, unsigned int *image)
{
	int			i;
	int			g;
	static int	frame = 0;
	static int	type = 1;

	i = -1;
	while (++i < WIDTH * HEIGHT)
		image[i] = ((unsigned int*)data->lib.start_bg->pixels)[i];
	print_autor(data, image, frame << 16);
	i = 0;
	g = WIDTH * (HEIGHT - 1) - 1;
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
	frame += type;
	if (frame == 255 || frame == 0)
		type *= -1;
}

static inline void	create_start_renderer(t_doom *data)
{
	int			test;

	if (!SDL_LockTexture(data->lib.texture, NULL, (void**)&data->lib.image
		, &test))
	{
		SDL_UnlockTexture(data->lib.texture);
		draw_on_texture(data, data->lib.image);
		SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
		SDL_RenderPresent(data->lib.renderer);
	}
}

int					state_start(t_doom *data)
{
	while (SDL_PollEvent(&data->lib.event))
		if (data->lib.event.type == SDL_KEYDOWN)
			switch_state(data, START, MAIN_MENU);
	create_start_renderer(data);
	return (0);
}
