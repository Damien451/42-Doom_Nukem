/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_game.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 16:44:31 by dacuvill          #+#    #+#             */
/*   Updated: 2020/02/13 17:37:07 by dacuvill         ###   ########.fr       */
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
#include "mixer.h"

void		skybox(t_doom *data)
{
	int			i;
	int			j;
//	unsigned int			format;
	unsigned char			tab[4];
	static unsigned char	tabi[3 * 256 * 256];
	static unsigned int		tabl[256 * 256];
	static int				ok = 0;
	int						fd;


	/*int						k;
	char					destpath[70] = "/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/";
	char					full_destpath[100];
	char					originpath[60] = "/sgoinfre/goinfre/Perso/dacuvill/blocks_rgb_tmp/";
	char					full_originpath[80];

	k = -1;
	while (++k < NBR_TEXTURES_BLOCKS)
	{
		ft_bzero(full_originpath, 80);
		ft_bzero(full_destpath, 100);
		ft_strcat(ft_strcat(ft_strcat(full_originpath, originpath), ft_itoa(k)), ".rgb");
		ft_strcat(ft_strcat(ft_strcat(full_destpath, destpath), ft_itoa(k)), ".binary");
		tab[0] = 0;*/
		fd = open("stone_cylinder.rgb", O_RDONLY);
		read(fd, tabi, 128*128*3);
		close(fd);
		i = 0;
		while (i < 128)
		{
			j = 0;
			while (j < 128)
			{
				tab[0] = tabi[i * 128 * 3 + 3 * j + 2];
				tab[1] = tabi[i * 128 * 3 + 3 * j + 1];
				tab[2] = tabi[i * 128 * 3 + 3 * j];
				tab[3] = 0;
				tabl[i * 128 + j] = *((unsigned int *)&tab);
				data->lib.image[i * WIDTH + j] = *((unsigned int*)&tab);
				data->lib.image[i * WIDTH + j] = tabl[i * 128 + j];
				j++;
			}
			i++;
		}
		//if (!ok)
		//{
		i = open("stone_cylinder.binary", O_TRUNC | O_WRONLY | O_CREAT, 0777);
		write(i, tabl, 128*128*4);
		close(i);
		ok++;
		//}
	//}
}

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

#include <sys/time.h>

int			state_game(t_doom *data)
{
	struct timeval	time;
	long			wait;
	long			sleep;

	gettimeofday(&time, NULL);
	wait = time.tv_sec * 1000000 + time.tv_usec;
	raytracing(data);
	add_hud(data);
	put_health_bar(data);
	game_sounds(data, &data->player);
	minimap(data->map_to_save, &data->player, &data->lib);
	display_inventory(&data->lib, &data->player);
	update_physics(data);
	if (data->map_to_save[(int)data->player.camera.origin.x]
		[(int)data->player.camera.origin.y - 2][(int)data->player.camera.origin.z] == ID_FINISH_BLOCK + 1)
		switch_state(data, PLAYING, FINISHED);
	if (data->photo)
	{
		data->photo = 0;
		convert_to_ppm(data->lib.image);
	}
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	SDL_RenderPresent(data->lib.renderer);
	SDL_RenderClear(data->lib.renderer);
	if (data->player.health <= 0)
		switch_state(data, PLAYING, DEATH);
	gettimeofday(&time, NULL);
	if ((sleep = time.tv_sec * 1000000 + time.tv_usec - wait) < 50000)
		usleep(50000 - sleep);
	return (0);
}
