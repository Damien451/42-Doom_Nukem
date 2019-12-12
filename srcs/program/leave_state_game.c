#include "doom.h"

void	leave_state_game(t_player *player)
{
	player->camera.origin.x = -1;
	player->camera.origin.y = -1;
	player->camera.origin.z = -1;
}
