/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_test_mode.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 15:27:33 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/19 22:57:21 by dacuvill         ###   ########.fr       */
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

static inline void	check_events(t_doom *data)
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN &&
			data->lib.event.key.keysym.sym == SDLK_ESCAPE)
		{
			leave_game(data, &data->player);
			switch_state(data, TEST_MODE, EDITOR);
			return ;
		}
		else if (data->lib.event.type == SDL_MOUSEMOTION)
			camera_mouse_motion(&data->player.camera
					, &data->lib.event.motion.xrel, &data->lib.event.motion.yrel
					, &data->player.sensitivity);
		else if (data->lib.event.type == SDL_MOUSEBUTTONDOWN)
			data->lib.cam_keys |= DESTROY;
		else if (data->lib.event.type == SDL_MOUSEBUTTONUP)
			data->lib.cam_keys &= ~DESTROY;
		camera_press_key(&data->lib.event, data);
	}
	ft_memcpy(data->lib.image,
		data->lib.hud_texture->pixels, (WIDTH * HEIGHT) << 2);
	put_health_bar(data);
	raytracing(data);
}

static inline void	set_player_spawn(char map[64][64][64], t_vec3d *position,
	t_doom *data)
{
	int		x;
	int		y;
	int		z;

	z = -1;
	while (++z < 64)
	{
		y = -1;
		while (++y < 64)
		{
			x = -1;
			while (++x < 64)
			{
				if (map[z][y][x] == SPAWNBLOCK)
				{
					position->x = z + 0.5;
					position->y = y + 2.5;
					position->z = x + 0.5;
				}
			}
		}
	}
	data->lib.cam_keys |= WATER;
}

int					state_test_mode(t_doom *data)
{
	int		i;

	i = -1;
	SDL_SetRelativeMouseMode(SDL_TRUE);
	if (data->player.camera.origin.x == -1
		&& data->player.camera.origin.y == -1 &&
		data->player.camera.origin.z == -1)
		set_player_spawn(data->map_to_save, &data->player.camera.origin, data);
	check_events(data);
	while (++i < WIDTH * HEIGHT)
		if (((unsigned int*)data->lib.hud_texture->pixels)[i] != 0xffffff78)
			data->lib.image[i] = (((unsigned int*)data->lib.hud_texture->pixels)
			[i] & 0xff000000) + ((((unsigned int*)data->lib.hud_texture->pixels)
			[i] & 0xff) << (16))
			+ ((((unsigned int*)data->lib.hud_texture->pixels)[i] & 0xff00))
			+ ((((unsigned int*)data->lib.hud_texture->pixels)[i] & 0xff0000)
			>> 16);
	minimap(data->map_to_save, &data->player, &data->lib);
	data->player.acceleration = data->player.physics.acceleration;
	data->player.camera.origin = data->player.physics.origin;
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	SDL_RenderPresent(data->lib.renderer);
	SDL_RenderClear(data->lib.renderer);
	return (0);
}
