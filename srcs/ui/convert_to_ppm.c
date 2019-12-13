/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_to_ppm.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/29 10:59:14 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/13 13:49:10 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include "libft.h"
#include "doom.h"

static int	create_name_screen(char name[30])
{
	time_t	actual_time;

	time(&actual_time);
	if (!(ctime_r(&actual_time, name)))
		return (1);
	name[24] = 0;
	ft_strcat(name, ".ppm");
	return (0);
}

static void	fill_ppm_file(unsigned int *view, int fd)
{
	int				i;
	int				j;
	unsigned char	color[3];

	i = 0;
	while (i < HEIGHT)
	{
		j = 0;
		while (j < WIDTH)
		{
			color[0] = (view[i * WIDTH + j] >> 16) & 255;
			color[1] = (view[i * WIDTH + j] >> 8) & 255;
			color[2] = (view[i * WIDTH + j]) & 255;
			dprintf(fd, "%3d %3d %3d  ", color[0], color[1], color[2]);
			j++;
		}
		dprintf(fd, "\n");
		i++;
	}
}

int			convert_to_ppm(unsigned int *view)
{
	int		fd;
	char	name[30];

	ft_memset(&name, 0, sizeof(name));
	if (create_name_screen(name))
		return (1);
	fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (fd < 0)
		return (1);
	dprintf(fd, "P3\n%d %d\n255\n", WIDTH, HEIGHT);
	fill_ppm_file(view, fd);
	close(fd);
	return (0);
}
