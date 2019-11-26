#include "doom.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include "vec3.h"

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
	else if (data->lib.event.key.keysym.sym == SDLK_t && !data->lib.event.key.repeat)
		data->editor_alpha = data->editor_alpha == 1 ? 10 : 1;
}

static inline void	mouse_editor_commands2(t_doom *data, int *map)
{
	if (data->lib.event.button.x >= 1859 && data->lib.event.button.y >= 573
		&& data->lib.event.button.x <= 1910 && data->lib.event.button.y <= 1070)
		data->editor_mode = (data->editor_mode == 0 ? 1 : 0);
	else if (data->lib.event.button.x >= 963 && data->lib.event.button.y >= 1046
		&& data->lib.event.button.x <= 997 && data->lib.event.button.y <= 1079)
		fill_step(data, *map);
}

static inline void	mouse_editor_commands(t_doom *data, int *ok,
	int *map, int button)
{
	printf("x = %d, y = %d\n", data->lib.event.button.x, data->lib.event.button.y);
	if (data->lib.event.button.x >= 1052 && data->lib.event.button.y >= 16
		&& data->lib.event.button.x <= 1903 && data->lib.event.button.y <= 350)
		pick_texture(data, data->lib.event.button.x, data->lib.event.button.y);
	else if (data->lib.event.button.x >= 15 && data->lib.event.button.y >= 15
		&& data->lib.event.button.x <= 1030 && data->lib.event.button.y <= 1030
		&& button == SDL_BUTTON_LEFT)
	{
		*ok = 1;
		draw_block(data, data->lib.event.button.x,
			data->lib.event.button.y, *map);
	}
	else if (data->lib.event.button.x >= 15 && data->lib.event.button.y >= 15
		&& data->lib.event.button.x <= 1030 && data->lib.event.button.y <= 1030
		&& button == SDL_BUTTON_RIGHT)
	{
		*ok = 1;
		erase_block(data, data->lib.event.button.x,
			data->lib.event.button.y, *map);
	}
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
		mouse_editor_commands(data, &ok, map, data->lib.event.button.button);
	if (data->lib.event.type == SDL_MOUSEBUTTONDOWN &&
		data->lib.event.button.x >= 0 && data->lib.event.button.y >= 1046
		&& data->lib.event.button.x <= 30 && data->lib.event.button.y <= 1079)
		save_map_to_file(data, str);
	if (data->lib.event.type == SDL_MOUSEBUTTONUP)
		ok = 0;
	if (ok == 1)
	{
		if (data->lib.event.button.button == SDL_BUTTON_LEFT)
			draw_block(data, data->lib.event.button.x,
				data->lib.event.button.y, *map);
		else if (data->lib.event.button.button == SDL_BUTTON_RIGHT)
			erase_block(data, data->lib.event.button.x,
				data->lib.event.button.y, *map);
	}
	else if (data->lib.event.type == SDL_KEYDOWN)
		keydown_editor_commands(data, map, first);
}
