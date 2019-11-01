
#include "doom.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include "vec3.h"
#include "libft.h"

#include <stdio.h>

static inline void	pick_texture(t_doom *data, int x, int y)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	x -= 1052;
	y -= 16;
	while ((i + 1) * 85 < x)
		++i;
	while ((j + 1) * 83 < y)
		++j;
	data->lib.picked_texture = j * 10 + i;
}

static inline void	fill_step(t_doom *data, int step)
{
	int			i;
	int			j;

	i = -1;
	while (++i < SIZE_MAP)
	{
		j = -1;
		while (++j < SIZE_MAP)
		{
			if (data->lib.picked_texture)
				data->map_to_save[i][step][j] =
					data->lib.picked_texture + 1;
		}
	}
}

static inline void	reset_step(t_doom *data, int step)
{
	int			i;
	int			j;

	i = -1;
	while (++i < SIZE_MAP)
	{
		j = -1;
		while (++j < SIZE_MAP)
			data->map_to_save[i][step][j] = 0;
	}
}

static inline void	save_map_to_file(t_doom *data, char *str)
{
	int			fd;
	char		full_path[50];

	fd = 0;
	ft_bzero(full_path, 50);
	if (check_map_validity(data) == 0)
	{
		if ((fd = open(ft_strcat(ft_strcat(full_path, "./maps/"), str),
			O_WRONLY | O_CREAT | O_TRUNC, 0777)) != -1)
		{
			write(fd, data->map_to_save, SIZE_MAP * SIZE_MAP * SIZE_MAP);
			close(fd);
		}
	}
}

static inline void	draw(t_doom *data, int x, int y, int step)
{
	if (data->editor_mode == 1)
		data->map_to_save[(y - 10) / BLOCK_SIZE_EDITOR][step][(x - 10)
			/ BLOCK_SIZE_EDITOR] = 0;
	else
		data->map_to_save[(y - 10) / BLOCK_SIZE_EDITOR][step][(x - 10)
			/ BLOCK_SIZE_EDITOR] = data->lib.picked_texture + 1;
}

static inline void	keydown_editor_commands(t_doom *data, int *map, int *first)
{
	if (data->lib.event.key.keysym.sym == SDLK_UP ||
		(unsigned int)data->lib.event.key.keysym.sym ==
		data->tabinputs.keycode[0])
		*map = (*map < SIZE_MAP - 1 ? *map + 1 : *map);
	else if (data->lib.event.key.keysym.sym == SDLK_DOWN ||
		(unsigned int)data->lib.event.key.keysym.sym ==
		data->tabinputs.keycode[2])
		*map = (*map > 0 ? *map - 1 : *map);
	else if (data->lib.event.key.keysym.sym == SDLK_ESCAPE)
	{
		*first = 0;
		*map = 0;
		switch_state(data, EDITOR, EDITOR_MENU);
	}
}

static inline void	mouse_editor_commands2(t_doom *data, int *map)
{
	if (data->lib.event.button.x >= 919 && data->lib.event.button.y >= 1046
		&& data->lib.event.button.x <= 957 && data->lib.event.button.y <= 1079)
		data->editor_mode = (data->editor_mode == 0 ? 1 : 0);
	else if (data->lib.event.button.x >= 963 && data->lib.event.button.y >= 1046
		&& data->lib.event.button.x <= 997 && data->lib.event.button.y <= 1079)
		fill_step(data, *map);
}

static inline void	mouse_editor_commands(t_doom *data, int *ok,
	int *map, char str[50])
{
	//printf("x = %d, y = %d\n", data->lib.event.button.x, data->lib.event.button.y);
	if (data->lib.event.button.x >= 1052 && data->lib.event.button.y >= 16
		&& data->lib.event.button.x <= 1903 && data->lib.event.button.y <= 350)
		pick_texture(data, data->lib.event.button.x, data->lib.event.button.y);
	else if (data->lib.event.button.x >= 15 && data->lib.event.button.y >= 15
		&& data->lib.event.button.x <= 1030 && data->lib.event.button.y <= 1030)
	{
		*ok = 1;
		draw(data, data->lib.event.button.x, data->lib.event.button.y, *map);
	}
	else if (data->lib.event.button.x >= 0 && data->lib.event.button.y >= 1046
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
	mouse_editor_commands2(data, map);
}

void				editor_commands(t_doom *data, char str[50],
	int *map, int *first)
{
	static int		ok = 0;

	if (data->lib.event.type == SDL_MOUSEBUTTONDOWN)
		mouse_editor_commands(data, &ok, map, str);
	if (data->lib.event.type == SDL_MOUSEBUTTONUP)
		ok = 0;
	if (ok == 1)
	{
		if (data->lib.event.button.x >= 15 && data->lib.event.button.y >= 15
			&& data->lib.event.button.x <= 1030 &&
			data->lib.event.button.y <= 1030)
			draw(data, data->lib.event.button.x,
				data->lib.event.button.y, *map);
	}
	else if (data->lib.event.type == SDL_KEYDOWN)
		keydown_editor_commands(data, map, first);
}
