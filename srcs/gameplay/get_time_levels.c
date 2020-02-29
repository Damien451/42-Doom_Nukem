/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_time_levels.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 16:41:04 by dacuvill          #+#    #+#             */
/*   Updated: 2020/02/29 17:15:19 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "player.h"
#include <sys/time.h>

long		get_time_levels(t_player *player)
{
	struct timeval	time;
	static int		call = 0;
	static long		duration = 0;

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
		duration = time.tv_sec - duration;
		call = 0;
		return (duration);
	}
}
