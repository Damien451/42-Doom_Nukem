#include "doom.h"

void	leave_state_game(t_vec3d *position)
{
	position->x = -1;
	position->y = -1;
	position->z = -1;
}
