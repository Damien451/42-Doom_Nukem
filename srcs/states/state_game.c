#include "doom.h"
#include "player.h"
#include <SDL.h>
#include "graphic_lib.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
/*
x = 0  z = 1
x = 1  z = 0
x = 0  z = -1
z = -1 z = 0

il y a 512 pixels entre 2 etats.

if (x == 0 && z == 1)
{
	start = 0;
	texture = NORTH;
}
else if (x == 1 && z == 0)
{
	start = 0;
	texture = EAST;
}
else if (x == 0 && z == -1)
{
	start = 0;
	texture = SOUTH;
}
else if (x == -1 && z == 0)
{
	start = 0;
	texture = WEST;
}

M_PI / 6 = 30 degres;
*/

/*void		skybox(t_doom *data)
{
	int			ret;
	t_vec3d		vec;

	vec = data->player.camera.direction;
	ret = max_absolute_between_three(vec.x, vec.y, vec.z);
	if (ret == 1)
	{
		if (vec.x > 0)
	}
}
*/

void		skybox(t_doom *data)
{
	int			i;
	int			j;
	unsigned char	*test;
	int			w;
	int			h;
	unsigned int			format;
	unsigned char			tab[4];
	static unsigned int		tabl[512 * 512];
	static int				ok = 0;
	int						fd;

	tab[0] = 0;
/*	if (!ok)
	{
	fd = open("test.binary", O_RDONLY);
	read(fd, tabl, 512*512*4);
	ok++;
	}*/
	SDL_QueryTexture(data->lib.skybox_t[0], &format, NULL, &w, &h);
	printf("format = %u, w = %d, h = %d\n", format, w, h);
	printf("test   = %u\n", SDL_PIXELFORMAT_ARGB8888);
	SDL_LockTexture(data->lib.skybox_t[0], NULL, (void**)&test, &i);
	i = 0;
	while (i < 512)
	{
		j = 0;
		while (j < 512)
		{
			tab[1] = ((unsigned char*)data->lib.skybox[5]->pixels)[i * data->lib.skybox[5]->pitch + j * 3 + 1];
			tab[2] = ((unsigned char*)data->lib.skybox[5]->pixels)[i * data->lib.skybox[5]->pitch + j * 3 + 2];
			tab[3] = ((unsigned char*)data->lib.skybox[5]->pixels)[i * data->lib.skybox[5]->pitch + j * 3];
			tabl[i * 512 + j] = *((unsigned int *)&tab);
//			data->lib.image[i * WIDTH + j] = *((unsigned int*)&tab);
			data->lib.image[i * WIDTH + j] = tabl[i * 512 + j];
			j++;
		}
		i++;
	}
	SDL_UnlockTexture(data->lib.skybox_t[0]);
	if (!ok)
	{
		i = open("test6.binary", O_TRUNC | O_WRONLY | O_CREAT, 0777);
		write(i, tabl, 512*512*4);
		ok++;
	}
}

int			state_game(t_doom *data)
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN && data->lib.event.key.keysym.sym == SDLK_ESCAPE)
				switch_state(data, PLAYING, MAIN_MENU);
		else if (data->lib.event.type == SDL_MOUSEMOTION)
			camera_mouse_motion(&data->player.camera
				, &data->lib.event.motion.xrel, &data->lib.event.motion.yrel
				, &data->player.sensitivity);
		camera_press_key(&data->lib.event, data);
	}
	camera_event_translate(data);
//	printf("Direction vector = (%.2f|%.2f|%.2f)\n    position = (%.2f|%.2f|%.2f)\n", data->player.camera.direction.x, data->player.camera.direction.y, data->player.camera.direction.z, data->player.camera.origin.x, data->player.camera.origin.y, data->player.camera.origin.z);
//	if (data->lib.cam_keys & WATER)
//		printf("water");
//	printf("\n");
	ft_memcpy(data->lib.image, data->lib.hud_texture->pixels, (WIDTH * HEIGHT) << 2);
	raytracing(data);
//	skybox(data);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	SDL_RenderPresent(data->lib.renderer);
	return (0);
}
