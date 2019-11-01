#ifndef MENUS_H
# define MENUS_H

/*
** ====-* INCLUDES *-====
*/

# include "graphic_lib.h"

/*
** ====-* DEFINES *-====
*/

# define DEF_BUTTON_W (WIDTH / 7)
# define DEF_BUTTON_H (HEIGHT / 12)
# define WIDTH_CENTER (WIDTH / 2)
# define HEIGHT_CENTER (HEIGHT / 2)
# define BUTTON_GAP_X (WIDTH / 12)
# define BUTTON_GAP_Y (HEIGHT / 36)

# define SET_BUTTON_W (WIDTH / 5)
# define SET_BUTTON_H (HEIGHT / 12)

# define NB_BUBBLE		125

/*
** ====-* TYPEDEFS *-====
*/

typedef struct s_doom	t_doom;
typedef struct s_point	t_point;
typedef struct s_button	t_button;
typedef struct s_img	t_img;
typedef struct s_start	t_start;

/*
** ====-* STRUCTURES *-====
*/

struct					s_start
{
	int					pos;
	int					speed;
	int					size;
	int					color;
};

struct					s_point
{
	int					x;
	int					y;
};

struct					s_button
{
	t_point				pos;
	t_point				dim;
	char				*title;
	long				state;
	long				select;
};

struct					s_img
{
	int					width;
	int					height;
	__uint32_t			*pixels;
};

/*
** ====-* PROTOTYPES *-====
*/

t_point					add_points(t_point a, t_point b);

void					create_buttons_inputs(t_doom *data, t_button *btab);

int						draw_rectangle(t_graphic_lib *lib, t_point position, t_point dimensions, int color);

int						put_buttons_on_img(t_doom *data, t_button *btab, int nbuttons);

void					put_buttons_names(t_doom *data, t_button *btab, SDL_Color color, int nbuttons);

t_button				button(t_point pos, t_point dim, long state, char *title);

t_point					point(int width, int height);

void					start_drawing_circle(t_doom *data, int i
	, unsigned int *image);

int						create_flame(t_doom *data, unsigned int *image);

#endif
