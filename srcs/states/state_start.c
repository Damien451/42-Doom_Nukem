#include "doom.h"
#include "graphic_lib.h"
#include "libft.h"
#include <time.h>

void	putpixel(unsigned int *image, int a, int b, int c)
{
	if (a + b * WIDTH >= 0 && a + b * WIDTH < WIDTH * HEIGHT)
		image[a + b * WIDTH] = c;
}

void	drawCircle(unsigned int *image, int xc, int yc, int x, int y, int color)
{
	rand();
    putpixel(image, xc+x, yc+y, color);
    putpixel(image, xc-x, yc+y, color);
    putpixel(image, xc+x, yc-y, color);
    putpixel(image, xc-x, yc-y, color);
    putpixel(image, xc+y, yc+x, color);
    putpixel(image, xc-y, yc+x, color);
    putpixel(image, xc+y, yc-x, color);
    putpixel(image, xc-y, yc-x, color);
}

void	circleBres(unsigned int *image, int xc, int yc, int r, int color)
{
    int x = 0, y = r;
    int d = 3 - 2 * r;
    drawCircle(image, xc, yc, x, y, color);
    while (y >= x)
    {
        x++;
        if (d > 0)
        {
            y--;
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;
        drawCircle(image, xc, yc, x, y, color);
    }
}

static void	print_autor(t_doom *data, unsigned int *image, int color)
{
	t_bubble			*tmp;

	tmp = data->bubble_list;
	while (tmp)
	{
		image[tmp->pos] = color;
		tmp = tmp->next;
	}
}

// 1174 445

static int	color_percent(int color1, int color2, int percent)
{
	double		c1;

	if (color1 < color2)
	{
		c1 = 1.0 - (color1 / (double)color2);
		c1 = color1 + ((c1 * percent / 100.0) * 255.0);
	}
	else
	{
		c1 = color1 / (double)color2;
		c1 = color1 - ((c1 * percent / 100.0) * 255.0);
	}
	return ((int)c1);
}

void	lightning_flash(unsigned int *image, int percent)
{
	unsigned int	ok[4];
	int				i;

	i = 0;
	while (i < WIDTH * HEIGHT)
	{
		ok[0] = (image[i] >> 24) % 256;
		ok[1] = (image[i] >> 16) % 256;
		ok[2] = (image[i] >> 8) % 256;
		ok[3] = image[i] % 256;
		ok[0] = color_percent(ok[0], 255, percent);
		ok[1] = color_percent(ok[1], 255, percent);
		ok[2] = color_percent(ok[2], 255, percent);
		ok[3] = color_percent(ok[3], 255, percent);
		image[i++] = (ok[1] << 16) + (ok[2] << 8) + ok[3];
	}
}

void	lightning(t_doom *data, unsigned int *image, int color)
{
	t_bubble *tmp;

	tmp = data->lightning_list;
	while (tmp)
	{
		image[tmp->pos] = color;
		tmp = tmp->next;
	}
}

static void	draw_on_texture(t_doom *data, unsigned int *image)
{
	int			i;
	int			g;
	static int	frame = 0;
	static int	type = 1;

	i = -1;
	while (++i < WIDTH * HEIGHT)
		image[i] = ((unsigned int*)data->lib.start_bg->pixels)[i];
	print_autor(data, image, frame << 16);
	i = 0;
	g = WIDTH * (HEIGHT - 1) - 1;
	srand(time(NULL));
	while (i < NB_BUBBLE)
	{
		circleBres(image, data->tab[i].pos % WIDTH, data->tab[i].pos / WIDTH, data->tab[i].size, data->tab[i].color);
		if (data->tab[i].pos % WIDTH > 1174)
		{
			if (data->tab[i].pos / WIDTH > 445)
				circleBres(image, data->tab[i].pos % WIDTH - data->tab[i].size / 4, data->tab[i].pos / WIDTH - data->tab[i].size / 4, data->tab[i].size / (i % 3 + 3), data->tab[i].color + (((data->tab[i].color >> 16) / 2) << 8) + ((data->tab[i].color >> 16) / 2));
			else
				circleBres(image, data->tab[i].pos % WIDTH - data->tab[i].size / 4, data->tab[i].pos / WIDTH + data->tab[i].size / 4, data->tab[i].size / (i % 3 + 3), data->tab[i].color + (((data->tab[i].color >> 16) / 2) << 8) + ((data->tab[i].color >> 16) / 2));
		}
		else
		{
			if (data->tab[i].pos / WIDTH > 445)
				circleBres(image, data->tab[i].pos % WIDTH + data->tab[i].size / 4, data->tab[i].pos / WIDTH - data->tab[i].size / 4, data->tab[i].size / (i % 3 + 3), data->tab[i].color + (((data->tab[i].color >> 16) / 2) << 8) + ((data->tab[i].color >> 16) / 2));
			else
				circleBres(image, data->tab[i].pos % WIDTH + data->tab[i].size / 4, data->tab[i].pos / WIDTH + data->tab[i].size / 4, data->tab[i].size / (i % 3 + 3), data->tab[i].color + (((data->tab[i].color >> 16) / 2) << 8) + ((data->tab[i].color >> 16) / 2));
		}
		data->tab[i].pos += (data->tab[i].speed * WIDTH);
		if (data->tab[i].pos >= WIDTH * HEIGHT)
		{
			srand(time(NULL) + rand());
			data->tab[i].pos = rand() % WIDTH;
			data->tab[i].speed = rand() % 10 + 1;
			data->tab[i].size = rand() % 10 + 4;
			data->tab[i].color = (rand() % 256) << 16;
		}
		i++;
	}
	if (type > 0 && frame >= 120 && frame <= 135)
	{
		lightning(data, image, ((frame + 75) << 16) | ((frame + 75) << 8));
		if (frame == 125)
			ft_memset(image, 255, WIDTH * HEIGHT * 4);
		else if (frame > 125 && frame <= 130)
			ft_memset(image, 255 - frame + 125, WIDTH * HEIGHT * 4);
		else if (frame > 120 && frame <= 125)
			ft_memset(image, 255 - frame + 125, WIDTH * HEIGHT * 4);
	}
	frame += type;
	if (frame == 255 || frame == 0)
		type *= -1;
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
