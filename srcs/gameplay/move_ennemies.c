/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ennemies.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 21:55:17 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/09 18:59:03 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "gameplay.h"
#include "libft.h"
#include "math.h"

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

static void			init_vecs(t_vec3d *vecs)
{
	vecs[0] = vec3d(0, -1, 0);
	vecs[1] = vec3d(0, 1, 0);
	vecs[2] = vec3d(0, 0, 1);
	vecs[3] = vec3d(-1, 0, 0);
	vecs[4] = vec3d(1, 0, 0);
	vecs[5] = vec3d(0, 0, -1);
}

t_way				*breadth_first_search_player(t_doom *data,
	t_vec3d playerpos, char map[64][64][64], t_enemy *enemy)
{
	t_queue		*queue[2];
	t_path		*path;
	int			i;
	t_vec3d		vecs[6];
	t_hitbox	tmp_hitbox;

	printf("BFS\n");
	create_map_copy(data);
	init_vecs(vecs);
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
		tmp_hitbox = hitbox(playerpos, vec3d(playerpos.x + 1, playerpos.y + 2, playerpos.z + 1));
		i = -1;
		while (++i < 6)
		{
			if (playerpos.x + vecs[i].x >= 0 && playerpos.x + vecs[i].x <= 63 && playerpos.y + vecs[i].y >= 0 && playerpos.y + vecs[i].y <= 63 && playerpos.z + vecs[i].z >= 0 && playerpos.z + vecs[i].z <= 63)
			{
				if (data->map_copy[(int)(playerpos.x + vecs[i].x)][(int)(playerpos.y + vecs[i].y)][(int)(playerpos.z + vecs[i].z)] == 0)
				{
					if (!move_hitbox(vecs[i], tmp_hitbox, map))
					{
						path = malloc(sizeof(t_path));
						path->position.x = vecs[i].x;
						path->position.y = vecs[i].y;
						path->position.z = vecs[i].z;
						path->prev = playerpos;
						queue_add(&queue[1], queue_new(path));
						data->map_copy[(int)(playerpos.x + vecs[i].x)][(int)(playerpos.y + vecs[i].y)][(int)(playerpos.z + vecs[i].z)] = 1;
					}
				}
				else if (data->map_copy[(int)(playerpos.x + vecs[i].x)][(int)(playerpos.y + vecs[i].y)][(int)(playerpos.z + vecs[i].z)] == 2)
				{
					path = malloc(sizeof(t_path));
					path->position.x = vecs[i].x;
					path->position.y = vecs[i].y;
					path->position.z = vecs[i].z;
					path->prev = playerpos;
					queue_add(&queue[1], queue_new(path));
					return (transform_queue_to_path(queue[1]));
				}
			}
		}
		queue[0] = queue[0]->next;
	}
	free_queue_ptr(queue[1]);
	return (NULL);
}

static double position_check(t_player *player, t_enemy *enemy)
{
	return (vec3d_length2(vec3d_sub(player->camera.origin,
		enemy->hitbox.min)));
}

static void move_enemy(t_enemy *enemy, char map[64][64][64])
{
	printf("MOVE ENEMY\n");
	enemy->state = ALIVE;
	if (!(move_hitbox(enemy->way->position, enemy->hitbox, map)))
	{
		enemy->hitbox.min.x = enemy->way->position.x;
		enemy->hitbox.min.y = enemy->way->position.y;
		enemy->hitbox.min.z = enemy->way->position.z;
		enemy->hitbox.max.x = enemy->way->position.x + 1;
		enemy->hitbox.max.y = enemy->way->position.y + 2;
		enemy->hitbox.max.z = enemy->way->position.z + 1;
	}
}

static void attack_enemy(t_enemy *enemy, t_player *player)
{
	enemy->state = ATTACK;
	player->health = (player->health - 50 < 0 ? 0 : player->health - 50);
}

void move_ennemies(t_doom *data, t_player *player,
				   t_enemies *enemies)
{
	int			i;
	static int	frame = 0;
	double		distance;

	i = -1;
	while (++i < enemies->nb)
	{
		distance = position_check(player, &enemies->enemy[i]);
		if (enemies->enemy[i].state == ALIVE && distance < 255 && distance > 1
			&& frame % 20 == 0)
			enemies->enemy[i].way = breadth_first_search_player(
				data, player->camera.origin, data->map_to_save,
				&enemies->enemy[i]);
		if (enemies->enemy[i].way != NULL)
			move_enemy(&enemies->enemy[i], data->map_to_save);
		if (distance <= 1 && frame % 10 == 0)
			attack_enemy(&enemies->enemy[i], player);
        //printf("distance == %f\n", distance);
		//printf("playerpos x %f, y %f, z %f\n", player->camera.origin.x, player->camera.origin.y, player->camera.origin.z);
	}
	++frame;
	if (frame == 120)
		frame = 0;
}
