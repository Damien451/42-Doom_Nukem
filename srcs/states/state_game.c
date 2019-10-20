#include "doom.h"
#include "player.h"
#include <SDL.h>
#include "graphic_lib.h"
#include "libft.h"

int			state_game(t_doom *data)
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN && data->lib.event.key.keysym.sym == SDLK_ESCAPE)
				switch_state(data, PLAYING, MAIN_MENU);
		else if (data->lib.event.type == SDL_MOUSEMOTION)
			camera_mouse_motion(&data->player.camera, &data->lib.event.motion.xrel, &data->lib.event.motion.yrel, &data->player.sensitivity);
		camera_press_key(&data->lib.event, data);
	}
	camera_event_translate(data);
	printf("Direction vector = (%.2f|%.2f|%.2f)\n    position = (%.2f|%.2f|%.2f)\n", data->player.camera.direction.x, data->player.camera.direction.y, data->player.camera.direction.z, data->player.camera.origin.x, data->player.camera.origin.y, data->player.camera.origin.z);
	if (data->lib.cam_keys & WATER)
		printf("water\n");
	else
		printf("\n");
	ft_memcpy(data->lib.image, data->lib.hud_texture->pixels, (WIDTH * HEIGHT) << 2);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	SDL_RenderPresent(data->lib.renderer);
	return (0);
}
