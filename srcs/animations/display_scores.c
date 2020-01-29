/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_scores.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/21 17:19:54 by dacuvill          #+#    #+#             */
/*   Updated: 2020/01/27 18:54:03 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "menus.h"

static void	put_string_at_exact_pos(t_doom *data, t_point pos, t_label label
	, TTF_Font *font)
{
	SDL_Texture	*text;
	SDL_Rect	src;
	SDL_Rect	dest;

	data->lib.surface = TTF_RenderText_Blended(font, label.str, label.color);
	text = SDL_CreateTextureFromSurface(data->lib.renderer, data->lib.surface);
	SDL_FreeSurface(data->lib.surface);
	SDL_QueryTexture(text, &data->lib.text.format, &data->lib.text.access,
		&src.w, &src.h);
	src.x = 0;
	src.y = 0;
	dest = src;
	dest.x = pos.x;
	dest.y = pos.y - src.h / 2;
	SDL_RenderCopy(data->lib.renderer, text, &src, &dest);
	SDL_DestroyTexture(text);
}

static void	display_current_score(t_doom *data, t_scoreboard *scores,
	int *curr_score, int frame)
{
	int			i;
	char		*score;

	i = -1;
	while (++i <= *curr_score && i < 10)
	{
		if (i == *curr_score)
			score = ft_itoa(scores->scores[i] / (65 - frame));
		else
			score = ft_itoa(scores->scores[i]);
		put_string_with_shadow(data, point(WIDTH / 1.5,
			(HEIGHT / 3.4) + i * 70), label(score,
			(SDL_Color){255 - 13 * i, 13 * i, 13 * i, 0}), data->lib.ptrfont[3]);
		ft_strdel(&score);
	}
}

static void	put_correct_string(t_doom *data, char player_rank[25], int i)
{
	int			spaces;

	spaces = 25 - ft_strlen(player_rank);
	while (--spaces > 0)
		ft_strcat(player_rank, "_");
	put_string_at_exact_pos(data, point((WIDTH / 4.5) + 15,
		(HEIGHT / 3.4) + i * 70), label(player_rank,
		(SDL_Color){0, 0, 0, 0}), data->lib.ptrfont[3]);
	put_string_at_exact_pos(data, point(WIDTH / 4.5,
		(HEIGHT / 3.4) + i * 70), label(player_rank,
		(SDL_Color){255 - 13 * i, 13 * i, 13 * i, 0}), data->lib.ptrfont[3]);
}

int			display_scores(t_doom *data, t_scoreboard *scores, int frame,
	int *curr_score)
{
	char		player_rank[25];
	char		*rank;
	int			i;

	i = -1;
	if (frame == 64 && *curr_score < 10)
		*curr_score += 1;
	display_current_score(data, scores, curr_score, frame);
	while (++i < PLAYERS_SCOREBOARD)
	{
		ft_bzero(player_rank, 25);
		rank = ft_itoa(i + 1);
		ft_strcpy(player_rank, rank);
		(i + 1 == 10 ? ft_strcat(player_rank, ".__")
			: ft_strcat(player_rank, ".___"));
		ft_strcat(player_rank, scores->playertags[i]);
		put_correct_string(data, player_rank, i);
		ft_strdel(&rank);
	}
	return (0);
}