#include "doom.h"

static void		add_sound_path(t_doom *data)
{
	data->lib.mix->sound_path[0] = "ressources/sound/file_example_WAV_10MG.wav";
	data->lib.mix->sound_path[1] = "ressources/sound/file_example_WAV_1MG.wav";
	data->lib.mix->sound_path[2] = "ressources/sound/0124.wav";
	data->lib.mix->sound_path[3] = "ressources/sound/Storm_exclamation.wav";
}

int				load_sounds(t_doom *data)
{
	int			i;

	i = -1;
	add_sound_path(data);
	while (++i < NB_IMG)
	{
		if (load_sound(data->lib.mix->sound_path[i], &(data->lib.mix->sounds[i])))
			return (1);
	}
	return (0);
}