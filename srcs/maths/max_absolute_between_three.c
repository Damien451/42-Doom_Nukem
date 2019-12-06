/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   max_absolute_between_three.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 12:00:52 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/02 12:17:14 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"

static inline void	compute_values(t_vec3d vec, int x[3], int tab[3])
{
	x[0] = 0;
	x[1] = 1;
	x[2] = 2;
	if (vec.x < 0)
	{
		vec.x = -vec.x;
		x[0] = 3;
	}
	if (vec.y < 0)
	{
		vec.y = -vec.y;
		x[1] = 4;
	}
	if (vec.z < 0)
	{
		vec.z = -vec.z;
		x[2] = 5;
	}
	tab[0] = x[0];
	tab[1] = x[1];
	tab[2] = x[2];
}

static void			swap_values(int tab[3], int first, int second)
{
	tab[second] ^= tab[first];
	tab[first] ^= tab[second];
	tab[second] ^= tab[first];
}

void				max_absolute_between_three(t_vec3d vec, int tab[3])
{
	int		x[3];

	compute_values(vec, x, tab);
	if (vec.x <= vec.y && vec.x <= vec.z)
	{
		if (vec.z < vec.y)
			swap_values(tab, 1, 2);
		return ;
	}
	if (vec.y <= vec.x && vec.y <= vec.z)
	{
		tab[0] = x[1];
		tab[1] = x[0];
		if (vec.z < vec.x)
			swap_values(tab, 1, 2);
		return ;
	}
	tab[0] = x[2];
	tab[2] = x[0];
	if (vec.x < vec.y)
		swap_values(tab, 1, 2);
}
