/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_test_mode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 15:27:33 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/23 17:35:08 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "player.h"
#include <SDL.h>
#include "graphic_lib.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include "octree.h"

static void	add_hud(t_doom *data)
{
	int			i;

	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		if (((unsigned int*)data->lib.hud_texture->pixels)[i] != 0xffffff78 && ((unsigned int*)data->lib.hud_texture->pixels)[i] != 0xff00ffff)
			data->lib.image[i] = (((unsigned int*)data->lib.hud_texture->pixels)[i] & 0xff000000) + ((((unsigned int*)data->lib.hud_texture->pixels)[i] & 0xff) << (16)) + ((((unsigned int*)data->lib.hud_texture->pixels)[i] & 0xff00)) + ((((unsigned int*)data->lib.hud_texture->pixels)[i] & 0xff0000) >> 16);
		i++;
	}
}

static void	update_physics(t_doom *data)
{
	data->player.acceleration = data->player.physics.acceleration;
	data->player.camera.origin = data->player.physics.origin;
	data->player.camera.direction = data->player.physics.camera.direction;
	data->player.camera.up = data->player.physics.camera.up;
	data->player.camera.right = data->player.physics.camera.right;
}

int			state_test_mode(t_doom *data)
{
	unsigned long	time;
	long			wait;

	time = SDL_GetTicks();
	raytracing(data);
	wait = SDL_GetTicks();
	add_hud(data);
	data->player.health = 1000;
	put_health_bar(data);
	minimap(data->map_to_save, &data->player, &data->lib);
	display_inventory(&data->lib, &data->player);
	update_physics(data);
	if (data->photo)
	{
		data->photo = 0;
		convert_to_ppm(data->lib.image);
	}
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	SDL_RenderPresent(data->lib.renderer);
	SDL_RenderClear(data->lib.renderer);
	if ((wait = (SDL_GetTicks() - time)) < 50)
		usleep(50000 - (wait * 1000));
	return (0);
}