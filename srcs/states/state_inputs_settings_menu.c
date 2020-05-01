/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_inputs_settings_menu.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 15:20:52 by roduquen          #+#    #+#             */
/*   Updated: 2020/04/19 18:57:46 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include "menus.h"
#include "inputs.h"
#include <fcntl.h>
#include <unistd.h>

static int	save_inputs(t_doom *data)
{
	int			fd;

	if ((fd = open("./files/inputs", O_WRONLY | O_TRUNC | O_CREAT, 0777)) == -1)
		return (1);
	write(fd, (void*)data->tabinputs.keycode, 12 * 4);
	close(fd);
	switch_state(data, SETTINGS_INPUTS, SETTINGS);
	return (0);
}

static int	check_inputs_settings3(t_doom *data, int *first)
{
	if (data->lib.event.key.keysym.sym == SDLK_RETURN)
	{
		if (data->button == 8)
		{
			if (save_inputs(data) != 0)
				return (1);
		}
		else if (data->button == 13)
			get_default_inputs(data);
		else
		{
			switch_state(data, SETTINGS_INPUTS, GET_INPUT);
			*first = 0;
		}
	}
	else if (data->lib.event.key.keysym.sym == SDLK_ESCAPE)
	{
		*first = 0;
		switch_state(data, SETTINGS_INPUTS, SETTINGS);
	}
	return (0);
}

static int	check_inputs_settings2(t_doom *data, int nbuttons, int *first)
{
	if (data->lib.event.key.keysym.sym == SDLK_LEFT ||
		(unsigned int)data->lib.event.key.keysym.sym ==
		data->tabinputs.keycode[1])
	{
		if (data->button > 3)
			data->button = ((data->button - 4) < 4)
			? data->button - 4 : data->button - 5;
	}
	else if (data->lib.event.key.keysym.sym == SDLK_RIGHT ||
		(unsigned int)data->lib.event.key.keysym.sym ==
		data->tabinputs.keycode[3])
	{
		if (data->button > 3)
			data->button = (data->button + 5 <= nbuttons - 1)
			? data->button + 5 : data->button;
		else
			data->button += 4;
	}
	return (check_inputs_settings3(data, first));
}

static int	check_inputs_settings(t_doom *data, int nbuttons, int *first)
{
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN)
		{
			if (data->lib.event.key.keysym.sym == SDLK_UP ||
				(unsigned int)data->lib.event.key.keysym.sym ==
				data->tabinputs.keycode[0])
				data->button = data->button == 0
					? nbuttons - 1 : data->button - 1;
			else if (data->lib.event.key.keysym.sym == SDLK_DOWN ||
				(unsigned int)data->lib.event.key.keysym.sym ==
				data->tabinputs.keycode[2])
				data->button = (data->button == nbuttons - 1)
				? 0 : data->button + 1;
			else
				return (check_inputs_settings2(data, nbuttons, first));
		}
	}
	return (0);
}

int			state_inputs_settings_menu(t_doom *data)
{
	t_button	buttons[14];
	static int	first = 0;

	ft_memset(data->lib.image, 0, WIDTH * HEIGHT * 4);
	ft_memcpy(data->lib.image, data->lib.bg_menu[0],
		(WIDTH * HEIGHT) << 2);
	create_buttons_inputs(data, buttons, &first);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	put_buttons_on_img(data, buttons, 14);
	put_string_with_shadow(data, point(WIDTH / 2, HEIGHT / 6)
		, label("SETTINGS", (SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[1]);
	put_buttons_names(data, buttons, (SDL_Color){255, 0, 0, 0}, 14);
	if (check_inputs_settings(data, 14, &first) != 0)
		return (1);
	SDL_RenderPresent(data->lib.renderer);
	return (0);
}
