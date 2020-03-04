/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_pos_player.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 20:12:01 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/04 12:45:23 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "player.h"
#include "gameplay.h"

void        check_pos_player(t_doom *data, char map[64][64][64], t_vec3d pos)
{
	if (map[(int)pos.x][(int)pos.y - 2][(int)pos.z] == ID_FINISH_BLOCK + 1)
		put_string_with_shadow(data, point(WIDTH / 2, HEIGHT / 3),
			label("Press return to leave the level",
			(SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[2]);
	//else if ((int)pos.y - 1 == 0)
		//data->player.health = 0;
}
