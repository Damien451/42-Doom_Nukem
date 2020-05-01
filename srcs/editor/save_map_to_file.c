/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_map_to_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 23:03:03 by dacuvill          #+#    #+#             */
/*   Updated: 2020/02/25 23:05:29 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include <inputs.h>
#include <fcntl.h>
#include <unistd.h>

void		save_map_to_file(t_doom *data, char *map_name)
{
	int			fd;
	char		full_path[50];

	fd = 0;
	ft_bzero(full_path, 50);
	if (check_map_validity(data) == 0)
	{
		if ((fd = open(ft_strcat(ft_strcat(full_path, "./maps/"), map_name),
			O_WRONLY | O_CREAT | O_TRUNC, 0777)) != -1)
		{
			write(fd, data->map_to_save, SIZE_MAP * SIZE_MAP * SIZE_MAP);
			close(fd);
		}
	}
}
