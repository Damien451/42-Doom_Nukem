/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_scoreboard.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 15:25:37 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/21 19:41:04 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include "menus.h"
#include <unistd.h>

/*static int	save_scores(t_doom *data)
{
	int			fd;
	int			i;
	char		buf[26];
	char		*tmp;


	i = -1;
	if ((fd = open("./files/scores", O_WRONLY | O_TRUNC | O_CREAT, 0777)) == -1)
		return (1);
	while (++i < PLAYERS_SCOREBOARD)
	{
		ft_bzero(buf, 26);
		tmp = ft_itoa(data->scoreboard.scores[i]);
		ft_strcat(ft_strcat(buf, tmp), data->scoreboard.playertags[i]);
		write(fd, ft_strcat(buf, "\n"), ft_strlen(buf));
		free(tmp);
	}
	close(fd);
	switch_state(data, SCORES, MAIN_MENU);
	return (0);
}*/

static void	check_inputs(t_doom *data)
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
			switch_state(data, SCORES, MAIN_MENU);
	}
}

int			state_scoreboard(t_doom *data)
{
	static unsigned long	time = 0;
	static int				first = 0;
	static int				frame = 0;
	long					wait;

	if (first == 0)
		if (parse_scores_file(data, &first))
			switch_state(data, SCORES, MAIN_MENU);
	if (!time)
		time = SDL_GetTicks();
	ft_memset(data->lib.image, 0, WIDTH * HEIGHT * 4);
	ft_memcpy(data->lib.image, data->lib.menu_texture[4]->pixels
		, (WIDTH * HEIGHT) << 2);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	put_string_with_shadow(data, point(WIDTH / 2, HEIGHT / 13)
		, label("SCOREBOARD", (SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[1]);
	display_scores(data, &data->scoreboard, frame);
	check_inputs(data);
	if ((wait = (SDL_GetTicks() - time)) < 17)
		usleep(17000 - (wait * 1000));
	time = SDL_GetTicks();
	SDL_RenderPresent(data->lib.renderer);
	if (++frame == 1024)
		frame = 1;
	return (0);
}
