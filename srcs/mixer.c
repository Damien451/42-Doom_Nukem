#include "doom.h"

int		init_mixer(t_doom *data)
{
    if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    if (!(data->lib.mix = malloc(sizeof(t_mixer))))
    	return (1);
    data->lib.mix->rate = 44100;
    data->lib.mix->format = AUDIO_S16SYS;
    data->lib.mix->channels = 2;
    data->lib.mix->buffers = 4096;
    data->lib.mix->v_master = 1;
    data->lib.mix->v_sound_effects = 1;
    data->lib.mix->v_music = 1;
	if (Mix_OpenAudio(data->lib.mix->rate, data->lib.mix->format, data->lib.mix->channels, data->lib.mix->buffers) != 0)
	{
		printf("Unable to initialize audio: %s\n", Mix_GetError());
		return(1);
	}
	if (load_sounds(data))
		return (1);
	return (0);
}

int		load_sound(char *path, Mix_Chunk **sound)
{
	*sound = Mix_LoadWAV(path);
	if (*sound == NULL)
	{
		printf("---%s---\n", path);
		printf("Unable to load WAV file: %s\n", Mix_GetError());
		return (1);
	}
	return (0);
}

int		play_sound(Mix_Chunk *sound)
{
	int channel;

	channel = Mix_PlayChannel(-1, sound, 0);
	if (channel == -1)
	{
		printf("Unable to play WAV file: %s\n", Mix_GetError());
		return (1);
	}
	return (0);
}

int		loop_sound(Mix_Chunk *sound)
{
	int channel;

	Mix_FadeOutChannel(1, 300);
	channel = Mix_FadeInChannel(1, sound, -1, 300);
	if (channel == -1)
	{
		printf("Unable to play WAV file: %s\n", Mix_GetError());
		return (1);
	}
	return (0);
}

int		change_volume(t_mixer *mix)
{
	if ((Mix_Volume(-1, (int)(mix->v_master * mix->v_sound_effects * 128)) == -1) ||
	(Mix_Volume(1, (int)(mix->v_master * mix->v_music * 128)) == -1))
		return (-1);
	return (0);
}

int		set_master_volume(t_graphic_lib *lib, double a)
{
	if (a < 0 || a > 1)
		return (-1);
	lib->mix->v_master = a;
	change_volume(lib->mix);
	return (0);
}

int		set_music_volume(t_graphic_lib *lib, double a)
{
	if (a < 0 || a > 1)
		return (-1);
	lib->mix->v_music = a;
	change_volume(lib->mix);
	return (0);
}

int		set_sound_effects_volume(t_graphic_lib *lib, double a)
{
	if (a < 0 || a > 1)
		return (-1);
	lib->mix->v_sound_effects = a;
	change_volume(lib->mix);
	return (0);
}

