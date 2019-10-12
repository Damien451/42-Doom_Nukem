#include "doom.h"
#include "graphic_lib.h"
#include "libft.h"
#include <time.h>

static void	draw_on_texture(t_doom *data, unsigned int *image)
{
	int			i;
	int			g;
	int			test;

	ft_memset(image, 0, WIDTH * HEIGHT * 4);
	i = 0;
	g = WIDTH * (HEIGHT - 1) - 1;
	srand(time(NULL));
	while (i < 50)
	{
		test = 0;
		while (test < data->tab[i].size)
		{
			if (data->tab[i].pos + test < WIDTH * HEIGHT)
				image[data->tab[i].pos + test] = 0xFFFFFF;
			if (data->tab[i].pos - test >= 0)
				image[data->tab[i].pos - test] = 0xFFFFFF;
			if (data->tab[i].pos + (test * WIDTH) < WIDTH * HEIGHT)
				image[data->tab[i].pos + (test * WIDTH)] = 0xFFFFFF;
			if (data->tab[i].pos - (test * WIDTH) >= 0)
				image[data->tab[i].pos - (test * WIDTH)] = 0xFFFFFF;
			test++;
		}
		data->tab[i].pos -= (data->tab[i].speed * WIDTH);
		if (data->tab[i].pos < 0)
		{
			srand(time(NULL) + rand());
			data->tab[i].pos = rand() % WIDTH + g;
			data->tab[i].speed = rand() % 10 + 1;
			data->tab[i].size = rand() % 10 + 4;
		}
		i++;
	}
}

static void	create_start_renderer(t_doom *data)
{
	int			test;

	if (!SDL_LockTexture(data->lib.texture, NULL, (void**)&data->lib.image, &test))
	{
		SDL_UnlockTexture(data->lib.texture);
		draw_on_texture(data, data->lib.image);
		SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
		SDL_RenderPresent(data->lib.renderer);
	}
}

int			state_start(t_doom *data)
{
	while (SDL_PollEvent(&data->lib.event))
		if (data->lib.event.type == SDL_KEYDOWN)
			switch_state(data, START, MAIN_MENU);
	create_start_renderer(data);
	return (0);
}
