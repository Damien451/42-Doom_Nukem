#include "doom.h"

int		init_mixer(t_mixer *mixer)
{
    if (SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        return 1;
    }
    mixer->rate = 44100;
    mixer->format = AUDIO_S16SYS;
    mixer->channels = 2;
    mixer->buffers = 4096;
	if (Mix_OpenAudio(mixer->rate, mixer->format, mixer->channels, mixer->buffers) != 0)
	{
		printf("Unable to initialize audio: %s\n", Mix_GetError());
		return(1);
	}
	return (0);
}

int		load_sound(char *path, Mix_Chunk **sound)
{
	*sound = Mix_LoadWAV(path);
	printf("%s\n", path);
	if (*sound == NULL)
	{
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

	channel = Mix_PlayChannel(-1, sound, -1);
	if (channel == -1)
	{
		printf("Unable to play WAV file: %s\n", Mix_GetError());
		return (1);
	}
	return (0);
}
