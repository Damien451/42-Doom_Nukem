/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_start.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:06:01 by roduquen          #+#    #+#             */
/*   Updated: 2020/04/21 16:06:26 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "libft.h"
#include <time.h>
#include "vec3.h"
#include <unistd.h>

static inline void	create_start_renderer(t_doom *data)
{
	static unsigned long	time = 0;
	long					wait;

	if (!time)
		time = SDL_GetTicks();
	draw_start_texture(data, data->lib.image);
	if (!data->load_page[0])
	{
		ft_memset(data->lib.image, 0, ((WIDTH * HEIGHT) << 1)
				- data->load_page[1] * WIDTH);
		ft_memset(data->lib.image + ((((WIDTH * HEIGHT) << 1)
				+ data->load_page[1] * WIDTH) >> 2), 0, ((WIDTH * HEIGHT) << 1)
				- (data->load_page[1] * (WIDTH)));
		data->load_page[1] += 32;
		if (data->load_page[1] >= HEIGHT << 1)
			data->load_page[0] = 1;
	}
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	if ((wait = (SDL_GetTicks() - time)) < 17)
		usleep(17000 - (wait * 1000));
	time = SDL_GetTicks();
	SDL_RenderPresent(data->lib.renderer);
}

int					state_start(t_doom *data)
{
	loop_sound_effect(data->mix.sounds[0], 0);
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
		{
			data->load_page[0] = 0;
			data->load_page[1] = 0;
			Mix_HaltChannel(-1);
			switch_state(data, START, MAIN_MENU);
		}
	}
	create_start_renderer(data);
	return (0);
}
