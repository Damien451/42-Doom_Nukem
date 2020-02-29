/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_anim_state_start.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 00:05:06 by dacuvill          #+#    #+#             */
/*   Updated: 2020/02/29 17:16:46 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include <SDL_image.h>
#include <SDL.h>
#include <fcntl.h>
#include <unistd.h>
#include <limits.h>

static int		get_texture(unsigned int **dest, int size, char *path_text)
{
	int		fd;

	fd = 0;
	if (!(*dest = malloc(size)))
		return (1);
	if (!(fd = open(path_text, O_RDONLY)))
		return (1);
	if (read(fd, *dest, size) != size)
		return (1);
	close(fd);
	return (0);
}

static void		init_bubbles(t_doom *data)
{
	int			i;

	i = 0;
	while (i < NB_BUBBLE)
	{
		data->tab[i].pos = rand() % WIDTH * HEIGHT;
		if (rand() % 2)
			rand();
		data->tab[i].speed = rand() % 10 + 1;
		if (rand() % 3)
			rand();
		data->tab[i].size = rand() % 10 + 4;
		if (rand() % 4)
			rand();
		data->tab[i++].color = (rand() % 256) << 16;
	}
}

void			init_anim_state_start(t_doom *data)
{
	int				i;
	unsigned int	*surface;
	t_bubble		*tmp;
	t_bubble		*tmp2;

	init_bubbles(data);
	get_texture(&surface, 4 * 1920 * 1080,
		"/sgoinfre/goinfre/Perso/dacuvill/textures_binary/Credits.binary");
	get_texture(&data->lib.start_bg, 4 * 1920 * 1200,
		"/sgoinfre/goinfre/Perso/dacuvill/textures_binary/start_bg.binary");
	i = -1;
	tmp = NULL;
	while (++i < WIDTH * HEIGHT)
	{
		if (surface[i] != UINT_MAX)
		{
			if (!tmp)
			{
				tmp = malloc(sizeof(t_bubble));
				tmp->pos = i;
				tmp->next = NULL;
				data->bubble_list = tmp;
			}
			else
			{
				tmp->next = malloc(sizeof(t_bubble));
				tmp->next->pos = i;
				tmp->next->next = NULL;
				tmp = tmp->next;
			}
		}
	}
	tmp = NULL;
	free(surface);
	get_texture(&surface, 4 * 1920 * 1440,
		"/sgoinfre/goinfre/Perso/dacuvill/textures_binary/eclair.binary");
	i = -1;
	tmp2 = NULL;
	while (++i < WIDTH * HEIGHT)
	{
		if (surface[i] != UINT_MAX && (surface[i] % 0x1000000 <= 0x888888))
		{
			if (!tmp)
			{
				tmp = malloc(sizeof(t_bubble));
				tmp->pos = i;
				tmp->next = NULL;
				data->lightning_list = tmp;
			}
			else
			{
				tmp->next = malloc(sizeof(t_bubble));
				tmp->next->pos = i;
				tmp->next->next = NULL;
				tmp = tmp->next;
			}
		}
		else if (surface[i] != UINT_MAX && (surface[i] % 0x1000000 <= 0x999999))
		{
			if (!tmp2)
			{
				tmp2 = malloc(sizeof(t_bubble));
				tmp2->pos = i;
				tmp2->next = NULL;
				data->lightning_list2 = tmp2;
			}
			else
			{
				tmp2->next = malloc(sizeof(t_bubble));
				tmp2->next->pos = i;
				tmp2->next->next = NULL;
				tmp2 = tmp2->next;
			}
		}
	}
	free(surface);
}
