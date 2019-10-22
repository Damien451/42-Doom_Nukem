#include "doom.h"
#include "player.h"
#include <SDL.h>
#include "graphic_lib.h"
#include "libft.h"
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

int			max_absolute_between_three(double a, double b, double c)
{
	a = a < 0 ? -a : a;
	b = b < 0 ? -b : b;
	c = c < 0 ? -c : c;
	if (a >= c && a >= b)
		return (1);
	else if (b >= a && b >= c)
		return (2);
	return (3);
}

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
/*	if (data->lib.cam_keys & WATER)
		printf("water");
	printf("\n");*/
	ft_memcpy(data->lib.image, data->lib.hud_texture->pixels, (WIDTH * HEIGHT) << 2);
	raytracing(data);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	//skybox(data);
	SDL_RenderPresent(data->lib.renderer);
	return (0);
}
