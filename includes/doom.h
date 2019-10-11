#ifndef DOOM_H
# define DOOM_H

/*
** ====-* INCLUDES *-====
*/ 

#include "graphic_lib.h"
#include "inputs.h"

/*
** ====-* DEFINES *-====
*/

# define EPSILON	1e-20

# define RUNNING	(1l << 62)
# define START		(1l)
# define PLAYING	(1l << 1)
# define PAUSE		(1l << 2)
# define MAIN_MENU	(1l << 3)
# define SCORES		(1l << 4)
# define SETTINGS	(1l << 5)
# define LEAVING	(1l << 6)

/*
** ====-* TYPEDEFS *-====
*/

typedef struct s_doom			t_doom;
typedef struct s_graphic_lib	t_graphic_lib;

/*
** ====-* STRUCTURES *-====
*/

struct						s_doom
{
	t_graphic_lib			lib;
	t_tabinputs				tabinputs;
	long					button;
	long					state;
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

/*
** ====-* PHYSICS *-====
*/

/*
** ====-* GAMEPLAY *-====
*/

/*
** ====-* COMMANDS *-====
*/

/*
** ====-* GAMESTATES *-====
*/

void						switch_state(t_doom *data, long actual_state, long new_state);

int							game_start(t_doom *data);

int							game_main_menu(t_doom *data);

int							settings_menu(t_doom *data);

#endif
