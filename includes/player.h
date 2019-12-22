/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 13:26:27 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/21 19:52:22 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PLAYER_H
# define PLAYER_H

/*
** ====-* INCLUDES *-====
*/

# include "vec3.h"
# include <math.h>
# include <SDL.h>

/*
** ====-* DEFINES *-====
*/

# define CAMERA_TR_RIGHT	0x1l
# define CAMERA_TR_LEFT		0x2l
# define CAMERA_TR_FRONT	0x4l
# define CAMERA_TR_BACK		0x8l
# define COURSE				0x10l
# define WATER				0x20l
# define SQUAT				0x40l
# define DESTROY			0x80l

# define GRAVITY			1.0
# define ACCELERATION		0.003333333333333
# define MAX_SPEED			0.05

# define WIDTH_PLAYER		0.2
# define SIZE_PLAYER		1.5

/*
** ====-* TYPEDEFS *-====
*/

typedef struct s_player		t_player;
typedef struct s_camera		t_camera;
typedef struct s_inventory	t_inventory;
typedef struct s_doom		t_doom;
typedef struct s_hitbox		t_hitbox;
typedef struct s_physics	t_physics;
typedef struct s_octree		t_octree;
typedef struct s_tabinputs	t_tabinputs;

/*
** ====-* STRUCTURES *-====
*/

struct						s_hitbox
{
	t_vec3d					vertex;
};

struct						s_physics
{
	t_vec3d					origin;
	t_vec3d					acceleration;
	t_octree				*octree;
};

struct						s_camera
{
	t_vec3d					origin;
	t_vec3d					direction;
	t_vec3d					rotation;
	t_vec3d					up;
	t_vec3d					right;
	double					x_angle;
};

struct						s_inventory
{
	int						weapons;
	int						keys;
	int						*blocks[40];
	int						selected_block;
};

struct						s_player
{
	t_camera				camera;
	t_vec3d					course;
	t_vec3d					new_pos;
	t_inventory				inventory;
	double					speed;
	double					gravity;
	double					sensitivity;
	int						health;
	t_vec3d					position;
	t_vec3d					acceleration;
	t_hitbox				hitbox[12];
	void					(*collider)(t_vec3d*, t_vec3d*, t_doom*, t_player*);
	t_physics				physics;
};

void						rotate_camera(t_camera *camera, t_vec3d rot_vec
	, double angle);

void						camera_mouse_motion(t_camera *camera, int *x, int *y
	, double *sensitivity);

void						camera_press_key(SDL_Event *event, t_tabinputs *inputs, t_doom *data);

void						camera_event_translate(t_doom *data);

int							add_vertex_clipping_y_min(t_vec3d *acceleration
	, t_vec3d *new_pos, char map[64][64][64], t_vec3d position
	, t_player *player);
int							add_vertex_clipping_y_max(t_vec3d *acceleration
	, t_vec3d *new_pos, char map[64][64][64], t_vec3d position);
int							add_vertex_clipping_x_min(t_vec3d *acceleration
	, t_vec3d *new_pos, char map[64][64][64], t_vec3d position);
int							add_vertex_clipping_x_max(t_vec3d *acceleration
	, t_vec3d *new_pos, char map[64][64][64], t_vec3d position);
int							add_vertex_clipping_z_min(t_vec3d *acceleration
	, t_vec3d *new_pos, char map[64][64][64], t_vec3d position);
int							add_vertex_clipping_z_max(t_vec3d *acceleration
	, t_vec3d *new_pos, char map[64][64][64], t_vec3d position);

void						add_clipping_for_each_point(t_doom *data
	, t_player *player);

#endif
