/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 13:59:18 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/29 18:40:28 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include <fcntl.h>
#include <unistd.h>
#include <SDL_image.h>

static void		load_skybox(t_doom *data)
{
	int		fd;

	fd = 0;
	data->skybox = malloc(sizeof(int*) * 6);
	while (fd < 6)
		data->skybox[fd++] = malloc(sizeof(int) * 512 * 512);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/textures_binary/skybox1.binary", O_RDONLY);
	read(fd, data->skybox[0], 512 * 512 * 4);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/textures_binary/skybox2.binary", O_RDONLY);
	read(fd, data->skybox[1], 512 * 512 * 4);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/textures_binary/skybox3.binary", O_RDONLY);
	read(fd, data->skybox[2], 512 * 512 * 4);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/textures_binary/skybox4.binary", O_RDONLY);
	read(fd, data->skybox[3], 512 * 512 * 4);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/textures_binary/skybox5.binary", O_RDONLY);
	read(fd, data->skybox[4], 512 * 512 * 4);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/textures_binary/skybox6.binary", O_RDONLY);
	read(fd, data->skybox[5], 512 * 512 * 4);
	close(fd);
}


static void		load_binary_textures(t_doom *data)
{
	int		fd;
	int		i;

	i = 0;
	dictionnary_binary_tex(data);
	while (i < NBR_TEXTURES_EDITOR)
	{
		if (i < 42)
			data->lib.textures[i] = malloc(128 * 128 * 4);
		else
			data->lib.textures[i] = malloc(64 * 64 * 4);
		fd = open(data->lib.texture_dic[i], O_RDONLY);
		if (i < 42)
			read(fd, data->lib.textures[i], 128 * 128 * 4);
		else
			read(fd, data->lib.textures[i], 64 * 64 * 4);
		close(fd);
		i++;
	}
}

static int		get_texture(unsigned int **dest, int size, char *path_text)
{
	int		fd;
	
	if (!(*dest = malloc(size)))
		return (1);
	fd = open(path_text, O_RDONLY);
	if (read(fd, *dest, size) != size)
		return (1);
	close(fd);
	return (0);
}

int				load_textures(t_doom *data)
{
	get_texture(&data->lib.character, 500 * 350 * 4,
		"/sgoinfre/goinfre/Perso/dacuvill/textures_binary/character.binary");
	get_texture(&data->lib.menu_texture[0], 256 * 128 * 4,
		"/sgoinfre/goinfre/Perso/dacuvill/textures_binary/gstvine1.binary");
	get_texture(&data->lib.menu_texture[1], 256 * 128 * 4,
		"/sgoinfre/goinfre/Perso/dacuvill/textures_binary/gstvine2.binary");
	get_texture(&data->lib.menu_texture[2], 1920 * 1080 * 4,
		"/sgoinfre/goinfre/Perso/dacuvill/textures_binary/background_menu.binary");
	get_texture(&data->lib.menu_texture[3], 1920 * 1080 * 4,
		"/sgoinfre/goinfre/Perso/dacuvill/textures_binary/background_scoreboard.binary");
	get_texture(&data->lib.menu_texture[4], 64 * 64 * 4,
		"/sgoinfre/goinfre/Perso/dacuvill/textures_binary/arrow_left.binary");
	get_texture(&data->lib.menu_texture[5], 64 * 64 * 4,
		"/sgoinfre/goinfre/Perso/dacuvill/textures_binary/arrow_right.binary");
	data->lib.game_icon = IMG_Load("textures/doom-icon.bmp");
	data->lib.editor.texture[0] = IMG_Load("textures/editor.bmp");
	data->lib.editor.texture[1] = IMG_Load("textures/editor2.bmp");
	data->lib.ennemy = IMG_Load("textures/ennemy.bmp");
	get_texture(&data->lib.hud_texture, 1920 * 1080 * 4,
		"/sgoinfre/goinfre/Perso/dacuvill/textures_binary/hud2.binary");
	load_binary_textures(data);
	load_skybox(data);
	return (0);
}
