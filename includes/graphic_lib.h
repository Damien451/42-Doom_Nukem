/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_lib.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:55:58 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/10 19:05:50 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GRAPHIC_LIB_H
# define GRAPHIC_LIB_H

/*
** ====-* INCLUDES *-====
*/

# include <SDL.h>
# include <SDL_ttf.h>
# include "mixer.h"

/*
** ====-* DEFINES *-====
*/

# define WIDTH					1920
# define HEIGHT					1080
# define SIZE_MAP				64
# define SIZE_TEXTURE			64
# define BLOCK_SIZE_EDITOR		16
# define TEXTURE_SIZE			83

# define NBR_TEXTURES_EDITOR	63
# define NBR_TEXTURES_BLOCKS	40
# define NBR_TEXTURES_OBJECTS	20
# define NBR_TEXTURES_ENEMY		21
# define NBR_TEXTURES_GUN		16
# define NBR_TEXTURES_MENU		6
# define NBR_FONTS				5
# define NB_IMG					2
# define ID_START_BLOCK			30
# define ID_FINISH_BLOCK		31

# define L_INPUT_EDITOR			1
# define R_INPUT_EDITOR			2

/*
** ====-* TYPEDEFS *-====
*/

typedef struct s_graphic_lib	t_graphic_lib;
typedef struct s_editor			t_editor;
typedef struct s_doom			t_doom;
typedef struct s_format			t_format;
typedef struct s_text			t_text;
typedef struct s_sprites		t_sprites;
typedef struct s_label			t_label;
typedef struct s_point			t_point;
typedef struct s_mixer			t_mixer;
typedef struct s_scoreboard		t_scoreboard;
typedef struct s_button			t_button;

/*
** ====-* STRUCTURES *-====
*/

struct							s_point
{
	int							x;
	int							y;
};

struct							s_label
{
	char						*str;
	SDL_Color					color;
};

struct							s_format
{
	int							height;
	int							width;
};

struct							s_text
{
	Uint32						format;
	int							access;
	int							w;
	int							h;
};

struct							s_editor
{
	unsigned int				texture[2][1920 * 1080];
	unsigned int				picked_texture;
	unsigned int				mouseinputs;
	int							mode;
	int							alpha;
	int							brush_size;
	int							pickmode;
	unsigned int				block1;
	unsigned int				block2;
	unsigned int				blocktoremove;
};

struct							s_sprites
{
	unsigned int				circle[128 * 128];
	unsigned int				ammo[15 * 32];
};

struct							s_graphic_lib
{
	unsigned int				character[500 * 350];
	unsigned int				bg_anim_menu[2][256 * 128];
	unsigned int				arrows_menu[2][64 * 64];
	unsigned int				bg_menu[2][1920 * 1080];
	unsigned int				start_bg[1920 * 1200];
	unsigned int				hud_texture[1920 * 1080];
	unsigned int				game_icon[400 * 400];
	unsigned int				enemy_textures[NBR_TEXTURES_ENEMY][64 * 64];
	unsigned int				gun_textures[NBR_TEXTURES_GUN][350 * 100];
	unsigned int				textures[NBR_TEXTURES_EDITOR][128 * 128];
	unsigned int				map_colors[NBR_TEXTURES_EDITOR];
	unsigned int				*image;
	unsigned int				cam_keys;
	char						texture_dic[NBR_TEXTURES_EDITOR][100];
	SDL_Texture					*texture;
	SDL_Window					*window;
	SDL_Renderer				*renderer;
	SDL_Surface					*surface;
	SDL_Event					event;
	TTF_Font					*ptrfont[NBR_FONTS];
	t_sprites					sprites;
	t_editor					editor;
	t_format					format;
	t_text						text;
};

/*
** ====-* PROTOTYPES *-====
*/

t_label							label(char *str, SDL_Color color);

int								load_textures(t_doom *data);

void							put_string_on_renderer(t_doom *data,
	t_point pos, t_label label, TTF_Font *font);

void							put_string_with_shadow(t_doom *data,
	t_point pos, t_label label, TTF_Font *font);

int								anim_main_menu(t_doom *data, int total_frame
	, int frame);

int								anim_weapon(int *typeanim);

void							init_anim_state_start(t_doom *data);

void							dictionnary_binary_tex(t_doom *data);

void							init_map_colors(t_graphic_lib *lib);

int								display_scores(t_doom *data,
	t_scoreboard *scores, int frame, int *curr_score);

void							display_arrows(t_doom *data, t_button *button);

#endif
