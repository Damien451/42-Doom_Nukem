#include "doom.h"
#include "player.h"
#include <SDL.h>
#include "graphic_lib.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include "octree.h"
/*
x = 0  z = 1
x = 1  z = 0
x = 0  z = -1
z = -1 z = 0

il y a 512 pixels entre 2 etats.

if (x == 0 && z == 1)
{
	start = 0;
	texture = NORTH;
}
else if (x == 1 && z == 0)
{
	start = 0;
	texture = EAST;
}
else if (x == 0 && z == -1)
{
	start = 0;
	texture = SOUTH;
}
else if (x == -1 && z == 0)
{
	start = 0;
	texture = WEST;
}

M_PI / 6 = 30 degres;
*/

/*void		skybox(t_doom *data)
{
	int			ret;
	t_vec3d		vec;

	vec = data->player.camera.direction;
	ret = max_absolute_between_three(vec.x, vec.y, vec.z);
	if (ret == 1)
	{
		if (vec.x > 0)
	}
}
*/

void		skybox(t_doom *data)
{
	int			i;
	int			j;
	unsigned char	*test;
	int			w;
	int			h;
	unsigned int			format;
	unsigned char			tab[4];
	static unsigned int		tabl[512 * 512];
	static int				ok = 0;
	int						fd;

	tab[0] = 0;
/*	if (!ok)
	{
	fd = open("test.binary", O_RDONLY);
	read(fd, tabl, 512*512*4);
	ok++;
	}*/
	SDL_QueryTexture(data->lib.skybox_t[0], &format, NULL, &w, &h);
	//printf("format = %u, w = %d, h = %d\n", format, w, h);
	//printf("test   = %u\n", SDL_PIXELFORMAT_ARGB8888);
	printf("data->lib.textures[33]->pitch = %d\n", data->lib.textures[33]->pitch);
	SDL_LockTexture(data->lib.skybox_t[0], NULL, (void**)&test, &i);
	i = 0;
	while (i < 512)
	{
		j = 0;
		while (j < 512)
		{
			tab[0] = ((unsigned char *)data->lib.textures[33]->pixels)[i * data->lib.textures[33]->pitch + j * 4];
			tab[1] = ((unsigned char *)data->lib.textures[33]->pixels)[i * data->lib.textures[33]->pitch + j * 4];
			tab[2] = ((unsigned char *)data->lib.textures[33]->pixels)[i * data->lib.textures[33]->pitch + j * 4];
			tab[3] = ((unsigned char *)data->lib.textures[33]->pixels)[i * data->lib.textures[33]->pitch + j * 4];
			tabl[i * 512 + j] = *((unsigned int *)&tab);
			data->lib.image[i * WIDTH + j] = *((unsigned int*)&tab);
			data->lib.image[i * WIDTH + j] = tabl[i * 512 + j];
			j++;
		}
		i++;
	}
	SDL_UnlockTexture(data->lib.skybox_t[0]);
	if (!ok)
	{
		i = open("texture0.binary", O_TRUNC | O_WRONLY | O_CREAT, 0777);
		write(i, tabl, 512*512*4);
		ok++;
	}
}

static inline t_octree	*on_x_higher_than_middle(t_vec3d *position
	, t_octree *node)
{
	if (position->y < (double)(node->center.y >> 1))
	{
		if (position->z < (double)(node->center.z >> 1))
			return (node->child[1]);
		else
			return (node->child[5]);
	}
	else
	{
		if (position->z < (double)(node->center.z >> 1))
			return (node->child[3]);
		else
			return (node->child[7]);
	}
}

static inline t_octree	*on_x_lower_than_middle(t_vec3d *position
		, t_octree *node)
{
	if (position->y < (double)(node->center.y >> 1))
	{
		if (position->z < (double)(node->center.z >> 1))
			return (node->child[0]);
		else
			return (node->child[4]);
	}
	else
	{
		if (position->z < (double)(node->center.z >> 1))
			return (node->child[2]);
		else
			return (node->child[6]);
	}
}

static t_octree				*find_position(t_vec3d *position, t_octree *node)
{
	while (node->leaf != EMPTY)
	{
		if (node->leaf == INSIDE)
		{
			if (position->x < (double)(node->center.x >> 1))
				node = on_x_lower_than_middle(position, node);
			else
				node = on_x_higher_than_middle(position, node);
		}
	}
	return (node);
}

void			interaction(t_doom *data)
{
	t_octree	*node;
	t_vec3d		intersect;
	int			ret;

	node = find_position(&data->player.position, data->octree);
	ret = check_x_intersect(&intersect, data->player.position, data->player.camera.direction, &node);
	if (ret < 0 && node->leaf == BREAKABLE)
	{
		node->leaf = EMPTY;
		data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
		return ;
	}
	else if (ret == 3)
	{
		ret = check_x_intersect(&intersect, intersect, data->player.camera.direction, &node);
		if (ret < 0 && node->leaf == BREAKABLE)
		{
			node->leaf = EMPTY;
			data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
			return ;
		}
		ret = check_y_intersect(&intersect, data->player.position, data->player.camera.direction, &node);
		if (ret < 0 && node->leaf == BREAKABLE)
		{
			node->leaf = EMPTY;
			data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
			return ;
		}
		ret = check_z_intersect(&intersect, data->player.position, data->player.camera.direction, &node);
		if (ret < 0 && node->leaf == BREAKABLE)
		{
			node->leaf = EMPTY;
			data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
			return ;
		}
	}
	ret = check_y_intersect(&intersect, data->player.position, data->player.camera.direction, &node);
	if (ret < 0 && node->leaf == BREAKABLE)
	{
		node->leaf = EMPTY;
		data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
		return ;
	}
	else if (ret == 3)
	{
		ret = check_x_intersect(&intersect, intersect, data->player.camera.direction, &node);
		if (ret < 0 && node->leaf == BREAKABLE)
		{
			node->leaf = EMPTY;
			data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
			return ;
		}
		ret = check_y_intersect(&intersect, data->player.position, data->player.camera.direction, &node);
		if (ret < 0 && node->leaf == BREAKABLE)
		{
			node->leaf = EMPTY;
			data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
			return ;
		}
		ret = check_z_intersect(&intersect, data->player.position, data->player.camera.direction, &node);
		if (ret < 0 && node->leaf == BREAKABLE)
		{
			node->leaf = EMPTY;
			data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
			return ;
		}
	}
	ret = check_z_intersect(&intersect, data->player.position, data->player.camera.direction, &node);
	if (ret < 0 && node->leaf == BREAKABLE)
	{
		node->leaf = EMPTY;
		data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
		return ;
	}
	else if (ret == 3)
	{
		ret = check_x_intersect(&intersect, intersect, data->player.camera.direction, &node);
		if (ret < 0 && node->leaf == BREAKABLE)
		{
			node->leaf = EMPTY;
			data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
			return ;
		}
		ret = check_y_intersect(&intersect, data->player.position, data->player.camera.direction, &node);
		if (ret < 0 && node->leaf == BREAKABLE)
		{
			node->leaf = EMPTY;
			data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
			return ;
		}
		ret = check_z_intersect(&intersect, data->player.position, data->player.camera.direction, &node);
		if (ret < 0 && node->leaf == BREAKABLE)
		{
			node->leaf = EMPTY;
			data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
			return ;
		}
	}
}

int			state_game(t_doom *data)
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN && data->lib.event.key.keysym.sym == SDLK_ESCAPE)
			switch_state(data, PLAYING, MAIN_MENU);
		else if (data->lib.event.type == SDL_MOUSEMOTION)
			camera_mouse_motion(&data->player.camera
					, &data->lib.event.motion.xrel, &data->lib.event.motion.yrel
					, &data->player.sensitivity);
		else if (data->lib.event.type == SDL_MOUSEBUTTONDOWN)
			data->lib.cam_keys |= DESTROY;
		else if (data->lib.event.type == SDL_MOUSEBUTTONUP)
			data->lib.cam_keys &= ~DESTROY;
		camera_press_key(&data->lib.event, data);
	}
	if (data->lib.cam_keys & DESTROY)
		interaction(data);
	camera_event_translate(data);
	//	printf("Direction vector = (%.2f|%.2f|%.2f)\n    position = (%.2f|%.2f|%.2f)\n", data->player.camera.direction.x, data->player.camera.direction.y, data->player.camera.direction.z, data->player.camera.origin.x, data->player.camera.origin.y, data->player.camera.origin.z);
	//	if (data->lib.cam_keys & WATER)
	//		printf("water");
	//	printf("\n");
	ft_memcpy(data->lib.image, data->lib.hud_texture->pixels, (WIDTH * HEIGHT) << 2);
	raytracing(data);
	skybox(data);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	SDL_RenderPresent(data->lib.renderer);
	return (0);
}
