#ifndef GRAPHIC_LIB_H
# define GRAPHIC_LIB_H

/*
** ====-* INCLUDES *-====
*/

# include <SDL.h>
# include <SDL_ttf.h>

/*
** ====-* DEFINES *-====
*/

# define WIDTH					1920
# define HEIGHT					1080

# define NBR_FONTS				6

# define WHITE					(SDL_Color){255, 255, 255, 0}
# define BLACK					(SDL_Color){0, 0, 0, 0}
# define RED					(SDL_Color){255, 0, 0, 0}
# define BLUE					(SDL_Color){0, 0, 255, 0}
# define GREEN					(SDL_Color){0, 255, 0, 0}
# define YELLOW					(SDL_Color){255, 255, 0, 0}

/*
** ====-* TYPEDEFS *-====
*/

typedef struct s_graphic_lib	t_graphic_lib;
typedef struct s_doom			t_doom;
typedef struct s_format			t_format;
typedef struct s_text			t_text;
typedef struct s_label			t_label;
typedef struct s_point			t_point;

/*
** ====-* STRUCTURES *-====
*/

struct							s_label
{
	char						*str;
	SDL_Color					color;
};

struct							s_format
{
	int							height;
	int							width;
};

struct							s_text
{
	Uint32						format;
	int							access;
	int							w;
	int							h;
};

struct							s_graphic_lib
{
	SDL_Texture					*texture;
	SDL_Surface					*start_bg;
	SDL_Window					*window;
	SDL_Renderer				*renderer;
	SDL_Surface					*surface;
	SDL_Event					event;
	t_format					format;
	t_text						text;
	TTF_Font					*ptrfont[NBR_FONTS];
	unsigned int				*image;
};

/*
** ====-* PROTOTYPES *-====
*/

t_label		label(char *str, SDL_Color color);

void		put_string_on_renderer(t_doom *data, t_point pos, t_label label, TTF_Font *font);

#endif
