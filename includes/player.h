#ifndef PLAYER_H
# define PLAYER_H

/*
** ====-* INCLUDES *-====
*/

# include "vec3.h"

/*
** ====-* DEFINES *-====
*/

# define CAMERA_RIGHT		(1)
# define CAMERA_LEFT		(1 << 1)
# define CAMERA_FRONT		(1 << 2)
# define CAMERA_BACK		(1 << 3)

/*
** ====-* TYPEDEFS *-====
*/

typedef struct s_player		t_player;
typedef struct s_camera		t_camera;
typedef struct s_inventory	t_inventory;

/*
** ====-* STRUCTURES *-====
*/

struct						s_camera
{
	t_vec3d					origin;
	t_vec3d					direction;
	t_vec3d					rotation;
	t_vec3d					up;
	t_vec3d					right;
};

struct						s_inventory
{
	int						weapons;
	int						keys;
};

struct						s_player
{
	t_camera				camera;
	t_inventory				inventory;
};

#endif
