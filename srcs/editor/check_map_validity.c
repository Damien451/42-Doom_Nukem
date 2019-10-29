
#include "doom.h"
#include "graphic_lib.h"

static inline void	checks(char block, int *start, int *finish)
{
	if ((int)block == ID_START_BLOCK + 1)
		(*start)++;
	else if ((int)block == ID_FINISH_BLOCK + 1)
		(*finish)++;
}

int					check_map_validity(t_doom *data)
{
	int			i;
	int			step;
	int			j;
	int			start;
	int			finish;

	i = -1;
	start = 0;
	finish = 0;
	while (++i < SIZE_MAP)
	{
		step = -1;
		while (++step < SIZE_MAP)
		{
			j = -1;
			while (++j < SIZE_MAP)
				checks(data->map_to_save[i][step][j], &start, &finish);
		}
	}
	return (start == 1 && finish == 1 ? 0 : 1);
}
