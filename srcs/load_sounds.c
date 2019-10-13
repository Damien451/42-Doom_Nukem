#include "doom.h"

static void		add_sound_path(t_doom *data)
{
	data->lib.sound_path[0] = "ressources/sound/file_exemple_WAC_10MG.wav";
	data->lib.sound_path[1] = "ressources/sound/file_exemple_WAC_1MG.wav";
}

int				load_sounds(t_doom *data)
{
	int			i;

	i = -1;
	add_sound_path(data);
	while (++i < NB_IMG)
	{
		if (load_sound(data->lib.sound_path[i], &(data->lib.sounds[i])))
			return (1);
	}
	return (0);
}