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

# define CAMERA_TR_RIGHT	(1)
# define CAMERA_TR_LEFT		(1 << 1)
# define CAMERA_TR_FRONT	(1 << 2)
# define CAMERA_TR_BACK		(1 << 3)
# define COURSE				(1 << 4)
# define WATER				(1 << 5)
# define SQUAT				(1 << 6)
# define DESTROY			(1 << 7)

# define GRAVITY			1.0
# define ACCELERATION		(1.0 / 300.0)
# define MAX_SPEED			(1.0 / 20.0)

# define X_AXIS				(t_vec3d){1, 0, 0}
# define Y_AXIS				(t_vec3d){0, 1, 0}
# define Z_AXIS				(t_vec3d){0, 0, 1}
# define SENSITIVITY		(double)(M_PI / 90.0 / data->sensitivity)

/*
** ====-* TYPEDEFS *-====
*/

typedef struct s_player		t_player;
typedef struct s_camera		t_camera;
typedef struct s_inventory	t_inventory;
typedef struct s_doom		t_doom;

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
	double					x_angle;
};

struct						s_inventory
{
	int						weapons;
	int						keys;
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
	t_vec3d					position;
	t_vec3d					acceleration;
};

void						rotate_camera(t_camera *camera, t_vec3d rot_vec
	, double angle);

void			camera_mouse_motion(t_camera *camera, int *x, int *y
	, double *sensitivity);

void		camera_press_key(SDL_Event *event, t_doom *data);

void		camera_event_translate(t_doom *data);

#endif
