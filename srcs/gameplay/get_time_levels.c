/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_levels.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 16:41:04 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/04 12:53:41 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include <sys/time.h>

int			get_time_levels(void)
{
	struct timeval	time;
	static int		call = 0;
	static int		duration = 0;

	if (call == 0)
	{
		gettimeofday(&time, NULL);
		duration = time.tv_sec;
		call = 1;
		return (0);
	}
	else
	{
		gettimeofday(&time, NULL);
		duration = ((time.tv_sec - duration) * 10 > 5000 ? 0 :
			5000 - (time.tv_sec - duration) * 10);
		call = 0;
		return (duration);
	}
}
