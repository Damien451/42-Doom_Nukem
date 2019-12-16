/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 13:59:18 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/16 23:33:10 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include <fcntl.h>
#include <unistd.h>
#include <SDL_image.h>

static void		load_textures_blocks2(SDL_Surface *textures[NBR_TEXTURES_BLOCKS])
{
	textures[24] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/quartz.bmp");
	textures[25] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/quartz_pillar.bmp");
	textures[26] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/quartz_chiseled.bmp");
	textures[27] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/iron_bars.bmp");
	textures[28] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/glass.bmp");
	textures[29] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/obsidian.bmp");
	textures[30] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/start_block.bmp");
	textures[31] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/arrival_block.bmp");
	textures[32] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/water.bmp");
	textures[33] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/gold.bmp");
	textures[34] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/iron.bmp");
	textures[35] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/wood_oak.bmp");
	textures[36] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/wood_oak_planks.bmp");
	textures[37] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/wood_dark_oak.bmp");
	textures[38] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/wood_dark_oak_planks.bmp");
	textures[39] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/dirt.bmp");
	textures[40] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/glowstone.bmp");
}

static void		load_textures_blocks(SDL_Surface *textures[NBR_TEXTURES_BLOCKS])
{
	textures[0] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/andesite.bmp");
	textures[1] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/andesite_polished.bmp");
	textures[2] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/diorite.bmp");
	textures[3] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/diorite_polished.bmp");
	textures[4] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/granite.bmp");
	textures[5] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/granite_polished.bmp");
	textures[6] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/sand.bmp");
	textures[7] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/sandstone.bmp");
	textures[8] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/sandstone_bricks.bmp");
	textures[9] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/sandstone_chiseled.bmp");
	textures[10] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/stone_cut.bmp");
	textures[11] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/stone_smooth.bmp");
	textures[12] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/stone_pavement.bmp");
	textures[13] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/stone_slabs.bmp");
	textures[14] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/stone_bricks.bmp");
	textures[15] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/stone_bricks_mossy.bmp");
	textures[16] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/stone_bricks_cracked.bmp");
	textures[17] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/stone_bricks_chiseled.bmp");
	textures[18] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/stone_cobble.bmp");
	textures[19] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/stone_cobble_mossy.bmp");
	textures[20] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/stone.bmp");
	textures[21] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/nether_rock.bmp");
	textures[22] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/nether_bricks.bmp");
	textures[23] = IMG_Load("/sgoinfre/goinfre/Perso/dacuvill/blocks/gravel.bmp");
	load_textures_blocks2(textures);
}
/*
int				load_binary_textures(t_doom *data)
{
	int			ret;

}
*/
void			load_binary_textures(t_doom *data)
{
	int		fd;
	int		i;

	i = 0;
	dictionnary_binary_tex(data);
	while (i < NBR_TEXTURES_BLOCKS)
	{
		data->lib.textures_block[i] = malloc(128 * 128 * 4);
		fd = open(data->lib.texture_dic[i], O_RDONLY);
		read(fd, data->lib.textures_block[i], 128 * 128 * 4);
		close(fd);
		i++;
	}
}

void			load_textures(t_doom *data)
{
	data->lib.character = IMG_Load("textures/character.bmp");
	data->lib.menu_texture[0] = IMG_Load("textures/gstvine1.bmp");
	data->lib.menu_texture[1] = IMG_Load("textures/gstvine2.bmp");
	data->lib.menu_texture[2] = IMG_Load("enemy_menu.bmp");
	data->lib.menu_texture[3] = IMG_Load("energy_orb.bmp");
	data->lib.menu_texture[4] = IMG_Load("textures/background_menu.bmp");
	data->lib.editor.texture[0] = IMG_Load("textures/editor.bmp");
	data->lib.editor.texture[1] = IMG_Load("textures/editor2.bmp");
	data->lib.hud_texture = IMG_Load("textures/hud2.png");
	load_binary_textures(data);
	load_textures_blocks(data->lib.textures);
}
