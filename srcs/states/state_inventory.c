/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_inventory.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 18:13:55 by smokhtar          #+#    #+#             */
/*   Updated: 2020/02/24 21:04:01 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static inline void	keydown_inventory_commands(t_doom *data)
{
    if (data->lib.event.key.keysym.sym == SDLK_ESCAPE)
		switch_state(data, INVENTORY, PLAYING);
}

int			state_inventory(t_doom *data)
{
	static int	ok = 1;

	if (ok == 1)
	{
        SDL_ShowCursor(SDL_TRUE);
        while (SDL_PollEvent(&data->lib.event))
		    keydown_inventory_commands(data);
		SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
		SDL_RenderPresent(data->lib.renderer);
		SDL_RenderClear(data->lib.renderer);
		data->lib.cam_keys = 0;
		ok--;
	}
	return (0);
}
