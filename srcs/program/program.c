/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 13:46:14 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/15 14:27:37 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"

static int	game_state(t_doom *data)
{
	data->state_f[data->state](data);
	return (0);
}

int			program(t_doom *data)
{
	int				pitch;

	while (data->running)
	{
		if (!SDL_LockTexture(data->lib.texture, NULL, (void**)&data->lib.image
				, &pitch))
		{
			game_state(data);
			frame_calculator();
			SDL_UnlockTexture(data->lib.texture);
			SDL_RenderClear(data->lib.renderer);
		}
	}
	return (0);
}
