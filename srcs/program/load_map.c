/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 20:09:57 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/03 15:42:47 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>

int		load_map(t_doom *data, char *map_name)
{
	int		fd;
	int		ret;
	char	strtomap[SIZE_MAP * SIZE_MAP * SIZE_MAP];
	char	full_path[50];

	ft_bzero(full_path, 50);
	ft_strcat(ft_strcat(full_path, "./maps/"), map_name);
	if ((fd = open(full_path, O_RDONLY)) != -1)
	{
		ret = read(fd, strtomap, SIZE_MAP * SIZE_MAP * SIZE_MAP);
		close(fd);
		if (ret != SIZE_MAP * SIZE_MAP * SIZE_MAP)
			return (1);
		ft_memcpy(data->map_to_save, strtomap, SIZE_MAP * SIZE_MAP * SIZE_MAP);
	}
	else
	{
		ft_memset(data->lib.image, 0, HEIGHT * WIDTH * 4);
		ft_memset(data->map_to_save, 0, SIZE_MAP * SIZE_MAP * SIZE_MAP);
	}
	return (0);
}
