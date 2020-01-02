/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphic_lib.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 11:55:58 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/02 17:13:24 by dacuvill         ###   ########.fr       */
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

# define NBR_TEXTURES_BLOCKS	41
# define NBR_TEXTURES_MENU		5
# define NBR_FONTS				6
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
typedef struct s_label			t_label;
typedef struct s_point			t_point;
typedef struct s_mixer			t_mixer;

/*
** ====-* STRUCTURES *-====
*/

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
	SDL_Surface					*texture[2];
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

struct							s_graphic_lib
{
	SDL_Surface					*character;
	SDL_Surface					*menu_texture[NBR_TEXTURES_MENU];
	SDL_Surface					*skybox[6];
	SDL_Texture					*skybox_t[6];
	SDL_Surface					*textures[NBR_TEXTURES_BLOCKS];
	char						texture_dic[NBR_TEXTURES_BLOCKS][100];
	SDL_Surface					*hud_texture;
	SDL_Texture					*texture;
	SDL_Window					*window;
	SDL_Renderer				*renderer;
	SDL_Surface					*start_bg;
	SDL_Surface					*surface;
	SDL_Surface					*surfaces[NB_IMG];
	char						*texture_path[NB_IMG];
	SDL_Event					event;
	t_editor					editor;
	t_format					format;
	t_text						text;
	TTF_Font					*ptrfont[NBR_FONTS];
	unsigned int				*image;
	unsigned int				cam_keys;
	unsigned int				*textures_block[NBR_TEXTURES_BLOCKS];
};

/*
** ====-* PROTOTYPES *-====
*/

t_label							label(char *str, SDL_Color color);

void							load_textures(t_doom *data);

void							put_string_on_renderer(t_doom *data, t_point pos
	, t_label label, TTF_Font *font);

int								anim_main_menu(t_doom *data, int total_frame
	, int frame);

void							dictionnary_binary_tex(t_doom *data);

#endif
