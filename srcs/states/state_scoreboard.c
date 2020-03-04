/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_scoreboard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 15:25:37 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/02 12:32:49 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include "menus.h"
#include <unistd.h>

static void	check_inputs(t_doom *data, int *curr_score)
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN &&
			*curr_score < 10)
			*curr_score = 10;
		else if (data->lib.event.type == SDL_KEYDOWN)
		{
			*curr_score = 0;
			switch_state(data, SCORES, MAIN_MENU);
		}
	}
}

int			state_scoreboard(t_doom *data)
{
	static unsigned long	time = 0;
	static int				first = 0;
	static int				frame = 0;
	static int				curr_score = 0;
	long					wait;

	if (parse_scores_file(data, &first) != 0 || first == 0)
		switch_state(data, SCORES, MAIN_MENU);
	if (!time)
		time = SDL_GetTicks();
	ft_memset(data->lib.image, 0, WIDTH * HEIGHT * 4);
	ft_memcpy(data->lib.image, data->lib.bg_menu[1],
		(WIDTH * HEIGHT) << 2);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	put_string_with_shadow(data, point(WIDTH / 2, HEIGHT / 6),
		label("SCOREBOARD", (SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[1]);
	display_scores(data, &data->scoreboard, frame, &curr_score);
	check_inputs(data, &curr_score);
	if ((wait = (SDL_GetTicks() - time)) < 17)
		usleep(17000 - (wait * 1000));
	time = SDL_GetTicks();
	SDL_RenderPresent(data->lib.renderer);
	frame = (++frame == 65 ? 1 : frame);
	return (0);
}
