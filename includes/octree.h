/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:21:10 by roduquen          #+#    #+#             */
/*   Updated: 2019/10/27 20:13:00 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OCTREE_H
# define OCTREE_H

/*
**	INCLUDES
*/

# include "vec3.h"
# include "libft.h"

/*
**	DEFINES
*/

# define EMPTY	0
# define INSIDE	1
# define FULL	2

/*
**	TYPEDEF
*/

typedef struct s_octree	t_octree;
typedef struct s_doom	t_doom;

/*
**	STRUCTURES
*/

struct					s_octree
{
	t_octree			*child[8];
	t_vec3l				center;
	int					size;
	char				leaf;
	t_octree			*parent;
};

/*
**	PROTOTYPES
*/

t_octree				*create_node(int size, t_vec3l center
	, t_octree *parent);

int						create_child(t_octree *node, t_doom *data);

int						free_queue(t_queue *queue[2]);

void					check_if_child_is_leaf(t_doom *data, t_octree *node);

t_octree				*find_actual_position(t_vec3d *position
	, t_octree *node);

t_octree				*find_node_to_go_parent(t_vec3d intersect
	, t_octree *node, int card, t_vec3d origin);

#endif
