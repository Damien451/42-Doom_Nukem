#include "doom.h"
#include "libft.h"
#include "inputs.h"

static inline void	mouse_editor_commands3(t_doom *data, int *step)
{
	if (data->lib.event.button.x >= 1283 && data->lib.event.button.y >= 711
		&& data->lib.event.button.x <= 1318 && data->lib.event.button.y <= 734)
		data->lib.editor.brush_size = 1;
	else if (data->lib.event.button.x >= 1395 && data->lib.event.button.y >= 711
		&& data->lib.event.button.x <= 1443 && data->lib.event.button.y <= 734)
		data->lib.editor.brush_size = 2;
	else if (data->lib.event.button.x >= 1508 && data->lib.event.button.y >= 711
		&& data->lib.event.button.x <= 1554 && data->lib.event.button.y <= 734)
		data->lib.editor.brush_size = 3;
	else if (data->lib.event.button.x >= 1616 && data->lib.event.button.y >= 711
		&& data->lib.event.button.x <= 1668 && data->lib.event.button.y <= 734)
		data->lib.editor.brush_size = 4;
	else if (data->lib.event.button.x >= 1730 && data->lib.event.button.y >= 711
		&& data->lib.event.button.x <= 1775 && data->lib.event.button.y <= 734)
		data->lib.editor.brush_size = 5;
	else if (data->lib.event.button.x >= 1387 && data->lib.event.button.y >= 575
		&& data->lib.event.button.x <= 1422 && data->lib.event.button.y <= 607)
		replace_blocks(data);
	else if (data->lib.event.button.x >= 1277 && data->lib.event.button.y >= 640
		&& data->lib.event.button.x <= 1313 && data->lib.event.button.y <= 671)
		remove_type_block(data);
	else if (data->lib.event.button.x >= 1541 && data->lib.event.button.y >= 970
		&& data->lib.event.button.x <= 1573 && data->lib.event.button.y <= 1005
		&& *step > 0)
		copy_step(data, *step);
}

static inline void	mouse_editor_commands2(t_doom *data, int *step)
{
	if (data->lib.event.button.x >= 1189 && data->lib.event.button.y >= 904
		&& data->lib.event.button.x <= 1226 && data->lib.event.button.y <= 939)
		fill_step(data, *step);
	else if (data->lib.event.button.x >= 1350 && data->lib.event.button.y >= 833
		&& data->lib.event.button.x <= 1390 && data->lib.event.button.y <= 869)
		*step = (*step < SIZE_MAP - 1 ? *step + 1 : *step);
	else if (data->lib.event.button.x >= 1408 && data->lib.event.button.y >= 833
		&& data->lib.event.button.x <= 1448 && data->lib.event.button.y <= 869)
		*step = (*step > 0 ? *step - 1 : *step);
	else if (data->lib.event.button.x >= 1602 && data->lib.event.button.y >= 900
		&& data->lib.event.button.x <= 1647 && data->lib.event.button.y <= 944)
		reset_step(data, *step);
	else if (data->lib.event.button.x >= 1234 && data->lib.event.button.y >= 581
		&& data->lib.event.button.x <= 1254 && data->lib.event.button.y <= 601)
		data->lib.editor.pickmode = 1;
	else if (data->lib.event.button.x >= 1341 && data->lib.event.button.y >= 581
		&& data->lib.event.button.x <= 1361 && data->lib.event.button.y <= 601)
		data->lib.editor.pickmode = 2;
	else if (data->lib.event.button.x >= 1223 && data->lib.event.button.y >= 647
		&& data->lib.event.button.x <= 1243 && data->lib.event.button.y <= 667)
		data->lib.editor.pickmode = 3;
	mouse_editor_commands3(data, step);
}

void				mouse_editor_commands(t_doom *data, int *ok,
	int *step, int button)
{
	//printf("x = %d, y = %d\n", data->lib.event.button.x, data->lib.event.button.y);
	if (data->lib.event.button.x >= 1052 && data->lib.event.button.y >= 16
		&& data->lib.event.button.x <= 1903 && data->lib.event.button.y <= 350)
		pick_texture(data, data->lib.event.button.x, data->lib.event.button.y);
	else if (data->lib.event.button.x >= 15 && data->lib.event.button.y >= 15
		&& data->lib.event.button.x <= 1030 && data->lib.event.button.y <= 1030
		&& button == SDL_BUTTON_LEFT)
	{
		*ok = 1;
		draw_block(data, data->lib.event.button.x,
			data->lib.event.button.y, *step);
	}
	else if (data->lib.event.button.x >= 15 && data->lib.event.button.y >= 15
		&& data->lib.event.button.x <= 1030 && data->lib.event.button.y <= 1030
		&& button == SDL_BUTTON_RIGHT)
	{
		*ok = 1;
		erase_block(data, data->lib.event.button.x,
			data->lib.event.button.y, *step);
	}
	if (data->lib.editor.mode == 0)
		mouse_editor_commands2(data, step);
}
