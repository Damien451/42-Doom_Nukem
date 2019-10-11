
#include "menus.h"

t_point		add_points(t_point a, t_point b)
{
	a.x += b.x;
	a.y += b.y;
	return (a);
}
