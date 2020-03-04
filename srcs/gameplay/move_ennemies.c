/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ennemies.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 21:55:17 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/04 19:51:35 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "gameplay.h"
#include "libft.h"

void				free_queue_ptr(t_queue *queue)
{
	t_queue 	*tmp;

	tmp = queue;
	while (tmp)
	{
		queue = tmp->prev;
		free(tmp->ptr);
		free(tmp);
		tmp = queue;
	}
}

t_way				*transform_queue_to_path(t_queue *queue)
{
	t_queue		*end;
	t_way		*way;
	t_way		*start;

	way = malloc(sizeof(t_way));
	start = queue->ptr;
	way->next = NULL;
	way->position = ((t_path*)queue->ptr)->prev;
	end = queue;
	while (queue)
	{
		if (way->position.x == ((t_path*)queue->ptr)->position.x
			&& way->position.y == ((t_path*)queue->ptr)->position.y
			&& way->position.z == ((t_path*)queue->ptr)->position.z)
		{
			way->next = malloc(sizeof(t_way));
			way = way->next;
			way->next = NULL;
			way->position = ((t_path *)queue->ptr)->prev;
		}
		queue = queue->prev;
	}
	free_queue_ptr(end);
	return (start);
}

static void			create_map_copy(t_doom *data)
{
	int			i;
	int			j;
	int			k;

	k = -1;
	while (++k < SIZE_MAP)
	{
		i = -1;
		while (++i < SIZE_MAP)
		{
			j = -1;
			while (++j < SIZE_MAP)
			{
				if (data->map_to_save[k][i][j])
					data->map_copy[k][i][j] = 1;
				else
					data->map_copy[k][i][j] = 0;
			}
		}
	}
}

t_way				*breadth_first_search_player(t_doom *data,
	t_vec3d playerpos, char map[64][64][64], t_enemy *enemy)
{
	t_queue		*queue[2];
	t_path		*path;
	t_vec3d		i;
	t_vec3l		tmp;

	create_map_copy(data);
	path = malloc(sizeof(t_path));
	data->map_copy[(int)enemy->hitbox.min.x]
		[(int)enemy->hitbox.min.y][(int)enemy->hitbox.min.z] = 2;
	path->position = playerpos;
	path->prev = vec3d(-5, -5, -5);
	queue[0] = queue_new(path);
	queue[1] = queue[0];
	while (queue[0])
	{
		playerpos = ((t_path *)queue[0]->ptr)->position;
		i.x = -1;
		while (i.x <= 1)
		{
			i.y = -1;
			while (i.y <= 1)
			{
				i.z = -1;
				while (i.z <= 1)
				{
					tmp.x = playerpos.x + i.x;
					if (tmp.x >= 0 && tmp.x <= 63)
					{
						tmp.y = playerpos.y + i.y;
						if (tmp.y >= 0 && tmp.y <= 63)
						{
							tmp.z = playerpos.z + i.z;
							if (tmp.z >= 0 && tmp.z <= 63)
							{
								if (data->map_copy[tmp.x][tmp.y][tmp.z] == 0)
								{
									if (!move_hitbox(i, enemy->hitbox, map))
									{
										path = malloc(sizeof(t_path));
										path->position.x = tmp.x;
										path->position.y = tmp.y;
										path->position.z = tmp.z;
										path->prev = playerpos;
										queue_add(&queue[1], path);
										data->map_copy[tmp.x][tmp.y][tmp.z] = 1;
									}
								}
								else if (data->map_copy[tmp.x][tmp.y][tmp.z] == 2)
								{
									path = malloc(sizeof(t_path));
									path->position.x = tmp.x;
									path->position.y = tmp.y;
									path->position.z = tmp.z;
									path->prev = playerpos;
									queue_add(&queue[1], path);
									return (transform_queue_to_path(queue[1]));
								}
							}
						}
						i.z += 2;
					}
					i.y += 2;
				}
				i.x += 2;
			}
		}
		queue[0] = queue[0]->next;
	}
	free_queue_ptr(queue[1]);
	return (NULL);
}

static int			position_check(t_player *player, t_enemy *enemy)
{
	double 		distance;

	distance = vec3d_length2(vec3d_sub(player->camera.origin,
		enemy->hitbox.min));
	if (distance > 225 || distance <= 1)
		return (0);
	return (1);
}

static void			move_enemy(t_enemy *enemy, char map[64][64][64])
{
	enemy->state = ALIVE;
	if (!(move_hitbox(enemy->way->position, enemy->hitbox, map)))
	{
		enemy->hitbox.min.x += enemy->way->position.x - enemy->hitbox.min.x;
		enemy->hitbox.min.y += enemy->way->position.y - enemy->hitbox.min.y;
		enemy->hitbox.min.z += enemy->way->position.z - enemy->hitbox.min.z;
		enemy->hitbox.max.x += enemy->way->position.x - enemy->hitbox.max.x;
		enemy->hitbox.max.y += enemy->way->position.y - enemy->hitbox.max.y;
		enemy->hitbox.max.z += enemy->way->position.z - enemy->hitbox.max.z;
	}
}

static void			attack_enemy(t_enemy *enemy, t_player *player)
{
	enemy->state = ATTACK;
	player->health = (player->health - 50 < 0 ? 0 : player->health - 50);
}

void				move_ennemies(t_doom *data, t_player *player,
	t_enemies *enemies)
{
	int			i;
	double		distance;

	i = -1;
	while (++i < enemies->nb)
	{
		distance = position_check(player, &enemies->enemy[i]);
		if (enemies->enemy[i].state == ALIVE
			&& distance < 255 && distance > 1)
			enemies->enemy[i].way = breadth_first_search_player(
				data, player->camera.origin, data->map_to_save,
				&enemies->enemy[i]);
		if (enemies->enemy[i].way != NULL)
			move_enemy(&enemies->enemy[i], data->map_to_save);
		if (distance <= 1)
			attack_enemy(&enemies->enemy[i], player);
		printf("distance == %f\n", distance);
		//printf("enemy %d pos.x = %f, pos.y = %f, pos.z = %f\n",
		//	i, enemies->enemy[i].hitbox.min.x, enemies->enemy[i].hitbox.min.y, enemies->enemy[i].hitbox.min.z);
	}
}
