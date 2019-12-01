#ifndef DOOM_H
# define DOOM_H

/*
** ====-* INCLUDES *-====
*/

# include "graphic_lib.h"
# include "inputs.h"
# include "menus.h"
# include "mixer.h"
# include "player.h"
# include "vec3.h"

/*
** ====-* DEFINES *-====
*/

# define EPSILON			1e-5
# define FOV				(60.0 * M_PI / 180.0)
# define POV				(34 * M_PI / 180.0)

# define RUNNING			(1l << 62)
# define START				(1l)
# define PLAYING			(1l << 1)
# define PAUSE				(1l << 2)
# define MAIN_MENU			(1l << 3)
# define PLAY_MENU			(1l << 4)
# define EDITOR_MENU		(1l << 5)
# define EDITOR				(1l << 6)
# define GET_MAP_NAME		(1l << 7)
# define DELETE_MAP			(1l << 8)
# define SCORES				(1l << 9)
# define SETTINGS			(1l << 10)
# define SETTINGS_INPUTS	(1l << 11)
# define SETTINGS_SOUND		(1l << 12)
# define GET_INPUT			(1l << 13)
# define LEAVING			(1l << 14)

# define SUN				(1)
# define TORCH				(2)

# define SPAWNBLOCK			31

/*
** ====-* TYPEDEFS *-====
*/

typedef struct s_doom			t_doom;
typedef struct s_graphic_lib	t_graphic_lib;
typedef struct s_bubble			t_bubble;
typedef struct s_octree			t_octree;
typedef struct s_light			t_light;
typedef struct s_ray			t_ray;

/*
** ====-* STRUCTURES *-====
*/

struct						s_bubble
{
	int						pos;
	t_bubble				*next;
};

struct						s_light
{
	t_vec3d					position;
	char					type;
	t_light					*next;
};

struct						s_ray
{
	int						color;
	int						black;
	unsigned char			c_color[4];
	double					length;
	t_vec3d					intersect;
	t_vec3d					origin;
	t_vec3d					direction;
	int						face;
	t_octree				*node;
	t_vec3d					normal;
};

struct						s_doom
{
	t_graphic_lib			lib;
	t_player				player;
	t_tabinputs				tabinputs;
	t_start					tab[NB_BUBBLE];
	t_bubble				*bubble_list;
	t_bubble				*lightning_list;
	t_bubble				*lightning_list2;
	char					map_to_save[SIZE_MAP][SIZE_MAP][SIZE_MAP];
	char					*map_name;
	long					button;
	long					state;
	t_octree				*octree;
	int						load_page[2];
	double					sensitivity;
	t_mixer					*mix;
	int						sampling;
	int						map_to_show;
	int						(*check_intersect[6])(t_vec3d *, t_vec3d, t_ray *
								, t_octree **);
	int						(*add_texture[6])(t_vec3d, t_doom *);
	int						(*check_light_view[6])(t_vec3d, t_vec3d);
	t_light					*light;
	unsigned int			*octree_v2;
	int						ball;
	int						torch;
	t_vec3d					sun;
	char					photo;
	int						actual_i;
	int						actual_j;
	int						*samplingt[6];
};

/*
** ====-* PROGRAM *-====
*/

int							init_program(t_doom *data);
int							program(t_doom *data);
int							leave_program(t_doom *data, int type);
void						leave_state_game(t_vec3d *position);
void						load_textures(t_doom *data);
int							load_sounds(t_doom *data);
char						*get_map_name(int map_to_show);
int							count_maps(int *first);
void						free_octree(t_octree *node);

/*
** ====-* GRAPHICS *-====
*/

void						draw_block(t_doom *data, int x, int y, int step);
void						erase_block(t_doom *data, int x, int y, int step);
void						fill_step(t_doom *data, int step);
int							frame_calculator(void);
void						color_rectangle(t_doom *data, t_vec3l rectangle, int step, double alpha);
int							create_octree(t_doom *data);
void						pick_texture(t_doom *data, int x, int y);
void						reset_step(t_doom *data, int step);
int							raytracing(t_doom *data);
unsigned int				ray_intersect(t_ray ray, t_doom *data);
void						show_selected_params(t_doom *data);
int							check_x_intersect_neg(t_vec3d *intersect, t_vec3d origin
	, t_ray *ray, t_octree **node);
int							check_y_intersect_neg(t_vec3d *intersect, t_vec3d origin
	, t_ray *ray, t_octree **node);
int							check_z_intersect_neg(t_vec3d *intersect, t_vec3d origin
	, t_ray *ray, t_octree **node);
int							check_x_intersect_pos(t_vec3d *intersect, t_vec3d origin
	, t_ray *ray, t_octree **node);
int							check_y_intersect_pos(t_vec3d *intersect, t_vec3d origin
	, t_ray *ray, t_octree **node);
int							check_z_intersect_pos(t_vec3d *intersect, t_vec3d origin
	, t_ray *ray, t_octree **node);
unsigned int				add_skybox(t_vec3d intersect);
int							convert_to_ppm(unsigned int *view);
double						launch_ray_to_light(t_ray ray, t_light *light, t_doom *data);
void		max_absolute_between_three(double a, double b, double c, int tab[3]);
double		launch_ray_to_sun(t_ray ray, t_doom *data);
int							add_x_neg(t_vec3d intersect, t_doom *data);
int							add_y_neg(t_vec3d intersect, t_doom *data);
int							add_z_neg(t_vec3d intersect, t_doom *data);
int							add_x_pos(t_vec3d intersect, t_doom *data);
int							add_y_pos(t_vec3d intersect, t_doom *data);
int							add_z_pos(t_vec3d intersect, t_doom *data);
int			check_light_view_x_pos(t_vec3d position, t_vec3d light_pos);
int			check_light_view_x_neg(t_vec3d position, t_vec3d light_pos);
int			check_light_view_y_pos(t_vec3d position, t_vec3d light_pos);
int			check_light_view_y_neg(t_vec3d position, t_vec3d light_pos);
int			check_light_view_z_pos(t_vec3d position, t_vec3d light_pos);
int			check_light_view_z_neg(t_vec3d position, t_vec3d light_pos);
unsigned int				add_texture(t_vec3d intersect, int type, t_doom *data);

/*
** ====-* PHYSICS *-====
*/

int			check_player_clipping(t_vec3d *acceleration, t_vec3d *new_pos
	, char map[64][64][64], t_vec3d position);
int			check_camera_clipping(t_vec3d *acceleration, t_vec3d *new_pos
	, char map[64][64][64], t_vec3d position);
void		apply_motion(t_doom *data);

/*
** ====-* GAMEPLAY *-====
*/

/*
** ====-* COMMANDS *-====
*/

void						editor_commands(t_doom *data, char map_name[50], int *map, int *first);

int							check_map_validity(t_doom *data);

void						mouse_editor_commands(t_doom *data, int *ok, int *map, int button);

/*
** ====-* GAMESTATES *-====
*/

void						switch_state(t_doom *data, long actual_state, long new_state);

int							state_start(t_doom *data);

int							state_inputs_settings_menu(t_doom *data);

int							state_main_menu(t_doom *data);

int							state_play_menu(t_doom *data);

int							state_scoreboard(t_doom *data);

int							state_settings_menu(t_doom *data);

int							state_sound_settings(t_doom *data);

int							state_get_input(t_doom *data);

int							state_get_map_name(t_doom *data);

int							state_delete_map(t_doom *data);

int							state_editor(t_doom *data);

int							state_editor_menu(t_doom *data);

int							state_game(t_doom *data);

#endif
