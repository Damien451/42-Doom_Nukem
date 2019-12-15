/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entities.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 13:35:35 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/15 13:35:41 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ENTITIES_H
# define ENTITIES_H

# include "graphic_lib.h"
# include "player.h"
# include "libft.h"
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
int			init_zbuf(t_zbuf *zbuf);
void		z_buffer(t_entity *entities, t_player player, t_zbuf *zbuf);

#endif
