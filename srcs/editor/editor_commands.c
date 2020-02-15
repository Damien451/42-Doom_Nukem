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
	{
		data->player.gamemode = TEST_MODE;
		switch_state(data, EDITOR, TEST_MODE);
	}
	else if (data->lib.event.key.keysym.sym == SDLK_g && !data->lib.event.key.repeat)
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

static inline void	mouse_button_up(SDL_Event *event, t_editor *editor)
{
	if (event->button.button == SDL_BUTTON_LEFT)
		editor->mouseinputs &= ~L_INPUT_EDITOR;
	else if (event->button.button == SDL_BUTTON_RIGHT)
		editor->mouseinputs &= ~R_INPUT_EDITOR;
}

static inline void	mouse_button_down(t_doom *data, int *step,
	SDL_Event *event, t_editor *editor)
{
	if (event->button.x >= 15 && event->button.y >= 15
		&& event->button.x <= 1030 && event->button.y <= 1030 &&
		event->button.button == SDL_BUTTON_LEFT)
		editor->mouseinputs |= L_INPUT_EDITOR;
	else if (event->button.button == SDL_BUTTON_RIGHT)
		editor->mouseinputs |= R_INPUT_EDITOR;
	mouse_editor_commands(data, step);
}

void				editor_commands(t_doom *data, char map_name[50],
	int *step, int *first)
{
	if (data->lib.event.type == SDL_MOUSEBUTTONDOWN)
		mouse_button_down(data, step, &data->lib.event, &data->lib.editor);
	if (data->lib.event.type == SDL_MOUSEBUTTONDOWN
		&& data->lib.editor.mode == 0
		&& data->lib.event.button.x >= 1197 && data->lib.event.button.y >= 773
		&& data->lib.event.button.x <= 1226 && data->lib.event.button.y <= 802)
		save_map_to_file(data, map_name);
	if (data->lib.event.type == SDL_MOUSEBUTTONUP)
		mouse_button_up(&data->lib.event, &data->lib.editor);
	if (data->lib.editor.mouseinputs & L_INPUT_EDITOR)
		draw_block(data, data->lib.event.button.x,
			data->lib.event.button.y, *step);
	else if (data->lib.editor.mouseinputs & R_INPUT_EDITOR)
		erase_block(data, data->lib.event.button.x,
			data->lib.event.button.y, *step);
	else if (data->lib.event.type == SDL_KEYDOWN)
		keydown_editor_commands(data, step, first, map_name);
}
