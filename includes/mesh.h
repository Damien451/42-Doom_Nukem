/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/05 10:59:03 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/05 11:35:40 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MESH_H
# define MESH_H

# include "vec3.h"

typedef struct s_doom		t_doom;
typedef struct s_mesh		t_mesh;
typedef struct s_triangle	t_triangle;

struct						s_mesh
{
	t_triangle				*triangle;
	long					nbr_vertices;
	long					nbr_triangles;
	t_mesh					*next;
};

struct						s_triangle
{
	t_vec3d					vertices[3];
	t_vec3d					normals[3];
	long					attribute;
	t_triangle				*next;
};

int			rasterization(t_doom *data, t_mesh *meshes);

#endif
