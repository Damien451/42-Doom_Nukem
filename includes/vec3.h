/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 13:35:26 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/15 13:35:27 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VEC3_H
# define VEC3_H

/*
** ====-* INCLUDES *-====
*/

/*
** ====-* DEFINES *-====
*/

/*
** ====-* TYPEDEFS *-====
*/

typedef struct s_vec3l		t_vec3l;
typedef struct s_vec3d		t_vec3d;

/*
** ====-* STRUCTURES *-====
*/

struct						s_vec3d
{
	double					x;
	double					y;
	double					z;
};

struct						s_vec3l
{
	long					x;
	long					y;
	long					z;
};

/*
** DOUBLE
*/

t_vec3d						vec3d(double x, double y, double z);
double						vec3d_length2(t_vec3d vec);
t_vec3d						vec3d_unit(t_vec3d vec);
t_vec3d						vec3d_add(t_vec3d vec_a, t_vec3d vec_b);
t_vec3d						vec3d_sub(t_vec3d vec_a, t_vec3d vec_b);
t_vec3d						vec3d_mul(t_vec3d vec_a, t_vec3d vec_b);
t_vec3d						vec3d_cross(t_vec3d vec_a, t_vec3d vec_b);
t_vec3d						vec3d_scalar(t_vec3d vec_a, double scalar);
double						vec3d_dot(t_vec3d vec_a, t_vec3d vec_b);

/*
** LONG
*/

t_vec3l						vec3l(long x, long y, long z);
long						vec3l_length2(t_vec3l vec);
t_vec3l						vec3l_unit(t_vec3l vec);
t_vec3l						vec3l_add(t_vec3l vec_a, t_vec3l vec_b);
t_vec3l						vec3l_sub(t_vec3l vec_a, t_vec3l vec_b);
t_vec3l						vec3l_mul(t_vec3l vec_a, t_vec3l vec_b);
t_vec3l						vec3l_cross(t_vec3l vec_a, t_vec3l vec_b);
t_vec3l						vec3l_scalar(t_vec3l vec_a, long scalar);
long						vec3l_dot(t_vec3l vec_a, t_vec3l vec_b);

#endif
