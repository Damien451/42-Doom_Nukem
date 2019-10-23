#ifndef INPUTS_H
# define INPUTS_H

/*
** ====-* INCLUDES *-====
*/

# include <SDL.h>

/*
** ====-* DEFINES *-====
*/

# define NB_INPUTS 14
# define LINES_DICT_FILE 225
# define INPUTS_DICT_FILE 222

/*
** ====-* TYPEDEFS *-====
*/

typedef struct s_doom		t_doom;
typedef struct s_input		t_input;
typedef struct s_tabinputs	t_tabinputs;

/*
** ====-* STRUCTURES *-====
*/

struct						s_input
{
	SDL_Scancode			scancode;
	char					*key_name;
	char					*set_title;
};

struct						s_tabinputs
{
	t_input					inputs[NB_INPUTS];
	char					*comment;
};

/*
** ====-* PROTOTYPES *-====
*/

int			parse_input_dict(t_doom *data, char *input_dict);
void		free_tabinputs(t_doom *data);

#endif
