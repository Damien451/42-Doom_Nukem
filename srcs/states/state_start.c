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

static void	print_autor(t_doom *data, unsigned int *image)
{
	static unsigned int	actual = 0;
	static unsigned int	type = 1;
	t_bubble			*tmp;

	tmp = data->bubble_list;
	while (tmp)
	{
		image[tmp->pos] = actual << 16;
		tmp = tmp->next;
	}
	actual += type;
	if (actual < 0 || actual > 150)
	{
		actual -= type;
		type *= -1;
	}
}

static void	draw_on_texture(t_doom *data, unsigned int *image)
{
	int			i;
	int			g;

	i = 0;
	while (i < WIDTH * HEIGHT)
		image[i++] = 0x3E;
//	ft_memset(image, 0, WIDTH * HEIGHT * 4);
	print_autor(data, image);
	i = 0;
	g = WIDTH * (HEIGHT - 1) - 1;
	srand(time(NULL));
	while (i < NB_BUBBLE)
	{
		circleBres(image, data->tab[i].pos % WIDTH, data->tab[i].pos / WIDTH, data->tab[i].size, data->tab[i].color);
		data->tab[i].pos -= (data->tab[i].speed * WIDTH);
		if (data->tab[i].pos < 0)
		{
			srand(time(NULL) + rand());
			data->tab[i].pos = rand() % WIDTH + g;
			data->tab[i].speed = rand() % 10 + 1;
			data->tab[i].size = rand() % 10 + 4;
			data->tab[i].color = (rand() % 256) << 16;
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
