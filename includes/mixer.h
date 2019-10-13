#ifndef MIXER_H
# define MIXER_H

#include <SDL_mixer.h>

typedef struct		s_mixer
{
	int				rate;
	Uint16			format;
	int				channels;
	int				buffers;
}					t_mixer;

int		init_mixer(t_mixer *mixer);
int		load_sound(char *path, Mix_Chunk **sound);
int		play_sound(Mix_Chunk *sound);
int		loop_sound(Mix_Chunk *sound);

#endif