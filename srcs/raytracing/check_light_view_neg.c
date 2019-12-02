/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_light_view_neg.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 08:48:38 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/02 08:49:10 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

int			check_light_view_x_neg(t_vec3d position, t_vec3d light_pos)
{
	return (position.x > light_pos.x);
}

int			check_light_view_y_neg(t_vec3d position, t_vec3d light_pos)
{
	return (position.y > light_pos.y);
}

int			check_light_view_z_neg(t_vec3d position, t_vec3d light_pos)
{
	return (position.z > light_pos.z);
}
