/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 13:59:18 by roduquen          #+#    #+#             */
/*   Updated: 2020/04/17 20:05:32 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <SDL.h>

static int		check_sampling(t_doom *data, int i)
{
	int	x;
	int	y;
	int	value;

	value = (i > 0 ? i + 1 : 0);
	y = -1;
	while (++y < HEIGHT)
	{
		if (data->lib.sampling[i][(y * HEIGHT) + 1] < value / 2
			|| data->lib.sampling[i][(y * HEIGHT) + 1] > 1920 - (value / 2))
			return (1);
		x = -1;
		while (++x < WIDTH)
			if (data->lib.sampling[i][(y * HEIGHT) + x + 1] < value / 2
				|| data->lib.sampling[i][(y * HEIGHT) + x + 1] > 1080 - (value / 2))
				return (1);
	}
	return (0);
}

int			load_sampling(int fd, t_doom *data)
{
	char	sizec[4];
	int		i;

	i = 0;
	while (i < 6)
	{
		read(fd, sizec, 4);
		data->lib.sampling[i][0] = *((int*)sizec);
		read(fd, &data->lib.sampling[i][1], data->lib.sampling[i][0] * 8);
		//if (check_sampling(data, i))
		//	return (1);
		i++;
	}
	return (0);
}

void			create_sound_size(int sound[13])
{
	sound[0] = 7545742;
	sound[1] = 466326;
	sound[2] = 7089956;
	sound[3] = 76079182;
	sound[4] = 49147214;
	sound[5] = 42369238;
	sound[6] = 79254910;
	sound[7] = 31363150;
	sound[8] = 89904;
	sound[9] = 89904;
	sound[10] = 58012;
	sound[11] = 112510;
	sound[12] = 41338;
}

int				create_sound(int fd)
{
	char	*buffer;
	char	name[25];
	int		fd_new;
	int		i;
	int		sound_size[13];

	create_sound_size(sound_size);
	buffer = malloc(sound_size[6]);
	i = 0;
	while (i < 13)
	{
		sprintf(name, "ressources/sounds/%d.wav", i);
		fd_new = open(name, O_WRONLY | O_TRUNC | O_CREAT, 0777);
		read(fd, buffer, sound_size[i]);
		write(fd_new, buffer, sound_size[i]);
		close(fd_new);
		i++;
	}
	free(buffer);
	return (0);
}

int				load_textures(t_doom *data)
{
	int		fd;

	fd = open("textures/all_img.bin", O_RDONLY);
	read(fd, &data->lib, TEXTURES_SIZE + CREDIT_SIZE + OBJ_SIZE);
	if (load_sampling(fd, data))
		return (1);
	create_sound(fd);
	if (init_mixer(data))
		return (1);
	close(fd);
	return (0);
}
