#include "doom.h"
#include "graphic_lib.h"
#include <fcntl.h>
#include <unistd.h>
#include <SDL_image.h>

static void		load_textures_blocks2(SDL_Surface *textures[NBR_TEXTURES_BLOCKS])
{
	textures[24] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/quartz.bmp");
	textures[25] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/quartz_pillar.bmp");
	textures[26] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/quartz_chiseled.bmp");
	textures[27] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/iron_bars.bmp");
	textures[28] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/glass.bmp");
	textures[29] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/obsidian.bmp");
	textures[30] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/start_block.bmp");
	textures[31] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/arrival_block.bmp");
	textures[32] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/water.bmp");
	textures[33] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/gold.bmp");
	textures[34] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/iron.bmp");
	textures[35] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/wood_oak.bmp");
	textures[36] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/wood_oak_planks.bmp");
	textures[37] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/wood_dark_oak.bmp");
	textures[38] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/wood_dark_oak_planks.bmp");
	textures[39] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/dirt.bmp");
	textures[40] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/glowstone.bmp");
}

static void		load_textures_blocks(SDL_Surface *textures[NBR_TEXTURES_BLOCKS])
{
	textures[0] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/andesite.bmp");
	textures[1] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/andesite_polished.bmp");
	textures[2] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/diorite.bmp");
	textures[3] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/diorite_polished.bmp");
	textures[4] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/granite.bmp");
	textures[5] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/granite_polished.bmp");
	textures[6] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/sand.bmp");
	textures[7] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/sandstone.bmp");
	textures[8] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/sandstone_bricks.bmp");
	textures[9] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/sandstone_chiseled.bmp");
	textures[10] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/stone_cut.bmp");
	textures[11] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/stone_smooth.bmp");
	textures[12] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/stone_pavement.bmp");
	textures[13] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/stone_slabs.bmp");
	textures[14] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/stone_bricks.bmp");
	textures[15] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/stone_bricks_mossy.bmp");
	textures[16] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/stone_bricks_cracked.bmp");
	textures[17] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/stone_bricks_chiseled.bmp");
	textures[18] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/stone_cobble.bmp");
	textures[19] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/stone_cobble_mossy.bmp");
	textures[20] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/stone.bmp");
	textures[21] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/nether_rock.bmp");
	textures[22] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/nether_bricks.bmp");
	textures[23] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/gravel.bmp");
	load_textures_blocks2(textures);
}

static void		load_skybox(t_doom *data)
{
	int		i;
	data->lib.skybox[0] = SDL_LoadBMP("textures/hell_rt.bmp");
	data->lib.skybox[1] = SDL_LoadBMP("textures/hell_ft.bmp");
	data->lib.skybox[2] = SDL_LoadBMP("textures/hell_lf.bmp");
	data->lib.skybox[3] = SDL_LoadBMP("textures/hell_bk.bmp");
	data->lib.skybox[4] = SDL_LoadBMP("textures/hell_up.bmp");
	data->lib.skybox[5] = SDL_LoadBMP("textures/hell_dn.bmp");
	i = 0;
	while (i < 6)
	{
		data->lib.skybox_t[i] = SDL_CreateTextureFromSurface(data->lib.renderer, data->lib.skybox[i]);
		i++;
	}
}

void			load_binary_textures(t_doom *data)
{
	int		fd;

	fd = 0;
	while (fd < NBR_TEXTURES_BLOCKS)
	{
		data->lib.textures_block[fd] = malloc(128 * 128 * 4);
		fd++;
	}
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/0.binary", O_RDONLY);
	read(fd, data->lib.textures_block[0], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/1.binary", O_RDONLY);
	read(fd, data->lib.textures_block[1], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/3.binary", O_RDONLY);
	read(fd, data->lib.textures_block[2], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/4.binary", O_RDONLY);
	read(fd, data->lib.textures_block[3], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/8.binary", O_RDONLY);
	read(fd, data->lib.textures_block[4], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/9.binary", O_RDONLY);
	read(fd, data->lib.textures_block[5], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/19.binary", O_RDONLY);
	read(fd, data->lib.textures_block[6], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/20.binary", O_RDONLY);
	read(fd, data->lib.textures_block[7], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/21.binary", O_RDONLY);
	read(fd, data->lib.textures_block[8], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/22.binary", O_RDONLY);
	read(fd, data->lib.textures_block[9], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/31.binary", O_RDONLY);
	read(fd, data->lib.textures_block[10], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/33.binary", O_RDONLY);
	read(fd, data->lib.textures_block[11], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/34.binary", O_RDONLY);
	read(fd, data->lib.textures_block[12], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/32.binary", O_RDONLY);
	read(fd, data->lib.textures_block[13], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/25.binary", O_RDONLY);
	read(fd, data->lib.textures_block[14], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/28.binary", O_RDONLY);
	read(fd, data->lib.textures_block[15], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/27.binary", O_RDONLY);
	read(fd, data->lib.textures_block[16], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/26.binary", O_RDONLY);
	read(fd, data->lib.textures_block[17], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/29.binary", O_RDONLY);
	read(fd, data->lib.textures_block[18], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/30.binary", O_RDONLY);
	read(fd, data->lib.textures_block[19], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/24.binary", O_RDONLY);
	read(fd, data->lib.textures_block[20], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/14.binary", O_RDONLY);
	read(fd, data->lib.textures_block[21], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/13.binary", O_RDONLY);
	read(fd, data->lib.textures_block[22], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/10.binary", O_RDONLY);
	read(fd, data->lib.textures_block[23], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/16.binary", O_RDONLY);
	read(fd, data->lib.textures_block[24], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/18.binary", O_RDONLY);
	read(fd, data->lib.textures_block[25], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/17.binary", O_RDONLY);
	read(fd, data->lib.textures_block[26], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/12.binary", O_RDONLY);
	read(fd, data->lib.textures_block[27], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/6.binary", O_RDONLY);
	read(fd, data->lib.textures_block[28], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/15.binary", O_RDONLY);
	read(fd, data->lib.textures_block[29], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/23.binary", O_RDONLY);
	read(fd, data->lib.textures_block[30], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/2.binary", O_RDONLY);
	read(fd, data->lib.textures_block[31], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/35.binary", O_RDONLY);
	read(fd, data->lib.textures_block[32], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/7.binary", O_RDONLY);
	read(fd, data->lib.textures_block[33], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/11.binary", O_RDONLY);
	read(fd, data->lib.textures_block[34], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/38.binary", O_RDONLY);
	read(fd, data->lib.textures_block[35], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/39.binary", O_RDONLY);
	read(fd, data->lib.textures_block[36], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/36.binary", O_RDONLY);
	read(fd, data->lib.textures_block[37], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/37.binary", O_RDONLY);
	read(fd, data->lib.textures_block[38], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/5.binary", O_RDONLY);
	read(fd, data->lib.textures_block[39], 128 * 4 * 128);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/40.binary", O_RDONLY);
	read(fd, data->lib.textures_block[40], 128 * 4 * 128);
	close(fd);
}

void			load_textures(t_doom *data)
{
	data->lib.character = SDL_LoadBMP("textures/character.bmp");
	data->lib.menu_texture[0] = SDL_LoadBMP("textures/gstvine1.bmp");
	data->lib.menu_texture[1] = SDL_LoadBMP("textures/gstvine2.bmp");
	data->lib.menu_texture[2] = SDL_LoadBMP("enemy_menu.bmp");
	data->lib.menu_texture[3] = SDL_LoadBMP("energy_orb.bmp");
	data->lib.menu_texture[4] = SDL_LoadBMP("textures/background_menu.bmp");
	data->lib.editor.texture[0] = SDL_LoadBMP("textures/editor.bmp");
	data->lib.editor.texture[1] = SDL_LoadBMP("textures/editor2.bmp");
	data->lib.hud_texture = SDL_LoadBMP("textures/hud.bmp");
	load_binary_textures(data);
	load_skybox(data);
	load_textures_blocks(data->lib.textures);
}
