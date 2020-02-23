/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_str.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/17 15:25:50 by dacuvill          #+#    #+#             */
/*   Updated: 2020/02/23 16:01:56 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include <sys/time.h>

static void	manage_transparency(long time_left, long duration, int *alpha)
{
	if (time_left > duration * 0.6 && *alpha <= 253 && *alpha > 0)
		(*alpha) += 2;
	else if (time_left < duration * 0.4 && *alpha <= 255 && *alpha > 2)
		(*alpha) -= 2;
}

int			display_str(t_doom *data, t_point pos, char *str, long duration)
{
	struct timeval	time;
	static int		flag = 0;
	static long		time_left = 255;
	static int		alpha = 1;
	long			wait;

	if (flag == 0)
	{
		time_left = duration;
		flag = 1;
	}
	gettimeofday(&time, NULL);
	wait = time.tv_sec * 1000000 + time.tv_usec;
	put_string_on_renderer(data, pos, label(str,
		(SDL_Color){255, 0, 0, alpha}), data->lib.ptrfont[2]);
	manage_transparency(time_left, duration, &alpha);
	gettimeofday(&time, NULL);
	if ((time_left -= time.tv_sec * 1000000 + time.tv_usec - wait) <= 0)
	{
		flag = 0;
		time_left = 0;
		alpha = 1;
	}
	return (time_left > 0 ? 0 : 1);
}