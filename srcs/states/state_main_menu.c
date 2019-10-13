#include "doom.h"
#include "libft.h"
#include "menus.h"

static int	create_character_animation(t_doom *data, unsigned int *image, int movement)
{
	int			i;
	int			j;

	i = 0;
	while (i < 200)
	{
		j = 0;
		while (j < 200)
		{
			if (((int*)data->lib.character->pixels)[(i / 4) * 500 + movement + (j / 4)])
				image[i * WIDTH + j + 525 * WIDTH + WIDTH / 16] = ((int*)data->lib.character->pixels)[(i / 4) * 500 + movement + (j / 4)];
			j++;
		}
		i++;
	}
	return (0);
}

static void	check_inputs_menu(t_doom *data, t_button *btab, int nbuttons)
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
		{
			if (data->lib.event.key.keysym.sym == SDLK_UP)
			{
				if (data->button == 0)
					data->button = nbuttons - 1;
				else
					--data->button;
			}
			if (data->lib.event.key.keysym.sym == SDLK_DOWN)
			{
				if (data->button == nbuttons - 1)
					data->button = 0;
				else
					++data->button;
			}
			if (data->lib.event.key.keysym.sym == SDLK_RETURN)
				switch_state(data, MAIN_MENU, btab[data->button].state);
		}
	}
}

static void	create_texture_anim(t_doom *data, int frame)
{
	int		i;
	int		j;

	i = 0;
	frame++;
	while (i < WIDTH)
	{
		j = 0;
		while (j < 128)
		{
			data->lib.image[i + j * WIDTH + 512 * WIDTH] = ((int*)data->lib.menu_texture[((i + frame) / 256) % 2]->pixels)[(i + frame) % 192 + j * 192];
			if (j < 64)
			data->lib.image[i + j * (WIDTH - 2) + 640 * WIDTH] = ((int*)data->lib.menu_texture[((i + frame) / 256) % 2]->pixels)[(i + frame) * 2 % 192 + j * 192 * 2] + 18;
			j++;
		}
		i++;
	}
}

int			state_main_menu(t_doom *data)
{
	t_button	buttons[4];
	static int	frame = 0;
	static int	total_frame = 0;
	int			ret;

	ft_memset(data->lib.image, 0, WIDTH * HEIGHT * 4);
	create_texture_anim(data, total_frame);
	if (frame >= 160 && frame <= 256)
	{
		if ((ret = frame / 16 % 4) == 0)
			create_character_animation(data, data->lib.image, 150 + 25000);
		else if (ret == 1 || ret == 3)
			create_character_animation(data, data->lib.image, 200 + 25000);
		else
			create_character_animation(data, data->lib.image, 250 + 25000);
	}
	else if (frame >= 448 && frame <= 512)
	{
		if ((ret = frame / 16 % 4) == 0)
			create_character_animation(data, data->lib.image, 100 + 100000);
		else if (ret == 1)
			create_character_animation(data, data->lib.image, 150 + 100000);
		else if (ret == 2)
			create_character_animation(data, data->lib.image, 200 + 100000);
		else
			create_character_animation(data, data->lib.image, 250 + 100000);
	}
	else if (frame >= 960)
	{
		if ((ret = frame / 16 % 4) == 0)
			create_character_animation(data, data->lib.image, 350 + 125000);
		else if (ret == 1 || ret == 3)
			create_character_animation(data, data->lib.image, 400 + 125000);
		else
			create_character_animation(data, data->lib.image, 450 + 125000);
	}
	else if ((ret = frame / 16 % 4) == 0)
		create_character_animation(data, data->lib.image, 150);
	else if (ret == 1 || ret == 3)
		create_character_animation(data, data->lib.image, 200);
	else
		create_character_animation(data, data->lib.image, 250);
	buttons[0] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER - (DEF_BUTTON_H + BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), LEAVING, "PLAY");
	buttons[1] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), SCORES, "SCORES");
	buttons[2] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER + (DEF_BUTTON_H + BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), SETTINGS, "SETTINGS");
	buttons[3] = button(point(WIDTH_CENTER - DEF_BUTTON_W,
		HEIGHT_CENTER + (2 * DEF_BUTTON_H + 2 * BUTTON_GAP_Y)),
		point(DEF_BUTTON_W * 2, DEF_BUTTON_H), LEAVING, "QUIT GAME");
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	put_buttons_on_img(data, buttons, 4);
	put_string_on_renderer(data, point(WIDTH / 2, HEIGHT / 8), label("DOOM", RED), data->lib.ptrfont[0]);
	put_buttons_names(data, buttons, BLACK, 4);
	check_inputs_menu(data, buttons, 4);
	SDL_RenderPresent(data->lib.renderer);
	frame++;
	total_frame++;
	if (frame == 1024)
		frame = 1;
	return (0);
}
