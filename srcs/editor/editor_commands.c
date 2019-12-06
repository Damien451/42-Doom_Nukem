#include "doom.h"
#include "libft.h"
#include <inputs.h>
#include <fcntl.h>
#include <unistd.h>
#include "vec3.h"

static inline void	save_map_to_file(t_doom *data, char *map_name)
{
	int			fd;
	char		full_path[50];

	fd = 0;
	ft_bzero(full_path, 50);
	if (check_map_validity(data) == 0)
	{
		if ((fd = open(ft_strcat(ft_strcat(full_path, "./maps/"), map_name),
			O_WRONLY | O_CREAT | O_TRUNC, 0777)) != -1)
		{
			write(fd, data->map_to_save, SIZE_MAP * SIZE_MAP * SIZE_MAP);
			close(fd);
		}
	}
}

static inline void	keydown_editor_commands(t_doom *data, int *step, int *first,
	char *map_name)
{
	if (data->lib.event.key.keysym.sym == SDLK_UP)
		*step = (*step < SIZE_MAP - 1 ? *step + 1 : *step);
	else if (data->lib.event.key.keysym.sym == SDLK_DOWN)
		*step = (*step > 0 ? *step - 1 : *step);
	else if (data->lib.event.key.keysym.sym == SDLK_ESCAPE)
	{
		*first = 0;
		*step = 0;
		switch_state(data, EDITOR, EDITOR_MENU);
	}
	else if (data->lib.event.key.keysym.sym == SDLK_t && !data->lib.event.key.repeat)
		data->lib.editor.alpha = data->lib.editor.alpha == 1 ? 10 : 1;
	else if (data->lib.event.key.keysym.sym == SDLK_s && !data->lib.event.key.repeat)
		save_map_to_file(data, map_name);
	else if (data->lib.event.key.keysym.sym == SDLK_f && !data->lib.event.key.repeat)
		fill_step(data, *step);
	else if (data->lib.event.key.keysym.sym == SDLK_r && !data->lib.event.key.repeat)
		reset_step(data, *step);
	else if (data->lib.event.key.keysym.sym == SDLK_c && !data->lib.event.key.repeat)
		copy_step(data, *step);
}

void				editor_commands(t_doom *data, char map_name[50],
	int *step, int *first)
{
	static int		ok = 0;

	if (data->lib.event.button.x >= 1859 && data->lib.event.button.y >= 573
		&& data->lib.event.button.x <= 1910 && data->lib.event.button.y <= 1070
		&& data->lib.event.type == SDL_MOUSEBUTTONDOWN)
		data->lib.editor.mode = (data->lib.editor.mode == 0 ? 1 : 0);
	if (data->lib.event.type == SDL_MOUSEBUTTONDOWN)
		mouse_editor_commands(data, &ok, step, data->lib.event.button.button);
	if (data->lib.event.type == SDL_MOUSEBUTTONDOWN
		&& data->lib.editor.mode == 0
		&& data->lib.event.button.x >= 1197 && data->lib.event.button.y >= 773
		&& data->lib.event.button.x <= 1226 && data->lib.event.button.y <= 802)
		save_map_to_file(data, map_name);
	if (data->lib.event.type == SDL_MOUSEBUTTONUP)
		ok = 0;
	if (ok == 1)
	{
		if (data->lib.event.button.button == SDL_BUTTON_LEFT)
			draw_block(data, data->lib.event.button.x,
				data->lib.event.button.y, *step);
		if (data->lib.event.button.button == SDL_BUTTON_RIGHT)
			erase_block(data, data->lib.event.button.x,
				data->lib.event.button.y, *step);
	}
	else if (data->lib.event.type == SDL_KEYDOWN)
		keydown_editor_commands(data, step, first, map_name);
}
