#include "doom.h"
#include "menus.h"

t_label		label(char *str, SDL_Color color)
{
	t_label		newlabel;

	newlabel.str = str;
	newlabel.color = color;
	return (newlabel);
}

t_button	button(t_point pos, t_point dim, long state, char *title)
{
	t_button	newbutton;

	newbutton.pos = pos;
	newbutton.dim = dim;
	newbutton.state = state;
	newbutton.title = title;
	return (newbutton);
}

t_point		point(int width, int height)
{
	t_point		newpoint;

	newpoint.x = width;
	newpoint.y = height;
	return (newpoint);
}

void		switch_button(t_doom *data, long actual_button, long new_button)
{
	data->button &= ~actual_button;
	data->button |= new_button;
}

void		switch_state(t_doom *data, long actual_state, long new_state)
{
	if (new_state != GET_INPUT && actual_state != GET_INPUT)
		data->button = 0;
	if (new_state == LEAVING)
	{
		data->running = 0;
		return ;
	}
	data->state = new_state;
	if ((new_state == PLAYING || new_state == TEST_MODE)
		&& actual_state != PAUSE && actual_state != DEATH)
	{
		free_octree(data->octree);
		create_octree(data);
		init_game(data, &data->player);
	}
}
