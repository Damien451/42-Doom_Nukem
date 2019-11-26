#include "doom.h"
#include "mixer.h"

void		get_default_sounds(t_doom *data)
{
	data->mix->v_master = 0.8;
	data->mix->v_music = 0.8;
	data->mix->v_sound_effects = 0.8;
}
