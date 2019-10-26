#include "doom.h"
#include "menus.h"

void		put_buttons_names(t_doom *data, t_button *btab, SDL_Color color, int nbuttons)
{
	while (nbuttons > 0)
	{
		put_string_on_renderer(data,
		point(btab[nbuttons - 1].pos.x + (btab[nbuttons - 1].dim.x / 2),
		btab[nbuttons - 1].pos.y + 27),
		label(btab[nbuttons - 1].title, nbuttons - 1 == data->button ? WHITE : color),
		data->lib.ptrfont[2]);
		--nbuttons;
	}
}
