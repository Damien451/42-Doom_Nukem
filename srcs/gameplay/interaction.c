/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interaction.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smokhtar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 15:46:30 by smokhtar          #+#    #+#             */
/*   Updated: 2020/02/12 15:46:31 by smokhtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gameplay.h"
#include "doom.h"

static int      put_block(t_doom *data, t_vec3d pos)
{
    // if ((int)floor(pos.x))
    data->map_to_save[(int)floor(pos.x)][(int)floor(pos.y)][(int)floor(pos.z)] =
        data->player.inventory.selected_block;
}

static int      check_distance(t_hit **line)
{
    int     i;
    int     good;

    i = -1;
    good = 0;
    while (++i < 3) {
	    // printf("hit block %d %d %d\n", (int)floor(line[i]->ray->intersect.x), (int)floor(line[i]->ray->intersect.y), (int)floor(line[i]->ray->intersect.z));
        if (line[i] && line[i]->type && (int)floor(line[i]->length) < DISTANCE_MAX_BLOCK
            && line[i]->length > 1)
        {
            // printf("gooddd");
            good++;
        }
        else
        {
	        // printf("bad because %d    %d    %f\n", (line[i] ? 1 : 0), (line[i] && line[i]->type ? line[i]->type : 0), (line[i] && line[i]->type && line[i]->length ? line[i]->length : 0));
            // printf("%f\n", line[i]->length );
            line[i] = NULL;
        }
    }
    printf("good = %d\n", good);
    return good > 1;
}

void            interaction(t_doom *data)
{
	t_hit			**line;
    int             i;

    i = -1;
	if (!(line = (t_hit**)malloc(sizeof(t_hit*) * 3)))
		return ;
    while (++i < 3){
        line[i] = line_of_sight(data->player.camera, data);
        line[i]->length = sqrt(line[i]->ray->length);
    }
    if (check_distance(line))
    {
        // printf("put_block\n");
	    // printf("player positionnnnnnn %f %f %f\n", data->player.position.x, data->player.position.y, data->player.position.z);
	    // printf("player direction %d %d %d\n", (int)floor(data->player.camera.direction.x), (int)floor(data->player.camera.direction.y), (int)floor(data->player.camera.direction.z));
        put_block(data, (line[1] ? line[1] : line[2])->ray->intersect);
        // printf("finish\n");
    }
}