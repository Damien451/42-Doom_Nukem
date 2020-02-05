/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_light_array.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/08 16:22:41 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/05 17:41:53 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"

int		free_light_map(t_doom *data)
{
	int		cnt[3];
	t_light	*tmp;

	cnt[0] = 0;
	while (cnt[0] < SIZE_MAP)
	{
		cnt[1] = 0;
		while (cnt[1] < SIZE_MAP)
		{
			cnt[2] = 0;
			while (cnt[2] < SIZE_MAP)
			{
				if (data->light_array[cnt[0]][cnt[1]][cnt[2]].type)
				{
					data->light_array[cnt[0]][cnt[1]][cnt[2]].type = 0;
					while (data->light_array[cnt[0]][cnt[1]][cnt[2]].next)
					{
						tmp = data->light_array[cnt[0]][cnt[1]][cnt[2]].next->next;
						free(data->light_array[cnt[0]][cnt[1]][cnt[2]].next);
						data->light_array[cnt[0]][cnt[1]][cnt[2]].next = tmp;
					}
				}
				cnt[2]++;
			}
			cnt[1]++;
		}
		cnt[0]++;
	}
	return (0);
}

int		add_light_to_node(t_doom *data, int cor[3], double tab[3])
{
	t_light	*light;

	if (data->light_array[cor[0]][cor[1]][cor[2]].type == 0)
	{
		data->light_array[cor[0]][cor[1]][cor[2]].type = TORCH;
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
	light->type = TORCH;
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
				add_light_to_node(data, inc, tab);
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

	free_light_map(data);
	cor[0] = 0;
	while (cor[0] < 64)
	{
		cor[1] = 0;
		while (cor[1] < 64)
		{
			cor[2] = 0;
			while (cor[2] < 64)
			{
				if (data->map_to_save[cor[0]][cor[1]][cor[2]] == 39)
					add_light_to_array(cor, data);
				cor[2]++;
			}
			cor[1]++;
		}
		cor[0]++;
	}
	return (0);
}
