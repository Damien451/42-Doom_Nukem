#ifndef INPUTS_H
# define INPUTS_H

/*
** ====-* INCLUDES *-====
*/

# include <SDL.h>

/*
** ====-* DEFINES *-====
*/

# define NB_MODIF_INPUTS 12

# define DEFINPUT1 SDLK_w
# define DEFINPUT2 SDLK_a
# define DEFINPUT3 SDLK_s
# define DEFINPUT4 SDLK_d
# define DEFINPUT5 SDLK_q
# define DEFINPUT6 SDLK_r
# define DEFINPUT7 SDLK_LSHIFT
# define DEFINPUT8 SDLK_z
# define DEFINPUT9 SDLK_c
# define DEFINPUT10 SDLK_SPACE
# define DEFINPUT11 SDLK_e
# define DEFINPUT12 SDLK_F2


/*
** ====-* TYPEDEFS *-====
*/

typedef struct s_tabinputs	t_tabinputs;

/*
** ====-* STRUCTURES *-====
*/

struct						s_tabinputs
{
	unsigned int			keycode[NB_MODIF_INPUTS];
};

/*
** ====-* PROTOTYPES *-====
*/

int			parse_input_file(t_doom *data, char *input_dict);
int			get_default_inputs(t_doom *data);


#endif
