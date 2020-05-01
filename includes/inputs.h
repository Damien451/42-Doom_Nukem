/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inputs.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 13:08:52 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/15 13:09:50 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUTS_H
# define INPUTS_H

/*
** ====-* INCLUDES *-====
*/

# include <SDL.h>

/*
** ====-* DEFINES *-====
*/

# define NB_MODIF_INPUTS	12

# define DEFINPUT1			SDLK_w
# define DEFINPUT2			SDLK_a
# define DEFINPUT3			SDLK_s
# define DEFINPUT4			SDLK_d
# define DEFINPUT5			SDLK_r
# define DEFINPUT6			SDLK_LSHIFT
# define DEFINPUT7			SDLK_c
# define DEFINPUT8			SDLK_SPACE
# define DEFINPUT9			SDLK_F2
# define DEFINPUT10			SDLK_h
# define DEFINPUT11			SDLK_l
# define DEFINPUT12			SDLK_F3

/*
** ====-* TYPEDEFS *-====
*/

typedef struct s_doom		t_doom;
typedef struct s_input		t_input;
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

int							parse_input_file(t_doom *data, char *input_dict);
int							get_default_inputs(t_doom *data);

#endif
