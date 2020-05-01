/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/04 15:44:00 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/06 17:46:59 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_H
# define MATRIX_H

/*
**	TYPEDEFS
*/

# include "vec3.h"

int		matrix44_multiply(const double a[4][4], const double b[4][4]
	, double result[4][4]);

int		matrix44_vec3d_mul(double matrix[4][4], t_vec3d src, t_vec3d *result);
int		matrix44_identity(double result[4][4]);
int		matrix44_inverse(const double matrix[4][4], double result[4][4]);
#endif
