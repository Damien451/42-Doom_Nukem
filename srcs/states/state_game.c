/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:44:31 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/10 21:35:51 by dacuvill         ###   ########.fr       */
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

static inline void	add_weapon_pixel(t_doom *data, t_point coords, int recoil,
	unsigned int pix)
{
	if (pix != 0xff00ffff && pix != 0xff01ffff && pix != 0xff02ffff
		&& pix != 0xff03ffff && pix != 0xff04ffff && pix != 0xff05ffff
		&& pix != 0xff06ffff && pix != 0xff07ffff && pix != 0xff08ffff
		&& pix != 0xff09ffff && pix != 0xff280e27 && pix != 0xff2e132a
		&& pix != 0xff260e24 && pix != 0xff3c1d30 && pix != 0xff291028
		&& pix != 0xff2c1229 && pix != 0xff2a1229 && pix != 0xff290f26
		&& pix != 0xff280f24
		&& (580 + coords.y + recoil) < HEIGHT)
		data->lib.image[(580 + coords.y + recoil) * WIDTH + coords.x] = pix;
}

static void			add_weapon(t_doom *data, t_player *player)
{
	int				i;
	int				j;
	int				texture;
	static int		recoil = 0;
	unsigned int	pix;

	j = -1;
	texture = anim_weapon(&player->inventory.weapon_state);
	if (texture == -1)
	{
		texture = 0;
		recoil = 300;
	}
	while (++j < 100 * 5)
	{
		i = -1;
		while (++i < 350 * 5)
		{
			pix = data->lib.gun_textures[texture][(j / 5 * 350) + i / 5];
			add_weapon_pixel(data, point(i, j), recoil, pix);
		}
	}
	if (recoil > 0)
		recoil -= 15;
}

static void	add_hud_and_weapon(t_doom *data, t_player *player)
{
	int				i;

	i = -1;
	if (data->state == PLAYING)
		add_weapon(data, player);
	while (++i < WIDTH * HEIGHT)
	{
		if (data->lib.hud_texture[i] != 7929855
			&& data->lib.hud_texture[i] != 0xff00ffff)
			data->lib.image[i] = (data->lib.hud_texture[i] & 0xff000000)
			+ ((data->lib.hud_texture[i] & 0xff) << 16)
			+ (data->lib.hud_texture[i] & 0xff00)
			+ ((data->lib.hud_texture[i] & 0xff0000) >> 16);
	}
}

int			state_game(t_doom *data)
{
	struct timeval	time;
	long			wait;
	long			sleep;

	gettimeofday(&time, NULL);
	wait = time.tv_sec * 1000000 + time.tv_usec;
	raytracing(data);
	add_hud_and_weapon(data, &data->player);
	put_health_bar(data);
	game_sounds(data, &data->player);
	minimap(data->map_to_save, &data->player, &data->lib);
//	display_inventory(data, &data->lib, &data->player, PLAYING);
//	move_ennemies(data, &data->player, &data->enemies);
	if (data->photo)
	{
		data->photo = 0;
		convert_to_ppm(data->lib.image);
	}
	if (data->player.inventory.lag > 0)
		data->player.inventory.lag--;
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	check_pos_player(data, data->map_to_save, data->player.camera.origin);
//	display_inventory_strings(data, &data->lib, &data->player, PLAYING);
	SDL_RenderPresent(data->lib.renderer);
	SDL_RenderClear(data->lib.renderer);
	if (data->player.health <= 0)
		switch_state(data, PLAYING, DEATH);
	gettimeofday(&time, NULL);
	if ((sleep = time.tv_sec * 1000000 + time.tv_usec - wait) < 50000)
		usleep(50000 - sleep);
	return (0);
}
