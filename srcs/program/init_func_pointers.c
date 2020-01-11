/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_func_pointers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 14:42:20 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/11 17:58:15 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

static void		init_func_pointer_game_state(t_doom *data)
{
	data->state_f[START] = &state_start;
	data->state_f[MAIN_MENU] = &state_main_menu;
	data->state_f[EDITOR_MENU] = &state_editor_menu;
	data->state_f[PLAY_MENU] = &state_play_menu;
	data->state_f[PLAY_EDIT_MAP] = &state_play_edit_map;
	data->state_f[EDITOR] = &state_editor;
	data->state_f[GET_MAP_NAME] = &state_get_map_name;
	data->state_f[DELETE_MAP] = &state_delete_map;
	data->state_f[SCORES] = &state_scoreboard;
	data->state_f[SETTINGS] = &state_settings_menu;
	data->state_f[SETTINGS_INPUTS] = &state_inputs_settings_menu;
	data->state_f[SETTINGS_SOUND] = &state_sound_settings;
	data->state_f[TEST_MODE] = &state_test_mode;
	data->state_f[GET_INPUT] = &state_get_input;
	data->state_f[PAUSE] = &state_pause;
	data->state_f[PLAYING] = &state_game;
	data->state_f[SETTINGS_SOUND] = &state_sound_settings;
	data->state_f[DEATH] = &state_death;
}

void			init_func_pointer(t_doom *data)
{
	data->check_intersect[0] = &check_x_intersect_pos;
	data->check_intersect[1] = &check_y_intersect_pos;
	data->check_intersect[2] = &check_z_intersect_pos;
	data->check_intersect[3] = &check_x_intersect_neg;
	data->check_intersect[4] = &check_y_intersect_neg;
	data->check_intersect[5] = &check_z_intersect_neg;
	data->add_texture[X_MIN] = &add_x_neg;
	data->add_texture[X_MAX] = &add_x_pos;
	data->add_texture[Y_MIN] = &add_y_neg;
	data->add_texture[Y_MAX] = &add_y_pos;
	data->add_texture[Z_MIN] = &add_z_neg;
	data->add_texture[Z_MAX] = &add_z_pos;
	data->check_light_view[X_MIN] = &check_light_view_x_neg;
	data->check_light_view[X_MAX] = &check_light_view_x_pos;
	data->check_light_view[Y_MIN] = &check_light_view_y_neg;
	data->check_light_view[Y_MAX] = &check_light_view_y_pos;
	data->check_light_view[Z_MIN] = &check_light_view_z_neg;
	data->check_light_view[Z_MAX] = &check_light_view_z_pos;
	init_func_pointer_game_state(data);
}
