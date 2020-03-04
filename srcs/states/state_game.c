/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:44:31 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/04 16:36:01 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "player.h"
#include "graphic_lib.h"
#include "libft.h"
#include "octree.h"
#include "mixer.h"
#include "gameplay.h"
#include <SDL.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/time.h>

static void	add_hud(t_doom *data)
{
	int			i;

	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		if (data->lib.hud_texture[i] != 7929855
			&& data->lib.hud_texture[i] != 0xff00ffff)
			data->lib.image[i] = (data->lib.hud_texture[i] & 0xff000000)
			+ ((data->lib.hud_texture[i] & 0xff) << (16))
			+ (data->lib.hud_texture[i] & 0xff00)
			+ ((data->lib.hud_texture[i] & 0xff0000) >> 16);
		i++;
	}
}

int			state_game(t_doom *data)
{
	struct timeval	time;
	long			wait;
	long			sleep;

	/*static int			first = 0;
	static t_hitbox		hitbox;

	if (first == 0)
	{
		hitbox.min.x = 23;
		hitbox.min.y = 61;
		hitbox.min.z = 23;
		hitbox.max.x = 24;
		hitbox.max.y = 62;
		hitbox.max.z = 24;
		first = 1;
	}
	while (move_hitbox((t_vec3d){-1, -3, -1}, hitbox, data->map_to_save) == 1)
	{
		hitbox.min.x--;
		hitbox.min.y -= 3;
		hitbox.min.z--;
		hitbox.max.x--;
		hitbox.max.y -= 3;
		hitbox.max.z--;
		printf("distance = %f\n", sqrt(((data->player.camera.origin.x - hitbox.min.x)
		* (data->player.camera.origin.x - hitbox.min.x))
		+ ((data->player.camera.origin.y - hitbox.min.y)
		* (data->player.camera.origin.y - hitbox.min.y))
		+ ((data->player.camera.origin.z - hitbox.min.z)
		* (data->player.camera.origin.z - hitbox.min.z))));
		printf("hitbox.min.x == %f, hits.min.y == %f, hitbox.min.z == %f\n", hitbox.min.x, hitbox.min.y, hitbox.min.z);
		printf("hitbox.max.x == %f, hitbox.max.y == %f, hitbox.max.z == %f\n", hitbox.max.x, hitbox.max.y, hitbox.max.z);
	}*/
	gettimeofday(&time, NULL);
	wait = time.tv_sec * 1000000 + time.tv_usec;
	raytracing(data);
	add_hud(data);
	put_health_bar(data);
	game_sounds(data, &data->player);
	minimap(data->map_to_save, &data->player, &data->lib);
	display_inventory(&data->lib, &data->player, PLAYING);
	move_ennemies(data, &data->player, &data->enemies);
	if (data->photo)
	{
		data->photo = 0;
		convert_to_ppm(data->lib.image);
	}
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	check_pos_player(data, data->map_to_save, data->player.camera.origin);
	SDL_RenderPresent(data->lib.renderer);
	SDL_RenderClear(data->lib.renderer);
	if (data->player.health <= 0)
		switch_state(data, PLAYING, DEATH);
	gettimeofday(&time, NULL);
	if ((sleep = time.tv_sec * 1000000 + time.tv_usec - wait) < 50000)
		usleep(50000 - sleep);
	return (0);
}
