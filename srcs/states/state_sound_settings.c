#include "doom.h"
#include "libft.h"
#include "menus.h"
#include "inputs.h"
#include <fcntl.h>
#include <unistd.h>

static void	mouse_sound_commands2(t_doom *data, int tab[3])
{
	if (data->lib.event.button.y >= BAR_HEIGHT_START + 2 * BAR_GAP
		&& data->lib.event.button.x >= BAR_WIDTH_START
		&& data->lib.event.button.y <= BAR_HEIGHT_START + BAR_HEIGHT + 2
		* BAR_GAP && data->lib.event.button.x <= BAR_WIDTH_START + BAR_WIDTH)
	{
		tab[2] = (int)((data->lib.event.button.x - BAR_WIDTH_START)
			* 100.0 / BAR_WIDTH + 0.5);
		set_sound_effects_volume(data->mix, (data->lib.event.button.x -
			(double)BAR_WIDTH_START) / (double)BAR_WIDTH);
	}
	else if (data->lib.event.button.x >= WIDTH_CENTER - DEF_BUTTON_W &&
		data->lib.event.button.y >= HEIGHT_CENTER + (3 * DEF_BUTTON_H + 3
		* BUTTON_GAP_Y) && data->lib.event.button.x <= WIDTH_CENTER 
		- DEF_BUTTON_W + DEF_BUTTON_W * 2 &&
		data->lib.event.button.y <= HEIGHT_CENTER + (3 * DEF_BUTTON_H + 3
		* BUTTON_GAP_Y) + DEF_BUTTON_H)
	{
		switch_state(data, SETTINGS_SOUND, SETTINGS);
	}
}

static void	mouse_sound_commands(t_doom *data, int tab[3])
{
	if (data->lib.event.button.y >= BAR_HEIGHT_START &&
		data->lib.event.button.x >= BAR_WIDTH_START && data->lib.event.button.y
		<= BAR_HEIGHT_START + BAR_HEIGHT && data->lib.event.button.x
		<= BAR_WIDTH_START + BAR_WIDTH)
	{
		tab[0] = (int)((data->lib.event.button.x - BAR_WIDTH_START)
			* 100.0 / BAR_WIDTH + 0.5);
		set_master_volume(data->mix, (data->lib.event.button.x -
			(double)BAR_WIDTH_START) / (double)BAR_WIDTH);
	}
	else if (data->lib.event.button.y >= BAR_HEIGHT_START + BAR_GAP &&
		data->lib.event.button.x >= BAR_WIDTH_START && data->lib.event.button.y
		<= BAR_HEIGHT_START + BAR_HEIGHT + BAR_GAP && data->lib.event.button.x
		<= BAR_WIDTH_START + BAR_WIDTH)
	{
		tab[1] = (int)((data->lib.event.button.x - BAR_WIDTH_START)
			* 100.0 / BAR_WIDTH + 0.5);
		set_music_volume(data->mix, (data->lib.event.button.x -
			(double)BAR_WIDTH_START) / (double)BAR_WIDTH);
	}
	mouse_sound_commands2(data, tab);
}

static int	check_sound_settings(t_doom *data, int tab[3])
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
		{
			if (data->lib.event.key.keysym.sym == SDLK_RETURN &&
				data->button == 0)
				switch_state(data, SETTINGS_SOUND, SETTINGS);
			else if (data->lib.event.key.keysym.sym == SDLK_RETURN &&
				data->button == 1)
				get_default_sounds(data);
		}
		if (data->lib.event.type == SDL_MOUSEBUTTONDOWN)
			mouse_sound_commands(data, tab);
	}
	return (0);
}

int			state_sound_settings(t_doom *data)
{
	t_button	buttons[2];
	static int	first = 1;
	static int	tab[3];

	if (first == 1)
	{
		tab[0] = (int)(data->mix->v_master * 100);
		tab[1] = (int)(data->mix->v_music * 100);
		tab[2] = (int)(data->mix->v_sound_effects * 100);
	}
	buttons[0] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER + (3 * DEF_BUTTON_H + 3 * BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), LEAVING, "RETURN");
	buttons[1] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER + (4 * DEF_BUTTON_H + 4 * BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), LEAVING, "RESET");
	ft_memset(data->lib.image, 0, WIDTH * HEIGHT * 4);
	ft_memcpy(data->lib.image, data->lib.menu_texture[4]->pixels, (WIDTH * HEIGHT) << 2);
	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_ShowCursor(SDL_TRUE);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	if (check_sound_settings(data, tab) != 0)
		return (1);
	put_buttons_on_img(data, buttons, 2);
	put_buttons_names(data, buttons, BLACK, 2);
	put_sound_bars(data, tab);
	put_string_on_renderer(data, point(WIDTH / 2, HEIGHT / 13),
		label("SETTINGS", RED), data->lib.ptrfont[1]);
	SDL_RenderPresent(data->lib.renderer);
	return (0);
}
