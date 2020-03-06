/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mixer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 13:19:58 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/06 17:43:59 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MIXER_H
# define MIXER_H

# include <SDL_mixer.h>

# define NB_SOUND				11
# define NB_MUSIC				5

# define NB_CHANNELS			5

# define CHANNEL_MUSIC			0
# define CHANNEL_SOUNDS			1
# define CHANNEL_SOUNDS2		2
# define CHANNEL_FOOTSTEP		3
# define CHANNEL_FOOTSTEP2		4
# define CHANNEL_PLAYER_SOUNDS	5

typedef struct s_doom			t_doom;
typedef struct s_player			t_player;
typedef struct s_mixer			t_mixer;
typedef struct s_graphic_lib	t_graphic_lib;

struct							s_mixer
{
	int							rate;
	Uint16						format;
	int							channels;
	int							buffers;
	Mix_Chunk					*sounds[NB_SOUND];
	char						*sound_path[NB_SOUND];
	double						v_master;
	double						v_music;
	double						v_sound_effects;
};

int								init_mixer(t_doom *data);
int								play_sound(Mix_Chunk *sound);
int								loop_music(Mix_Chunk *sound, int id_sound);
int								loop_sound_effect(Mix_Chunk *sound,
	int id_sound);
void							game_sounds(t_doom *data, t_player *player);

int								change_volume(t_mixer *mix);
int								set_master_volume(t_mixer *mix, double a);
int								set_music_volume(t_mixer *mix, double a);
int								set_sound_effects_volume(t_mixer *mix,
	double a);

void							get_default_sounds(t_doom *data);

#endif
