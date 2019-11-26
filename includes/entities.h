#ifndef ENTITIES_H
# define ENTITIES_H

# include "doom.h"
# include "vec3.h"

typedef struct s_entity t_entity;

typedef struct	s_entity
{
	SDL_Surface *texture;
	t_vec3d		pos;
	t_entity	*next;
}				t_entity;

typedef struct	s_zbuf
{
	int		*zcolor;
	double	*zdist;	
}				t_zbuf;


#endif