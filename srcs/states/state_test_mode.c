/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_test_mode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 15:27:33 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/25 23:52:55 by dacuvill         ###   ########.fr       */
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
#include <sys/time.h>

static void	add_hud(t_doom *data)
{
	int			i;

	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		if (((unsigned int*)data->lib.hud_texture->pixels)[i] != 0xffffff78
			&& ((unsigned int*)data->lib.hud_texture->pixels)[i] != 0xff00ffff)
			data->lib.image[i] =
				(((unsigned int*)data->lib.hud_texture->pixels)[i]
				& 0xff000000) +
				((((unsigned int*)data->lib.hud_texture->pixels)[i] & 0xff)
				<< (16)) + ((((unsigned int*)data->lib.hud_texture->pixels)[i]
				& 0xff00))
				+ ((((unsigned int*)data->lib.hud_texture->pixels)[i]
				& 0xff0000) >> 16);
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
	struct timeval	time;
	long			wait;
	long			sleep;

	gettimeofday(&time, NULL);
	wait = time.tv_sec * 1000000 + time.tv_usec;
	raytracing(data);
	add_hud(data);
	game_sounds(data, &data->player);
	minimap(data->map_to_save, &data->player, &data->lib);
	display_inventory(&data->lib, &data->player, TEST_MODE);
	update_physics(data);
	if (data->photo)
	{
		data->photo = 0;
		convert_to_ppm(data->lib.image);
	}
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	SDL_RenderPresent(data->lib.renderer);
	SDL_RenderClear(data->lib.renderer);
	gettimeofday(&time, NULL);
	if ((sleep = time.tv_sec * 1000000 + time.tv_usec - wait) < 50000)
		usleep(50000 - sleep);
	return (0);
}
