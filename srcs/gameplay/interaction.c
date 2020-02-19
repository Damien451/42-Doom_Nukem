/* ************************************************************************** */
/*	*/
/*	:::	  ::::::::   */
/*   interaction.c	  :+:	  :+:	:+:   */
/*	+:+ +:+	 +:+	 */
/*   By: dacuvill <marvin@42.fr>	+#+  +:+	   +#+	*/
/*	+#+#+#+#+#+   +#+	   */
/*   Created: 2020/02/12 15:46:30 by smokhtar	  #+#	#+#	 */
/*   Updated: 2020/02/19 16:22:01 by dacuvill	 ###   ########.fr	   */
/*	*/
/* ************************************************************************** */

#include "gameplay.h"
#include "doom.h"

static void		put_block(t_doom *data, t_hit *line)
{
	t_vec3d	pos;
	int		face;
	int		tmp[3];

	face = line->face;
	pos = line->ray->intersect;
	if (data->map_to_save[(int)floor(pos.x)][(int)floor(pos.y)][(int)floor(pos.z)] == 0)
		data->map_to_save[(int)floor(pos.x)][(int)floor(pos.y)][(int)floor(pos.z)] =
			data->player.inventory.selected_block;
	else
	{
		tmp[0] = (int)((face == X_MIN ? 1 : 0) + (face == X_MAX ? -1 : 0) + (int)floor(pos.x));
		tmp[1] = (int)((face == Y_MIN ? 1 : 0) + (face == Y_MAX ? -1 : 0) + (int)floor(pos.y));
		tmp[2] = (int)((face == Z_MIN ? 1 : 0) + (face == Z_MAX ? -1 : 0) + (int)floor(pos.z));
		if (data->map_to_save[tmp[0]][tmp[1]][tmp[2]] == 0)
			data->map_to_save[tmp[0]][tmp[1]][tmp[2]] = data->player.inventory.selected_block;
	}
}

static int		check_distance(t_hit **line)
{
	int		i;
	int		good;

	i = -1;
	good = 0;
	while (++i < 3) {
		if (line[i] && line[i]->face && (int)floor(line[i]->length) < DISTANCE_MAX_BLOCK
		&& line[i]->length > 1)
			good++;
		else
			line[i] = NULL;
	}
	return (good > 1);
}

void			interaction(t_doom *data)
{
	t_hit			**line;
	int				i;

	i = -1;
	line = (t_hit**)malloc(sizeof(t_hit*) * 3);
	while (++i < 3){
		line[i] = line_of_sight(data->player.camera, data);
		line[i]->length = sqrt(line[i]->ray->length);
	}
	if (check_distance(line))
		put_block(data, (line[1] ? line[1] : line[2]));
}