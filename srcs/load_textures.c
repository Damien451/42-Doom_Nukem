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
#include <SDL_image.h>

#include <SDL.h>

static int		load_gun_textures(t_doom *data)
{
	int		i;
	int		fd;
	char	path[70];

	i = 0;
	while (++i <= NBR_TEXTURES_GUN)
	{
		ft_bzero(path, 70);
		sprintf(path, "./textures/gun_binary/gun%d", i);
		ft_strcat(path, ".binary");
		fd = open(path, O_RDONLY);
		ft_bzero(data->lib.gun_textures[i - 1], 350 * 100 * 4);
		if (read(fd, data->lib.gun_textures[i - 1], 4 * 350 * 100) != 4 * 350 * 100)
			return (1);
		close(fd);
	}
	return (0);
}

static int		load_enemy_textures(t_doom *data)
{
	int		i;
	int		fd;
	char	path[70];

	i = 0;
	while (++i <= NBR_TEXTURES_ENEMY)
	{
		ft_bzero(path, 70);
		sprintf(path, "./textures/enemy_binary/enemy%d", i);
		ft_strcat(path, ".binary");
		fd = open(path, O_RDONLY);
		if (read(fd, data->lib.enemy_textures[i - 1], 4 * 64 * 64) != 4 * 64 * 64)
			return (1);
		close(fd);
	}
	return (0);
}

static int		load_sprites(t_doom *data)
{
	int		fd;

	fd = open("textures/sprites_binary/circle.binary", O_RDONLY);
	if (read(fd, data->lib.sprites.circle, 128 * 128 * 4) != 128 * 128 * 4)
		return (1);
	close(fd);
	fd = open("textures/sprites_binary/ammo.binary", O_RDONLY);
	if (read(fd, data->lib.sprites.ammo, 15 * 32 * 4) != 15 * 32 * 4)
		return (1);
	close(fd);
	return (0);
}

static int		load_skybox(t_doom *data)
{
	int		fd;

	fd = open("textures/textures_binary/skybox1.binary", O_RDONLY);
	read(fd, data->skybox[0], 512 * 512 * 4);
	close(fd);
	fd = open("textures/textures_binary/skybox2.binary", O_RDONLY);
	read(fd, data->skybox[1], 512 * 512 * 4);
	close(fd);
	fd = open("textures/textures_binary/skybox3.binary", O_RDONLY);
	read(fd, data->skybox[2], 512 * 512 * 4);
	close(fd);
	fd = open("textures/textures_binary/skybox4.binary", O_RDONLY);
	read(fd, data->skybox[3], 512 * 512 * 4);
	close(fd);
	fd = open("textures/textures_binary/skybox5.binary", O_RDONLY);
	read(fd, data->skybox[4], 512 * 512 * 4);
	close(fd);
	fd = open("textures/textures_binary/skybox6.binary", O_RDONLY);
	read(fd, data->skybox[5], 512 * 512 * 4);
	close(fd);
	return (0);
}

static int		load_binary_textures(t_doom *data)
{
	int		fd;
	int		i;

	i = 0;
	dictionnary_binary_tex(data);
	while (i < NBR_TEXTURES_EDITOR)
	{
		fd = open(data->lib.texture_dic[i], O_RDONLY);
		if (i < 42)
		{
			if (read(fd, data->lib.textures[i], 128 * 128 * 4)
				!= 128 * 128 * 4)
				return (1);
		}
		else
			if (read(fd, data->lib.textures[i], 64 * 64 * 4) != 64 * 64 * 4)
				return (1);
		close(fd);
		i++;
	}
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
	if (read(fd, data->lib.editor.texture[0], 1920 * 1080 * 4) != 1920 * 1080 * 4)
		return (1);
	close(fd);
	fd = open("textures/textures_binary/editor2.binary", O_RDONLY);
	if (read(fd, data->lib.editor.texture[1], 1920 * 1080 * 4) != 1920 * 1080 * 4)
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
	if (load_binary_textures(data))
		return (1);
	if (load_enemy_textures(data))
		return (1);
	if (load_gun_textures(data))
		return (1);
	load_skybox(data);
	return (0);
}
