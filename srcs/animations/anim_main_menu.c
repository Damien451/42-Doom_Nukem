#include "doom.h"
#include "graphic_lib.h"

static int	create_charac_anim(t_doom *data, unsigned int *image, int move)
{
	int			i;
	int			j;

	i = 0;
	while (i < 200)
	{
		j = 0;
		while (j < 200)
		{
			if (((int*)data->lib.character->pixels)
				[(i / 4) * 500 + move + (j / 4)])
			{
				image[i * WIDTH + j + 525 * WIDTH + WIDTH / 16] =
				((int*)data->lib.character->pixels)[(i / 4)
				* 500 + move + (j / 4)];
			}
			j++;
		}
		i++;
	}
	return (0);
}

static void	choose_animation_part2(t_doom *data, int frame)
{
	int			ret;

	if (frame >= 960)
	{
		if ((ret = frame / 16 % 4) == 0)
			create_charac_anim(data, data->lib.image, 350 + 125000);
		else if (ret == 1 || ret == 3)
			create_charac_anim(data, data->lib.image, 400 + 125000);
		else
			create_charac_anim(data, data->lib.image, 450 + 125000);
	}
	else if ((ret = frame / 16 % 4) == 0)
		create_charac_anim(data, data->lib.image, 150);
	else if (ret == 1 || ret == 3)
		create_charac_anim(data, data->lib.image, 200);
	else
		create_charac_anim(data, data->lib.image, 250);
}

static void	choose_animation_part1(t_doom *data, int frame)
{
	int			ret;

	if (frame >= 160 && frame <= 256)
	{
		if ((ret = frame / 16 % 4) == 0)
			create_charac_anim(data, data->lib.image, 150 + 25000);
		else if (ret == 1 || ret == 3)
			create_charac_anim(data, data->lib.image, 200 + 25000);
		else
			create_charac_anim(data, data->lib.image, 250 + 25000);
	}
	else if (frame >= 448 && frame <= 512)
	{
		if ((ret = frame / 16 % 4) == 0)
			create_charac_anim(data, data->lib.image, 100 + 100000);
		else if (ret == 1)
			create_charac_anim(data, data->lib.image, 150 + 100000);
		else if (ret == 2)
			create_charac_anim(data, data->lib.image, 200 + 100000);
		else
			create_charac_anim(data, data->lib.image, 250 + 100000);
	}
	else
		choose_animation_part2(data, frame);
}

void		anim_main_menu(t_doom *data, int total_frame, int frame)
{
	int			i;
	int			j;

	i = 0;
	total_frame++;
	while (i < WIDTH)
	{
		j = 0;
		while (j < 128)
		{
			data->lib.image[i + j * WIDTH + 512 * WIDTH] =
			((int*)data->lib.menu_texture[((i + total_frame) /
			256) % 2]->pixels)[(i + total_frame) % 192 + j * 192];
			if (j < 64)
			{
				data->lib.image[i + j * (WIDTH - 2) + 640 * WIDTH] =
				((int*)data->lib.menu_texture[((i + total_frame) /
				256) % 2]->pixels)[(i + total_frame) * 2 % 192 +
				j * 192 * 2] + 18;
			}
			j++;
		}
		i++;
	}
	choose_animation_part1(data, frame);
}
