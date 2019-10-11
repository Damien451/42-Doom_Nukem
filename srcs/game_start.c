#include "doom.h"

int		game_start(t_doom *data)
{
	if (data->lib.event.type == SDL_KEYDOWN)
		switch_state(data, START, MAIN_MENU);
	return (0);
}
