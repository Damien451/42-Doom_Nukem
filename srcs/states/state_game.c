#include "doom.h"
#include "player.h"
#include <SDL.h>
#include "graphic_lib.h"
#include "libft.h"
#include <unistd.h>
#include <fcntl.h>
#include "octree.h"

void		skybox(t_doom *data)
{
	int			i;
	int			j;
//	unsigned int			format;
	unsigned char			tab[4];
	static unsigned char	tabi[3 * 256 * 256];
	static unsigned int		tabl[256 * 256];
	static int				ok = 0;
	int						fd;


	int 					k;
	char					destpath[70] = "/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/";
	char					full_destpath[100];
	char					originpath[60] = "/sgoinfre/goinfre/Perso/dacuvill/blocks_rgb_tmp2/";
	char					full_originpath[70];

	k = -1;
	while (++k < NBR_TEXTURES_BLOCKS)
	{
		ft_bzero(full_originpath, 70);
		ft_bzero(full_destpath, 100);
		ft_strcat(ft_strcat(full_originpath, originpath), ft_itoa(k));
		ft_strcat(ft_strcat(ft_strcat(full_destpath, destpath), ft_itoa(k)), ".binary");
		tab[0] = 0;
		/*if (ok )
		{*/
			fd = open(full_originpath, O_RDONLY);
			read(fd, tabi, 128*128*3);
			close(fd);
		//}
		//	printf("pitch   = %u\n", data->lib.textures[0]->pitch);
		i = 0;
		while (i < 128)
		{
			j = 0;
			while (j < 128)
			{
				tab[3] = 0;
				tab[1] = tabi[i * 128 * 3 + 3 * j];
				tab[2] = tabi[i * 128 * 3 + 3 * j + 1];
				tab[0] = tabi[i * 128 * 3 + 3 * j + 2];
				tabl[i * 128 + j] = *((unsigned int *)&tab);
				data->lib.image[i * WIDTH + j] = *((unsigned int*)&tab);
				data->lib.image[i * WIDTH + j] = tabl[i * 128 + j];
				j++;
			}
			i++;
		}
		//if (!ok)
		//{
			i = open(full_destpath, O_TRUNC | O_WRONLY | O_CREAT, 0777);
			write(i, tabi, 128*128*4);
			close(i);
			ok++;
		//}
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

/*void			interaction(t_doom *data)
{
	t_octree	*node;
	t_vec3d		intersect;
	int			ret;

	node = find_position(&data->player.camera.origin, data->octree);
	ret = check_x_intersect(&intersect, data->player.camera.origin, data->player.camera.direction, &node);
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
		ret = check_y_intersect(&intersect, data->player.camera.origin, data->player.camera.direction, &node);
		if (ret < 0 && node->leaf == BREAKABLE)
		{
			node->leaf = EMPTY;
			data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
			return ;
		}
		ret = check_z_intersect(&intersect, data->player.camera.origin, data->player.camera.direction, &node);
		if (ret < 0 && node->leaf == BREAKABLE)
		{
			node->leaf = EMPTY;
			data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
			return ;
		}
	}
	ret = check_y_intersect(&intersect, data->player.camera.origin, data->player.camera.direction, &node);
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
		ret = check_y_intersect(&intersect, data->player.camera.origin, data->player.camera.direction, &node);
		if (ret < 0 && node->leaf == BREAKABLE)
		{
			node->leaf = EMPTY;
			data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
			return ;
		}
		ret = check_z_intersect(&intersect, data->player.camera.origin, data->player.camera.direction, &node);
		if (ret < 0 && node->leaf == BREAKABLE)
		{
			node->leaf = EMPTY;
			data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
			return ;
		}
	}
	ret = check_z_intersect(&intersect, data->player.camera.origin, data->player.camera.direction, &node);
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
		ret = check_y_intersect(&intersect, data->player.camera.origin, data->player.camera.direction, &node);
		if (ret < 0 && node->leaf == BREAKABLE)
		{
			node->leaf = EMPTY;
			data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
			return ;
		}
		ret = check_z_intersect(&intersect, data->player.camera.origin, data->player.camera.direction, &node);
		if (ret < 0 && node->leaf == BREAKABLE)
		{
			node->leaf = EMPTY;
			data->map_to_save[node->center.x >> 1][node->center.y >> 1][node->center.z >> 1] = 0;
			return ;
		}
	}
}*/

#include <stdio.h>

static void	set_player_spawn(char map[64][64][64], t_vec3d *position)
{
	int		x;
	int		y;
	int		z;

	printf("yo\n");
	z = -1;
	while (++z < 63)
	{
		y = -1;
		while (++y < 63)
		{
			x = -1;
			while (++x < 63)
			{
				if (map[z][y][x] == SPAWNBLOCK)
				{
					position->x = z;
					position->y = y + 1;
					position->z = x;
				}
			}
		}
	}
}

int			state_game(t_doom *data)
{
	SDL_SetRelativeMouseMode(SDL_TRUE);
	if (data->player.position.x == -1 && data->player.position.y == -1 &&
		data->player.position.z == -1)
		set_player_spawn(data->map_to_save, &data->player.position);
	while (SDL_PollEvent(&data->lib.event))
	{
		if (data->lib.event.type == SDL_KEYDOWN && data->lib.event.key.keysym.sym == SDLK_ESCAPE)
		{
			leave_state_game(&data->player.position);
			switch_state(data, PLAYING, MAIN_MENU);
			return (0);
		}
		else if (data->lib.event.type == SDL_MOUSEMOTION)
			camera_mouse_motion(&data->player.camera
					, &data->lib.event.motion.xrel, &data->lib.event.motion.yrel
					, &data->player.sensitivity);
		else if (data->lib.event.type == SDL_MOUSEBUTTONDOWN)
		{
			data->ball = 1;
			data->lib.cam_keys |= DESTROY;
		}
		else if (data->lib.event.type == SDL_MOUSEBUTTONUP)
			data->lib.cam_keys &= ~DESTROY;
		camera_press_key(&data->lib.event, data);
	}
//	if (data->lib.cam_keys & DESTROY)
//		interaction(data);
	camera_event_translate(data);
	ft_memcpy(data->lib.image, data->lib.hud_texture->pixels, (WIDTH * HEIGHT) << 2);
	raytracing(data);
	if (data->photo)
	{
		data->photo = 0;
		convert_to_ppm(data->lib.image);
	}
	//skybox(data);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	SDL_RenderPresent(data->lib.renderer);
	return (0);
}
