/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mixer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 13:19:58 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/05 19:36:12 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MIXER_H
# define MIXER_H

# include <SDL_mixer.h>

# define NB_SOUND				4

typedef struct s_doom		t_doom;

typedef struct				s_mixer
{
	int						rate;
	Uint16					format;
	int						channels;
	int						buffers;
	Mix_Chunk				*sounds[NB_SOUND];
	char					*sound_path[NB_SOUND];
	double					v_master;
	double					v_music;
	double					v_sound_effects;
}							t_mixer;

int							init_mixer(t_doom *data);
int							load_sound(char *path, Mix_Chunk **sound);
int							play_sound(Mix_Chunk *sound);
int							loop_sound(Mix_Chunk *sound);

int							change_volume(t_mixer *mix);
int							set_master_volume(t_mixer *mix, double a);
int							set_music_volume(t_mixer *mix, double a);
int							set_sound_effects_volume(t_mixer *mix, double a);

void						get_default_sounds(t_doom *data);

#endif
