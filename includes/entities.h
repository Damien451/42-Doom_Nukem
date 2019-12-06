#ifndef ENTITIES_H
# define ENTITIES_H

# include "doom.h"
# include "vec3.h"

typedef struct s_entity t_entity;

typedef struct	s_entity
{
	t_vec3d		pos;
	SDL_Surface *texture;
	t_entity	*next;
	int			id;
}				t_entity;

typedef struct	s_zbuf
{
	int			*zcolor;
	double		*zdist;
}				t_zbuf;

/*
** ====-* PROTOTYPES *-====
*/

void		create_entity(t_entity *entities, t_vec3d pos, SDL_Surface *texture);
int 		init_zbuf(t_zbuf *zbuf);
t_zbuf		z_buffer(t_entity *entities, t_player player);

#endif