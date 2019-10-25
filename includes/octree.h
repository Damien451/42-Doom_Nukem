/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   octree.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/16 17:21:10 by roduquen          #+#    #+#             */
/*   Updated: 2019/10/22 11:23:18 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OCTREE_H
# define OCTREE_H

# include "vec3.h"
# define EMPTY	0
# define INSIDE	1
# define FULL	2

typedef struct s_octree	t_octree;

struct					s_octree
{
	t_octree			*child[8];
	t_vec3l				center;
	int					size;
	char				leaf;
	t_octree			*parent;
};

#endif
