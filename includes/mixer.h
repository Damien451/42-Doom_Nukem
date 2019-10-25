#ifndef MIXER_H
# define MIXER_H

#include <SDL_mixer.h>

# define NB_SOUND				5


typedef struct s_doom		t_doom;

typedef struct		s_mixer
{
	int				rate;
	Uint16			format;
	int				channels;
	int				buffers;
	Mix_Chunk 					*sounds[NB_SOUND];
	char						*sound_path[NB_SOUND];
	double						v_master;
	double						v_music;
	double						v_sound_effects;
}					t_mixer;

int		init_mixer(t_doom *data);
int		load_sound(char *path, Mix_Chunk **sound);
int		play_sound(Mix_Chunk *sound);
int		loop_sound(Mix_Chunk *sound);

#endif