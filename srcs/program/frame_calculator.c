/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frame_calculator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 13:46:08 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/08 22:04:58 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <sys/time.h>

void		frame_calculator(void)
{
	static long		frame = 0;
	static long		time = 0;
	long			actual_time;
	long			actual_frame;
	struct timeval	timet;

	gettimeofday(&timet, NULL);
	actual_time = timet.tv_sec * 1000000 + timet.tv_usec;
	if (actual_time - time > 1000000)
	{
		actual_frame = frame;
		time = actual_time;
		ft_putnbr(frame);
		ft_putchar('\n');
		frame = 0;
	}
	frame++;
}
