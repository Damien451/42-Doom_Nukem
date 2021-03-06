/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   put_health_bar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:44:32 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/24 20:44:01 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "menus.h"
#include "libft.h"

void	put_health_bar(t_doom *data)
{
	if (data->player.health < 1000)
		draw_rectangle(&(data->lib), point(HEALTH_BAR_WIDTH_START,
			HEALTH_BAR_HEIGHT_START), point(HEALTH_BAR_WIDTH,
			(int)((((data->player.health < 0 ? 0 : data->player.health)
				- 1000.0) / -1000) * HEALTH_BAR_HEIGHT)),
			0xff0000);
}
