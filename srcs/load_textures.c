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
	textures[12] = SDL_LoadBMP("/sgoinfre/goinfre/Perso/dacuvill/blocks/stone_smooth_white.bmp");
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


static void		load_textures_new_blocks_binaries2(t_doom *data)
{
	int		fd;

	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/quartz.binary", O_RDONLY);
	read(fd, data->lib.textures_block[24], 512 * 512 * 4);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/quartz_pillar.binary", O_RDONLY);
	read(fd, data->lib.textures_block[25], 512 * 512 * 4);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/quartz_chiseled.binary", O_RDONLY);
	read(fd, data->lib.textures_block[26], 512 * 512 * 4);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/iron_bars.binary", O_RDONLY);
	read(fd, data->lib.textures_block[27], 512 * 512 * 4);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/block_binary/glass.binary", O_RDONLY);
	read(fd, data->lib.textures_block[28], 512 * 512 * 4);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/obsidian.binary", O_RDONLY);
	read(fd, data->lib.textures_block[29], 512 * 512 * 4);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/start_block.binary", O_RDONLY);
	read(fd, data->lib.textures_block[30], 512 * 512 * 4);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/arrival_block.binary", O_RDONLY);
	read(fd, data->lib.textures_block[31], 512 * 512 * 4);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/water.binary", O_RDONLY);
	read(fd, data->lib.textures_block[32], 512 * 512 * 4);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/gold.binary", O_RDONLY);
	read(fd, data->lib.textures_block[33], 512 * 512 * 4);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/iron.binary", O_RDONLY);
	read(fd, data->lib.textures_block[34], 512 * 512 * 4);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/wood_oak.binary", O_RDONLY);
	read(fd, data->lib.textures_block[35], 512 * 512 * 4);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/wood_oak_planks.binary", O_RDONLY);
	read(fd, data->lib.textures_block[36], 512 * 512 * 4);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/wood_dark_oak.binary", O_RDONLY);
	read(fd, data->lib.textures_block[37], 512 * 512 * 4);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/wood_dark_oak_planks.binary", O_RDONLY);
	read(fd, data->lib.textures_block[38], 512 * 512 * 4);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/dirt.binary", O_RDONLY);
	read(fd, data->lib.textures_block[39], 512 * 512 * 4);
	close(fd);
}

static void		load_binary_textures(t_doom *data)
{
	int		fd;

	fd = 0;
	while (fd < NBR_TEXTURES_BLOCKS)
	{
		data->lib.textures_block[fd] = malloc(512 * 512 * 4);
		fd++;
	}
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/andesite.binary", O_RDONLY);
	read(fd, data->lib.textures_block[0], 512 * 4 * 512);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/andesite_polished.binary", O_RDONLY);
	read(fd, data->lib.textures_block[1], 512 * 4 * 512);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/diorite.binary", O_RDONLY);
	read(fd, data->lib.textures_block[2], 512 * 4 * 512);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/diorite_polished.binary", O_RDONLY);
	read(fd, data->lib.textures_block[3], 512 * 4 * 512);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/granite.binary", O_RDONLY);
	read(fd, data->lib.textures_block[4], 512 * 4 * 512);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/granite_polished.binary", O_RDONLY);
	read(fd, data->lib.textures_block[5], 512 * 4 * 512);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/sand.binary", O_RDONLY);
	read(fd, data->lib.textures_block[6], 512 * 4 * 512);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/sandstone.binary", O_RDONLY);
	read(fd, data->lib.textures_block[7], 512 * 4 * 512);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/sandstone_bricks.binary", O_RDONLY);
	read(fd, data->lib.textures_block[8], 512 * 4 * 512);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/sandstone_chiseled.binary", O_RDONLY);
	read(fd, data->lib.textures_block[9], 512 * 4 * 512);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/stone_cut.binary", O_RDONLY);
	read(fd, data->lib.textures_block[10], 512 * 4 * 512);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/stone_smooth.binary", O_RDONLY);
	read(fd, data->lib.textures_block[11], 512 * 4 * 512);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/stone_smooth_white.binary", O_RDONLY);
	read(fd, data->lib.textures_block[12], 512 * 4 * 512);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/stone_slabs.binary", O_RDONLY);
	read(fd, data->lib.textures_block[13], 512 * 4 * 512);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/stone_bricks.binary", O_RDONLY);
	read(fd, data->lib.textures_block[14], 512 * 4 * 512);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/stone_bricks_mossy.binary", O_RDONLY);
	read(fd, data->lib.textures_block[15], 512 * 4 * 512);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/stone_bricks_cracked.binary", O_RDONLY);
	read(fd, data->lib.textures_block[16], 512 * 4 * 512);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/stone_bricks_chiseled.binary", O_RDONLY);
	read(fd, data->lib.textures_block[17], 512 * 4 * 512);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/stone_cobble.binary", O_RDONLY);
	read(fd, data->lib.textures_block[18], 512 * 4 * 512);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/stone_cobble_mossy.binary", O_RDONLY);
	read(fd, data->lib.textures_block[19], 512 * 4 * 512);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/stone.binary", O_RDONLY);
	read(fd, data->lib.textures_block[20], 512 * 4 * 512);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/nether_rock.binary", O_RDONLY);
	read(fd, data->lib.textures_block[21], 512 * 4 * 512);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/nether_bricks.binary", O_RDONLY);
	read(fd, data->lib.textures_block[22], 512 * 4 * 512);
	close(fd);
	fd = open("/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/gravel.binary", O_RDONLY);
	read(fd, data->lib.textures_block[23], 512 * 4 * 512);
	close(fd);
	load_textures_new_blocks_binaries2(data);
}

void			load_textures(t_doom *data)
{
	data->lib.character = SDL_LoadBMP("textures/character.bmp");
	data->lib.menu_texture[0] = SDL_LoadBMP("textures/gstvine1.bmp");
	data->lib.menu_texture[1] = SDL_LoadBMP("textures/gstvine2.bmp");
	data->lib.menu_texture[2] = SDL_LoadBMP("enemy_menu.bmp");
	data->lib.menu_texture[3] = SDL_LoadBMP("energy_orb.bmp");
	data->lib.menu_texture[4] = SDL_LoadBMP("textures/background_menu.bmp");
	data->lib.editor_texture[0] = SDL_LoadBMP("textures/editor.bmp");
	data->lib.editor_texture[1] = SDL_LoadBMP("textures/editor2.bmp");
	data->lib.hud_texture = SDL_LoadBMP("textures/hud.bmp");
	load_binary_textures(data);
	load_skybox(data);
	load_textures_blocks(data->lib.textures);
	data->lib.picked_texture = NBR_TEXTURES_BLOCKS;
}
