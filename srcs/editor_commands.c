
#include "doom.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include "vec3.h"

#include <stdio.h>

/*static inline void	put_textures_names(char *textures[4][10])
{
	textures[0][0] = "./textures/blocks/granite_polished.bmp";
	textures[0][1] = "./textures/blocks/granite.bmp";
	textures[0][2] = "./textures/blocks/nether_block.bmp";
	textures[0][3] = "./textures/blocks/nether_bricks.bmp";
	textures[0][4] = "./textures/blocks/quartz_pillar.bmp";
	textures[0][5] = "./textures/blocks/quartz.bmp";
	textures[0][6] = "./textures/blocks/sand.bmp";
	textures[0][7] = "./textures/blocks/sandstone_bricks.bmp";
	textures[0][8] = "./textures/blocks/sandstone_chiseled.bmp";
	textures[0][9] = "./textures/blocks/sandstone.bmp";
	textures[1][0] = "./textures/blocks/stone_bricks.bmp";
	textures[1][1] = "./textures/blocks/stone_chiseled.bmp";
	textures[1][2] = "./textures/blocks/stone_cobblestone.bmp";
	textures[1][3] = "./textures/blocks/stone_end_bricks.bmp";
	textures[1][4] = "./textures/blocks/stone_end.bmp";
	textures[1][5] = "./textures/blocks/obsidian.bmp";
	textures[1][6] = "./textures/blocks/stone_marine_bricks.bmp";
	textures[1][7] = "./textures/blocks/stone_mossy_bricks.bmp";
	textures[1][8] = "./textures/blocks/stone.bmp";
	textures[1][9] = "./textures/blocks/stone_smooth.bmp";
}

static inline void	pick_texture(t_doom *data, int x, int y)
{
	char	*textures[4][10];


	put_textures_names(textures);
	SDL_LoadBMP(textures[]);
}*/

static inline void	reset_step(t_doom *data, int step)
{
	int 		i;
	int			j;

	i = -1;
	while (++i < SIZE_MAP)
	{
		j = -1;
		while (++j < SIZE_MAP)
			data->map_to_save[step][i][j] = 0;
	}
}

static inline void	save_map_to_file(t_doom *data, char *str)
{
	int			fd;

	if ((fd = open(str, O_WRONLY | O_CREAT | O_TRUNC, 0777)) != -1)
	{
		write(fd, data->map_to_save, SIZE_MAP * SIZE_MAP * SIZE_MAP);
		close(fd);
	}
}

static inline void	keydown_editor_commands(t_doom *data, int *first)
{
	if (data->lib.event.key.keysym.sym == SDLK_ESCAPE)
	{
		switch_state(data, EDITOR, MAIN_MENU);
		*first = 0;
	}
}

static inline void	mouse_editor_commands(t_doom *data, int *ok, int *map, char str[50])
{
	//printf("x = %d, y = %d\n", data->lib.event.button.x, data->lib.event.button.y);
	if (data->lib.event.button.x >= 1052 && data->lib.event.button.y >= 16
		&& data->lib.event.button.x <= 1903 && data->lib.event.button.y <= 350)
		printf("yo");//pick_texture(data, data->lib.event.button.x, data->lib.event.button.y);
	else if (data->lib.event.button.x >= 15 && data->lib.event.button.y >= 15
		&& data->lib.event.button.x <= 1030 && data->lib.event.button.y <= 1030)
	{
		*ok = 1;
		color_rectangle(data, (t_vec3l){(data->lib.event.button.y - 10)
			- (data->lib.event.button.y - 10) % BLOCK_SIZE_EDITOR + 10
			, (data->lib.event.button.x - 10) - (data->lib.event.button.x - 10)
			% BLOCK_SIZE_EDITOR + 10, 0xFFFFFF}, *map);
	}
	else if(data->lib.event.button.x >= 0 && data->lib.event.button.y >= 1046
		&& data->lib.event.button.x <= 30 && data->lib.event.button.y <= 1079)
		save_map_to_file(data, str);
	else if (data->lib.event.button.x >= 37 && data->lib.event.button.y >= 1046
		&& data->lib.event.button.x <= 68 && data->lib.event.button.y <= 1079)
		*map = (*map < SIZE_MAP - 1 ? *map + 1 : *map);
	else if (data->lib.event.button.x >= 76 && data->lib.event.button.y >= 1046
		&& data->lib.event.button.x <= 109 && data->lib.event.button.y <= 1079)
		*map = (*map > 0 ? *map - 1 : *map);
	else if (data->lib.event.button.x >= 997 && data->lib.event.button.y >= 1046
		&& data->lib.event.button.x <= 1033 && data->lib.event.button.y <= 1079)
		reset_step(data, *map);
}

void		editor_commands(t_doom *data, char str[50], int *map, int *first)
{
	static int		ok = 0;

	if (data->lib.event.type == SDL_MOUSEBUTTONDOWN)
		mouse_editor_commands(data, &ok, map, str);
	if (data->lib.event.type == SDL_MOUSEBUTTONUP)
		ok = 0;
	if (ok == 1)
	{
		if (data->lib.event.button.y < 1034 && data->lib.event.button.x < 1034
			&& data->lib.event.button.y >= 10 && data->lib.event.button.x >= 10)
			color_rectangle(data, (t_vec3l){(data->lib.event.button.y - 10)
				- (data->lib.event.button.y - 10) % BLOCK_SIZE_EDITOR + 10
				, (data->lib.event.button.x - 10) - (data->lib.event.button.x
				- 10) % BLOCK_SIZE_EDITOR + 10, 0xFFFFFF}, *map);
	}
	else if (data->lib.event.type == SDL_KEYDOWN)
		keydown_editor_commands(data, first);
}