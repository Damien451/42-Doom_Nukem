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

int				load_textures(t_doom *data)
{
	int		fd;

	fd = open("textures/all_img.bin", O_RDONLY);
	printf("ret = %d, total = %d\n", read(fd, &data->lib, TEXTURES_SIZE + CREDIT_SIZE + OBJ_SIZE), TEXTURES_SIZE + CREDIT_SIZE + OBJ_SIZE);
	close(fd);
	return (0);
}
