/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_trader.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 15:14:32 by smokhtar          #+#    #+#             */
/*   Updated: 2020/02/24 21:03:44 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"


static inline void	keydown_trader_commands(t_doom *data)
{
    if (data->lib.event.key.keysym.sym == SDLK_ESCAPE)
		switch_state(data, TRADER, PLAYING);
}

int			state_trader(t_doom *data)
{
	static int	ok = 1;

	if (ok == 1)
	{
        SDL_ShowCursor(SDL_TRUE);
        while (SDL_PollEvent(&data->lib.event))
		    keydown_trader_commands(data);
		SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
		SDL_RenderPresent(data->lib.renderer);
		SDL_RenderClear(data->lib.renderer);
		data->lib.cam_keys = 0;
		ok--;
	}
	return (0);
}
