/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 13:08:35 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/24 21:16:32 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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
# include "entities.h"
# include "vec3.h"
# include "thread.h"
# include "mesh.h"
# include <pthread.h>
# include "weapons.h"

/*
** ====-* DEFINES *-====
*/

# define EPSILON			1e-5
# define FOV				1.047197551196598
# define POV				0.593411945678072

# define RUNNING			1
# define START				0
# define PLAYING			1
# define PAUSE				2
# define DEATH				3
# define MAIN_MENU			4
# define PLAY_MENU			5
# define PLAY_EDIT_MAP		6
# define EDITOR_MENU		7
# define EDITOR				8
# define GET_MAP_NAME		9
# define DELETE_MAP			10
# define SCORES				11
# define SETTINGS			12
# define SETTINGS_INPUTS	13
# define SETTINGS_SOUND		14
# define TEST_MODE			15
# define GET_INPUT			16
# define LEAVING			17

# define SUN				0
# define PLAYER				1
# define TORCH				2
# define TORCH2				3
# define TORCH3				4
# define TORCH4				5

# define SPAWNBLOCK			31

# define X_MIN				0
# define X_MAX				1
# define Y_MIN				2
# define Y_MAX				3
# define Z_MIN				4
# define Z_MAX				5
# define Y_MID				6

# define PLAYERS_SCOREBOARD	10

/*
** ====-* TYPEDEFS *-====
*/

typedef struct s_doom			t_doom;
typedef struct s_graphic_lib	t_graphic_lib;
typedef struct s_bubble			t_bubble;
typedef struct s_octree			t_octree;
typedef struct s_light			t_light;
typedef struct s_ray			t_ray;
typedef struct s_scoreboard		t_scoreboard;
typedef struct s_thread			t_thread;

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
	t_light					*next;
	int						type;
};

struct						s_scoreboard
{
	char					playertags[PLAYERS_SCOREBOARD][15];
	int						scores[PLAYERS_SCOREBOARD];
};

struct						s_ray
{
	t_vec3d					normal;
	t_vec3d					intersect;
	t_vec3d					origin;
	t_vec3d					direction;
	t_octree				*node;
	t_octree				*(*find_parent[3])(t_vec3d, t_octree *, t_vec3d);
	int						color;
	int						black;
	unsigned char			c_color[4];
	double					length;
	int						face;
	int						pos[2];
};

struct						s_thread
{
	t_ray					ray;
	pthread_t				thread;
	pthread_mutex_t			*mutex;
	pthread_mutex_t			*game;
	t_octree				*(*find_parent[3])(t_vec3d, t_octree*, t_vec3d);
	int						num;
	unsigned int			*image;
	int						total_frame;
	int						frame;
	t_doom					*data;
	t_vec3l					rectangle;
	double					alpha;
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
	t_scoreboard			scoreboard;
	char					map_to_save[SIZE_MAP][SIZE_MAP][SIZE_MAP];
	char					*map_name;
	unsigned int			**skybox;
	long					button;
	long					state;
	int						running;
	int						(*state_f[18])(t_doom *);
	t_octree				*octree;
	t_octree				*octree_model;
	int						load_page[2];
	double					sensitivity;
	t_mixer					*mix;
	int						sampling;
	int						map_to_show;
	int						(*check_intersect[6])(t_vec3d *, t_vec3d, t_ray *
								, t_octree **);
	int						(*add_texture[6])(t_vec3d, const t_doom *const);
	int						(*check_light_view[6])(t_vec3d, t_vec3d);
	t_light					*light;
	int						ball;
	int						torch;
	t_vec3d					sun;
	t_light					*sun_light;
	t_light					*player_light;
	double					power[6];
	char					photo;
	int						actual_i;
	int						actual_j;
	int						*samplingt[7];
	t_vec3d					normal[6];
	t_octree				*(*find_parent[3])(t_vec3d, t_octree *, t_vec3d);
	t_thread				thread[NBR_THREAD];
	pthread_mutex_t			mutex;
	t_zbuf					zbuf;
	t_entity				*entities;
	t_light					light_array[64][64][64];
	unsigned int			fire_model[64][64][64];
	int						tmp;
	double					*z_buffer;
	unsigned int			*frame_buffer;
	t_mesh					*meshes;
};

/*
** ====-* PROGRAM *-====
*/

int							init_program(t_doom *data);
void						init_game(t_doom *data, t_player *player);
int							program(t_doom *data);
int							leave_program(t_doom *data, int type);
void						leave_game(t_doom *data, t_player *player);
void						load_textures(t_doom *data);
int							load_sounds(t_doom *data);
char						*get_map_name(int map_to_show);
int							count_maps(int *first);
void						free_octree(t_octree *node);
int							parse_scores_file(t_doom *data, int *first);

/*
** ====-* GRAPHICS *-====
*/

void						bresenham(unsigned int *image, t_vec3l circle, int color);
void						draw_block(t_doom *data, int x, int y, int step);
void						erase_block(t_doom *data, int x, int y, int step);
void						fill_step(t_doom *data, int step);
int							frame_calculator(void);
void						copy_step(t_doom *data, int step);
void						color_rectangle(t_doom *data, t_vec3l rectangle
	, int step, double alpha);
int							create_octree(t_doom *data);
void						pick_element(t_doom *data, int x, int y);
void						pick_texture(t_doom *data, int x, int y);
void						reset_step(t_doom *data, int step);
int							raytracing(t_doom *data);
unsigned int				ray_intersect(t_ray ray, const t_doom *const data);
void						remove_type_block(t_doom *data);
void						replace_blocks(t_doom *data);
void						show_selected_params(t_doom *data);
unsigned int				add_skybox(t_vec3d intersect
	, unsigned int *skybox[6]);
int							convert_to_ppm(unsigned int *view);
double						launch_ray_to_light(t_ray ray, t_light *light
	, const t_doom *const data);
void						max_absolute_between_three(t_vec3d vec, int tab[3]);
double						launch_ray_to_sun(t_ray ray
	, const t_doom *const data);
int							create_light_array(t_doom *data);

/*
** ====-* RAYTRACER *-====
*/

t_octree					*find_node_to_go_neighboor(t_vec3d position
		, t_octree *node);
int							check_light_view_x_pos(t_vec3d position
		, t_vec3d light_pos);
int							check_light_view_x_neg(t_vec3d position
		, t_vec3d light_pos);
int							check_light_view_y_pos(t_vec3d position
		, t_vec3d light_pos);
int							check_light_view_y_neg(t_vec3d position
		, t_vec3d light_pos);
int							check_light_view_z_pos(t_vec3d position
		, t_vec3d light_pos);
int							check_light_view_z_neg(t_vec3d position
		, t_vec3d light_pos);
int							add_x_neg(t_vec3d intersect
		, const t_doom *const data);
int							add_y_neg(t_vec3d intersect
		, const t_doom *const data);
int							add_z_neg(t_vec3d intersect
		, const t_doom *const data);
int							add_x_pos(t_vec3d intersect
		, const t_doom *const data);
int							add_y_pos(t_vec3d intersect
		, const t_doom *const data);
int							add_z_pos(t_vec3d intersect
		, const t_doom *const data);
int							check_x_intersect_neg(t_vec3d *intersect
		, t_vec3d origin, t_ray *ray, t_octree **node);
int							check_y_intersect_neg(t_vec3d *intersect
		, t_vec3d origin, t_ray *ray, t_octree **node);
int							check_z_intersect_neg(t_vec3d *intersect
		, t_vec3d origin, t_ray *ray, t_octree **node);
int							check_x_intersect_pos(t_vec3d *intersect
		, t_vec3d origin, t_ray *ray, t_octree **node);
int							check_y_intersect_pos(t_vec3d *intersect
		, t_vec3d origin, t_ray *ray, t_octree **node);
int							check_z_intersect_pos(t_vec3d *intersect
		, t_vec3d origin, t_ray *ray, t_octree **node);
unsigned int				fill_percent_128(double a, double b
		, unsigned int tab[128 * 128]);
t_octree					*find_parent_x(t_vec3d position, t_octree *node
		, t_vec3d origin);
t_octree					*find_parent_y(t_vec3d position, t_octree *node
		, t_vec3d origin);
t_octree					*find_parent_z(t_vec3d position, t_octree *node
		, t_vec3d origin);
void						*launch_rays(void *ptr);
void						*launch_rays2(void *ptr);
void						sun(t_doom *data);
unsigned int				print_octree(t_vec3d intersect);
int							create_octree_model(t_doom *data);
void						init_func_pointer(t_doom *data);

/*
** ====-* PHYSICS *-====
*/

void						apply_motion(t_doom *data);
void			check_y_max(t_doom *data, t_vec3d *accel, t_vec3d hitbox[2]);
void			check_y_min(t_doom *data, t_vec3d *accel, t_vec3d hitbox[2]);
void			check_x_max(t_doom *data, t_vec3d *accel, t_vec3d hitbox[2]);
void			check_x_min(t_doom *data, t_vec3d *accel, t_vec3d hitbox[2]);
void			check_z_max(t_doom *data, t_vec3d *accel, t_vec3d hitbox[2]);
void			check_z_min(t_doom *data, t_vec3d *accel, t_vec3d hitbox[2]);

/*
** ====-* GAMEPLAY *-====
*/

/*
** ====-* COMMANDS *-====
*/

void						editor_commands(t_doom *data, char map_name[50]
	, int *step, int *first);

int							check_map_validity(t_doom *data);

void						mouse_editor_commands(t_doom *data, int *step);

/*
** ====-* GAMESTATES *-====
*/

void						switch_state(t_doom *data, long actual_state
	, long new_state);

int							state_start(t_doom *data);

int							state_inputs_settings_menu(t_doom *data);

int							state_main_menu(t_doom *data);

int							state_pause(t_doom *data);

int							state_play_menu(t_doom *data);

int							state_play_edit_map(t_doom *data);

int							state_scoreboard(t_doom *data);

int							state_settings_menu(t_doom *data);

int							state_sound_settings(t_doom *data);

int							state_test_mode(t_doom *data);

int							state_get_input(t_doom *data);

int							state_get_map_name(t_doom *data);

int							state_delete_map(t_doom *data);

int							state_editor(t_doom *data);

int							state_editor_menu(t_doom *data);

int							state_game(t_doom *data);

int							state_death(t_doom *data);

double						hit_sphere(t_ray *ray, const t_doom *const data);

double						hit_cylinder(t_ray *ray, const t_doom *const data);

double						hit_plane(t_ray *ray, const t_doom *const data);

#endif
