/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_new_highscore.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/26 19:59:28 by dacuvill          #+#    #+#             */
/*   Updated: 2020/02/27 16:23:19 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include "menus.h"
#include "inputs.h"
#include <stdio.h>

static void	shift_left_scores(t_scoreboard *scoreboard,
	t_player *player, char *nametag, int i)
{
	int			tmpscore;
	int			tmpscore2;
	static char	tmptag[LENGTH_NAMETAG];
	static char	tmptag2[LENGTH_NAMETAG];

	tmpscore = player->score;
	tmpscore2 = 0;
	ft_bzero(tmptag, LENGTH_NAMETAG);
	ft_strcpy(tmptag, nametag);
	while (i < PLAYERS_SCOREBOARD)
	{
		tmpscore2 = scoreboard->scores[i];
		ft_bzero(tmptag2, LENGTH_NAMETAG);
		ft_strcpy(tmptag2, scoreboard->playertags[i]);
		scoreboard->scores[i] = tmpscore;
		ft_strcpy(scoreboard->playertags[i], tmptag);
		tmpscore = tmpscore2;
		ft_bzero(tmptag, LENGTH_NAMETAG);
		ft_strcpy(tmptag, tmptag2);
		i++;
	}
}

void		add_new_highscore(t_scoreboard *scoreboard,
	t_player *player, char *nametag)
{
	int		i;

	i = 0;
	while (i < PLAYERS_SCOREBOARD && player->score < scoreboard->scores[i])
		++i;
	if (i == PLAYERS_SCOREBOARD - 1)
	{
		scoreboard->scores[PLAYERS_SCOREBOARD - 1] = player->score;
		ft_bzero(scoreboard->playertags[PLAYERS_SCOREBOARD - 1],
			LENGTH_NAMETAG);
		ft_strcpy(scoreboard->playertags[PLAYERS_SCOREBOARD - 1], nametag);
		return ;
	}
	else
		shift_left_scores(scoreboard, player, nametag, i);
}
