/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_light_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 16:22:41 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/15 16:08:35 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		add_light_to_node(t_doom *data, int cor[3], double tab[3]
	, int type)
{
	t_light	*light;

	if (data->light_array[cor[0]][cor[1]][cor[2]].type == 0)
	{
		data->light_array[cor[0]][cor[1]][cor[2]].type = type;
		data->light_array[cor[0]][cor[1]]
			[cor[2]].next = malloc(sizeof(t_light));
		light = data->light_array[cor[0]][cor[1]][cor[2]].next;
	}
	else
	{
		light = data->light_array[cor[0]][cor[1]][cor[2]].next;
		while (light->next)
			light = light->next;
		light->next = malloc(sizeof(t_light));
		light = light->next;
	}
	light->position.x = tab[0];
	light->position.y = tab[1];
	light->position.z = tab[2];
	light->next = NULL;
	light->type = type;
	return (0);
}

void	init_wait(int wait[3], int cor[3], double tab[3])
{
	tab[0] = cor[0] + 0.5;
	tab[1] = cor[1] + 0.5;
	tab[2] = cor[2] + 0.5;
	wait[0] = cor[0] + 3;
	if (wait[0] > 64)
		wait[0] = 64;
	wait[1] = cor[1] + 3;
	if (wait[1] > 64)
		wait[1] = 64;
	wait[2] = cor[2] + 3;
	if (wait[2] > 64)
		wait[2] = 64;
	wait[3] = cor[0] - 3;
	if (wait[3] < 0)
		wait[3] = 0;
	wait[4] = cor[1] - 3;
	if (wait[4] < 0)
		wait[4] = 0;
	wait[5] = cor[2] - 3;
	if (wait[5] < 0)
		wait[5] = 0;
}

int		add_light_to_array(int cor[3], t_doom *data)
{
	int			wait[6];
	int			inc[3];
	double		tab[3];
	int			type;

	type = TORCH + (rand() & 3);
	init_wait(wait, cor, tab);
	inc[0] = wait[3];
	while (inc[0] < wait[0])
	{
		inc[1] = wait[4];
		while (inc[1] < wait[1])
		{
			inc[2] = wait[5];
			while (inc[2] < wait[2])
			{
				add_light_to_node(data, inc, tab, type);
				inc[2]++;
			}
			inc[1]++;
		}
		inc[0]++;
	}
	return (0);
}

int		create_light_array(t_doom *data)
{
	int			cor[3];

	cor[0] = 0;
	while (cor[0] < 64)
	{
		cor[1] = 0;
		while (cor[1] < 64)
		{
			cor[2] = 0;
			while (cor[2] < 64)
			{
				if (data->map_to_save[cor[0]][cor[1]][cor[2]] == 41)
					add_light_to_array(cor, data);
				cor[2]++;
			}
			cor[1]++;
		}
		cor[0]++;
	}
	return (0);
}
