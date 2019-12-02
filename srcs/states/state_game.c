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


	int						k;
	char					destpath[70] = "/sgoinfre/goinfre/Perso/dacuvill/new_blocks_binaries/";
	char					full_destpath[100];
	char					originpath[60] = "/sgoinfre/goinfre/Perso/dacuvill/blocks_rgb_tmp/";
	char					full_originpath[80];

	k = -1;
	while (++k < NBR_TEXTURES_BLOCKS)
	{
		ft_bzero(full_originpath, 80);
		ft_bzero(full_destpath, 100);
		ft_strcat(ft_strcat(ft_strcat(full_originpath, originpath), ft_itoa(k)), ".rgb");
		ft_strcat(ft_strcat(ft_strcat(full_destpath, destpath), ft_itoa(k)), ".binary");
		tab[0] = 0;
		fd = open(full_originpath, O_RDONLY);
		read(fd, tabi, 128*128*3);
		close(fd);
		i = 0;
		while (i < 128)
		{
			j = 0;
			while (j < 128)
			{
				tab[0] = tabi[i * 128 * 3 + 3 * j + 2];
				tab[1] = tabi[i * 128 * 3 + 3 * j + 1];
				tab[2] = tabi[i * 128 * 3 + 3 * j];
				tab[3] = 0;
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
		printf("%s\n", full_destpath);
		write(i, tabl, 128*128*4);
		close(i);
		ok++;
		//}
	}
}

static void	set_player_spawn(char map[64][64][64], t_vec3d *position)
{
	int		x;
	int		y;
	int		z;

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
					position->x = z + 0.5;
					position->y = y + 1;
					position->z = x + 0.5;
				}
			}
		}
	}
}

int			state_game(t_doom *data)
{
	int	time = SDL_GetTicks();

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
//	printf("Time for computing physical motor = %d\n", SDL_GetTicks() - time);
	raytracing(data);
	if (data->photo)
	{
		data->photo = 0;
		convert_to_ppm(data->lib.image);
	}
//	skybox(data);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	SDL_RenderPresent(data->lib.renderer);
	SDL_RenderClear(data->lib.renderer);
	return (0);
}
