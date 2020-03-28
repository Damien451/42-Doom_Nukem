/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 13:59:18 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/11 20:36:12 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include <SDL.h>

static int		load_sprites(t_doom *data)
{
	int		fd;
	unsigned long	total_size;

	total_size = 128 * 128 * 4 + 15 * 32 * 4 + 512 * 512 * 4 * 6 + NBR_TEXTURES_EDITOR * 128 * 128 * 4 + NBR_TEXTURES_GUN * 350 * 100 * 4 + NBR_TEXTURES_ENEMY * 64 * 64 * 4;
	fd = open("textures/all_img.bin", O_RDONLY);
	printf("total = %d, read = %d\n", total_size, read(fd, &data->lib, total_size * 2));
	close(fd);
	return (0);
}


int				load_textures(t_doom *data)
{
	int		fd;

	fd = open("textures/textures_binary/gstvine1.binary", O_RDONLY);
	if (read(fd, data->lib.bg_anim_menu[0], 256 * 128 * 4) != 256 * 128 * 4)
		return (1);
	close(fd);
	fd = open("textures/textures_binary/gstvine2.binary", O_RDONLY);
	if (read(fd, data->lib.bg_anim_menu[1], 256 * 128 * 4) != 256 * 128 * 4)
		return (1);
	close(fd);
	fd = open("textures/textures_binary/background_menu.binary", O_RDONLY);
	if (read(fd, data->lib.bg_menu[0], 1920 * 1080 * 4) != 1920 * 1080 * 4)
		return (1);
	close(fd);
	fd = open("textures/textures_binary/background_scoreboard.binary", O_RDONLY);
	if (read(fd, data->lib.bg_menu[1], 1920 * 1080 * 4) != 1920 * 1080 * 4)
		return (1);
	close(fd);
	fd = open("textures/textures_binary/arrow_left.binary", O_RDONLY);
	if (read(fd, data->lib.arrows_menu[0], 64 * 64 * 4) != 64 * 64 * 4)
		return (1);
	close(fd);
	fd = open("textures/textures_binary/arrow_right.binary", O_RDONLY);
	if (read(fd, data->lib.arrows_menu[1], 64 * 64 * 4) != 64 * 64 * 4)
		return (1);
	close(fd);
	fd = open("textures/textures_binary/editor.binary", O_RDONLY);
	if (read(fd, data->lib.texture_editor[0], 1920 * 1080 * 4) != 1920 * 1080 * 4)
		return (1);
	close(fd);
	fd = open("textures/textures_binary/editor2.binary", O_RDONLY);
	if (read(fd, data->lib.texture_editor[1], 1920 * 1080 * 4) != 1920 * 1080 * 4)
		return (1);
	close(fd);
	fd = open("textures/textures_binary/doom-icon.binary", O_RDONLY);
	if (read(fd, data->lib.game_icon, 400 * 400 * 4) != 400 * 400 * 4)
		return (1);
	close(fd);
	fd = open("textures/textures_binary/character.binary", O_RDONLY);
	if (read(fd, data->lib.character, 500 * 350 * 4) != 500 * 350 * 4)
		return (1);
	close(fd);
	fd = open("textures/textures_binary/hud2.binary", O_RDONLY);
	if (read(fd, data->lib.hud_texture, 1920 * 1080 * 4) != 1920 * 1080 * 4)
		return (1);
	close(fd);
	if (load_sprites(data))
		return (1);
	return (0);
}
