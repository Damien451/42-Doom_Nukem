/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_scores_file.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/16 16:39:15 by dacuvill          #+#    #+#             */
/*   Updated: 2020/04/20 01:11:00 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int			parse_scores_file(t_doom *data, int *first)
{
	int			i;
	int			fd;
	char		*line;

	i = -1;
	if ((fd = open("./files/scores", O_RDONLY)) < 1)
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

void			write_scores_file(t_doom *data)
{
	int			i;
	int			fd;
	char		*score;

	i = -1;
	if ((fd = open("./files/scores_test",
		O_CREAT | O_WRONLY | O_TRUNC, 0777)) < 1)
		return ;
	while (++i < PLAYERS_SCOREBOARD)
	{
		if ((score = ft_itoa(data->scoreboard.scores[i])) <= 0)
			return ;
		write(fd, score, ft_strlen(score));
		write(fd, " ", 1);
		write(fd, data->scoreboard.playertags[i],
			ft_strlen(data->scoreboard.playertags[i]));
		write(fd, "\n", 1);
		ft_strdel(&score);
	}
	close(fd);
}
