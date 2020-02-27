/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_scores_file.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 12:27:15 by dacuvill          #+#    #+#             */
/*   Updated: 2020/02/26 15:55:54 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

int			parse_scores_file(t_doom *data, int *first)
{
	int			i;
	int			fd;
	char		*line;

	i = -1;
	if ((fd = open("./files/scores", O_RDONLY, 0777)) == -1)
		return (1);
	while (++i < PLAYERS_SCOREBOARD)
	{
		ft_bzero(data->scoreboard.playertags[i], 15);
		if (get_next_line(fd, &line) <= 0)
			return (1);
		data->scoreboard.scores[i] = ft_atoi(line);
		ft_strcpy(data->scoreboard.playertags[i], ft_strchr(line, ' ') + 1);
		ft_strdel(&line);
	}
	close(fd);
	*first = 1;
	return (0);
}
