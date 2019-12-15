/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   menus.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 13:19:42 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/15 13:26:08 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MENUS_H
# define MENUS_H

/*
** ====-* INCLUDES *-====
*/

# include "graphic_lib.h"

/*
** ====-* DEFINES *-====
*/

# define DEF_BUTTON_W				274
# define DEF_BUTTON_H				90
# define WIDTH_CENTER				960
# define HEIGHT_CENTER				540
# define BUTTON_GAP_X				160
# define BUTTON_GAP_Y				30

# define BAR_WIDTH					768
# define BAR_HEIGHT					18
# define BAR_HEIGHT_START			392
# define BAR_WIDTH_START			576
# define BAR_GAP					154

# define HEALTH_BAR_HEIGHT_START	196
# define HEALTH_BAR_WIDTH_START		78
# define HEALTH_BAR_WIDTH			36
# define HEALTH_BAR_HEIGHT			179

# define MINIMAP_WIDTH_START		1657
# define MINIMAP_HEIGHT_START		74

# define SET_BUTTON_W				384
# define SET_BUTTON_H				80

# define NB_BUBBLE					125

/*
** ====-* TYPEDEFS *-====
*/

typedef struct s_doom				t_doom;
typedef struct s_point				t_point;
typedef struct s_player				t_player;
typedef struct s_button				t_button;
typedef struct s_img				t_img;
typedef struct s_start				t_start;

/*
** ====-* STRUCTURES *-====
*/

struct								s_start
{
	int								pos;
	int								speed;
	int								size;
	int								color;
};

struct								s_point
{
	int								x;
	int								y;
};

struct								s_button
{
	t_point							pos;
	t_point							dim;
	char							*title;
	long							state;
	long							select;
};

struct								s_img
{
	int								width;
	int								height;
	__uint32_t						*pixels;
};

/*
** ====-* PROTOTYPES *-====
*/

t_point								add_points(t_point a, t_point b);

void								create_buttons_inputs(t_doom *data
		, t_button *btab);

int									draw_rectangle(t_graphic_lib *lib
		, t_point position, t_point dimensions, int color);

void								minimap(char map[64][64][64]
		, t_player *player, t_graphic_lib *lib);

void								mouse_sound_commands(t_doom *data
		, int tab[3]);

int									put_buttons_on_img(t_doom *data
		, t_button *btab, int nbuttons);

void								put_buttons_names(t_doom *data
		, t_button *btab, SDL_Color color, int nbuttons);

void								put_sound_bars(t_doom *data, int *tab);

t_button							button(t_point pos, t_point dim, long state
		, char *title);

t_point								point(int width, int height);

void								start_drawing_circle(t_doom *data, int i
	, unsigned int *image);

int									create_flame(t_doom *data
		, unsigned int *image);

void								put_health_bar(t_doom *data);

#endif
