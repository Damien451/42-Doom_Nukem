#ifndef DOOM_H
# define DOOM_H

/*
** ====-* INCLUDES *-====
*/

# include "graphic_lib.h"
# include "inputs.h"
# include "menus.h"
# include "player.h"
# include "vec3.h"

/*
** ====-* DEFINES *-====
*/

# define EPSILON	1e-20
# define FOV		(60.0 * M_PI / 180.0)
# define POV		(25.67 * M_PI / 180.0)

# define RUNNING	(1l << 62)
# define START		(1l)
# define PLAYING	(1l << 1)
# define PAUSE		(1l << 2)
# define MAIN_MENU	(1l << 3)
# define PLAY_MENU	(1l << 4)
# define EDITOR		(1l << 5)
# define SCORES		(1l << 6)
# define SETTINGS	(1l << 7)
# define GET_INPUT	(1l << 8)
# define LEAVING	(1l << 9)

/*
** ====-* TYPEDEFS *-====
*/

typedef struct s_doom			t_doom;
typedef struct s_graphic_lib	t_graphic_lib;
typedef struct s_bubble			t_bubble;
typedef struct s_octree			t_octree;

/*
** ====-* STRUCTURES *-====
*/

struct						s_bubble
{
	int						pos;
	t_bubble				*next;
};

struct						s_doom
{
	t_graphic_lib			lib;
	t_player				player;
	t_tabinputs				tabinputs;
	t_start					tab[NB_BUBBLE];
	t_bubble				*bubble_list;
	t_bubble				*lightning_list;
	t_bubble				*lightning_list2;
	char					map_to_save[SIZE_MAP][SIZE_MAP][SIZE_MAP];
	long					button;
	long					state;
	t_octree				*octree;
	int						load_page[2];
	double					sensitivity;
	int						sampling;
};

/*
** ====-* PROGRAM *-====
*/

int							init_program(t_doom *data);
int							program(t_doom *data);
int							leave_program(t_doom *data, int type);

/*
** ====-* GRAPHICS *-====
*/

int							frame_calculator(void);
void						color_rectangle(t_doom *data, t_vec3l rectangle, int step);
int							create_octree(t_doom *data);
int							raytracing(t_doom *data);
unsigned int				ray_intersect(t_vec3d ray, t_vec3d origin, t_octree *node, t_doom *data);

/*
** ====-* PHYSICS *-====
*/

/*
** ====-* GAMEPLAY *-====
*/

/*
** ====-* COMMANDS *-====
*/

void						editor_commands(t_doom *data, char str[50], int *map, int *first);

/*
** ====-* GAMESTATES *-====
*/

void						switch_state(t_doom *data, long actual_state, long new_state);

int							state_start(t_doom *data);

int							state_main_menu(t_doom *data);

int							state_play_menu(t_doom *data);

int							state_scoreboard(t_doom *data);

int							state_settings_menu(t_doom *data);

int							state_get_input(t_doom *data);

int							state_editor(t_doom *data);

int							state_game(t_doom *data);

#endif
