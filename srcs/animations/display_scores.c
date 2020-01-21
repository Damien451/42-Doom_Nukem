/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_scores.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:19:54 by dacuvill          #+#    #+#             */
/*   Updated: 2020/01/21 20:51:15 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "menus.h"

static void	display_current_score(t_doom *data, t_scoreboard *scores,
	int curr_score, int frame)
{
	int			i;
	char		*score;

	i = -1;
	while (++i <= curr_score && i < 10)
	{
		if (i == curr_score - 1)
			score = ft_itoa(scores->scores[i] / (65 - frame));
		else
			score = ft_itoa(scores->scores[i]);
		put_string_with_shadow(data, point(WIDTH / 1.5,
			(HEIGHT / 3.4) + i * 70), label(score,
			(SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[2]);
		ft_strdel(&score);
	}
}

int			display_scores(t_doom *data, t_scoreboard *scores, int frame)
{
	static int	curr_score = 0;
	char		player_rank[25];
	char		*rank;
	int			i;
	int			spaces;

	i = -1;
	if (frame > 65)
		++curr_score;
	display_current_score(data, scores, curr_score, frame % 65);
	while (++i < PLAYERS_SCOREBOARD)
	{
		ft_bzero(player_rank, 25);
		rank = ft_itoa(i + 1);
		ft_strcat(ft_strcat(ft_strcpy(player_rank, rank), ".___"), scores->playertags[i]);
		spaces = 25 - ft_strlen(player_rank);
		while (--spaces > 0)
			ft_strcat(player_rank, "_");
		put_string_with_shadow(data, point(WIDTH / 3,
			(HEIGHT / 3.4) + i * 70), label(player_rank,
			(SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[2]);
		ft_strdel(&rank);
	}
	return (0);
}