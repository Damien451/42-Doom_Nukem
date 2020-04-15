/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mixer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:37:53 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/26 00:14:50 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		init_mixer(t_doom *data)
{
	data->mix.rate = 44100;
	get_default_sounds(data);
	data->mix.format = AUDIO_S16SYS;
	data->mix.channels = NB_CHANNELS;
	data->mix.buffers = 4096;
	if (Mix_OpenAudio(data->mix.rate, data->mix.format,
		2, data->mix.buffers) != 0)
	{
		printf("Unable to initialize audio: %s\n", Mix_GetError());
		return (1);
	}
	if (load_sounds(data))
		return (1);
	change_volume(&data->mix);
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

int		loop_music(Mix_Chunk *sound, int id_music)
{
	static int	id_current_music = -1;
	int			channel;

	if (id_current_music != id_music)
	{
		Mix_FadeOutChannel(CHANNEL_MUSIC, 300);
		channel = Mix_FadeInChannel(CHANNEL_MUSIC, sound, -1, 300);
		if (channel == -1)
		{
			printf("Unable to play WAV file: %s\n", Mix_GetError());
			return (1);
		}
		id_current_music = id_music;
	}
	return (0);
}

int		loop_sound_effect(Mix_Chunk *sound, int id_sound)
{
	static int	id_current_sound = -1;
	int			id_channel;
	int			channel;

	id_channel = (!Mix_Playing(CHANNEL_SOUNDS) ?
		CHANNEL_SOUNDS : CHANNEL_SOUNDS2);
	if (id_current_sound != id_sound)
	{
		Mix_FadeOutChannel(id_channel, 300);
		channel = Mix_FadeInChannel(id_channel, sound, -1, 300);
		if (channel == -1)
		{
			printf("Unable to play WAV file: %s\n", Mix_GetError());
			return (1);
		}
		id_current_sound = id_sound;
	}
	return (0);
}
