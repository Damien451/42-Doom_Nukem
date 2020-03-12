/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gameplay.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/06 17:47:36 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/11 18:42:00 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GAMEPLAY_H
# define GAMEPLAY_H

/*
**	INCLUDES
*/

# include "vec3.h"

/*
** ====-* DEFINES *-====
*/

# define DISTANCE_MAX_BLOCK 4.0f

# define ALIVE		0
# define DEAD		1
# define ATTACK		2

/*
** ====-* TYPEDEFS *-====
*/

typedef struct s_doom		t_doom;
typedef struct s_player		t_player;
typedef struct s_enemy		t_enemy;
typedef struct s_enemies	t_enemies;
typedef	struct s_vec3l		t_vec3l;
typedef struct s_vec3d		t_vec3d;
typedef struct s_hitbox		t_hitbox;
typedef struct s_path		t_path;
typedef struct s_way		t_way;

/*
** ====-* STRUCTURES *-====
*/

struct						s_way
{
	t_way					*next;
	t_vec3d					position;
};

struct						s_path
{
	t_vec3d					position;
	t_vec3d					prev;
};

struct						s_hitbox
{
	t_vec3d					min;
	t_vec3d					max;
};

struct						s_enemy
{
	double					life;
	t_hitbox				hitbox;
	t_way					*way;
	int						state;
};

struct						s_enemies
{
	t_enemy					enemy[20];
	int						nb;
};

/*
** ====-* PROTOTYPES *-====
*/

void						interaction(t_doom *data, unsigned int key);
void						check_pos_player(t_doom *data,
	char map[64][64][64], t_vec3d pos);
int							check_if_not_in_map(t_hitbox hitbox,
	char map[64][64][64]);
t_hitbox					hitbox(t_vec3d min, t_vec3d max);
int							move_hitbox(t_vec3d direction,
	t_hitbox hitbox, char map[64][64][64]);
int							init_enemies(t_doom *data,
	t_enemies *enemies, char map[64][64][64]);
int							reset_game_values(t_doom *data, t_player *player);

void						move_ennemies(t_doom *data, t_player *player,
	t_enemies *enemies);
void						reload(t_player *player);

void						get_item(t_doom *data, t_player *player,
	char *map[64][64][64], t_vec3d posbloc);

#endif
