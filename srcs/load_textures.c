/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 13:59:18 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/11 20:36:12 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <SDL.h>

int			load_sampling(int fd, t_doom *data)
{
	char	sizec[4];
	int	i;

	i = 0;
	while (i < 6)
	{
		read(fd, sizec, 4);
		data->lib.sampling[i][0] = *((int*)sizec);
		read(fd, &data->lib.sampling[i][1], data->lib.sampling[i][0] * 8);
		i++;
	}
	return (0);
}

int				load_textures(t_doom *data)
{
	int		fd;

	fd = open("textures/all_img.bin", O_RDONLY);
	printf("ret = %d, total = %d\n", read(fd, &data->lib, TEXTURES_SIZE + CREDIT_SIZE + OBJ_SIZE), TEXTURES_SIZE + CREDIT_SIZE + OBJ_SIZE);
	load_sampling(fd, data);
	close(fd);
	return (0);
}
