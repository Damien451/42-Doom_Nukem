
#include "doom.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include "vec3.h"
#include "octree.h"

#include <stdio.h>

static inline int	display_info(t_doom *data, char *str, int step)
{
	char	info[70];
	char	*str_step;
	char	*is_valid;
	char	*tmp;

	ft_bzero(&info, 50);
	if (!(str_step = ft_itoa(step)))
		return (1);
	ft_strcat(ft_strcat(info, "Map : "), str);
	ft_strcat(ft_strcat(info, ", step : "), str_step);
	ft_strcat(info, is_valid = (check_map_validity(data) == 0 ?
		", Map Valid" : ", Map Invalid"));
	tmp = &info[0];
	if (ft_strlen(tmp) > 57)
	{
		ft_bzero(&info[57], 13);
		info[57] = '.';
		info[58] = '.';
		info[59] = '.';
	}
	put_string_on_renderer(data, point(510, 1045),
		label(info, BLACK), data->lib.ptrfont[5]);
	free(str_step);
	return (0);
}

static inline void	set_quadrillage(t_doom *data, int step)
{
	int			i;
	int			j;
	int			k;
	double		alpha;
	double		nbr;

	nbr = 1.0;
	if (step > 0)
		nbr = (1.0 / ((double)step + 1)) < 0.1 ? 0.1 : 1.0 / ((double)step + 1);
	SDL_SetTextureBlendMode(data->lib.texture, SDL_BLENDMODE_BLEND);
	k = step - data->editor_alpha < -1 ? -1 : step - data->editor_alpha;
	alpha = nbr;
	while (++k <= step)
	{
		i = -1;
		while (++i < SIZE_MAP)
		{
			j = -1;
			while (++j < SIZE_MAP)
				color_rectangle(data, (t_vec3l){i, j, 0}, k, alpha);
		}
		alpha += nbr;
	}
	SDL_SetTextureBlendMode(data->lib.texture, SDL_BLENDMODE_NONE);
}

static inline int	parse_file(t_doom *data, char *str, int step)
{
	int		fd;
	int		ret;
	char	strtomap[SIZE_MAP * SIZE_MAP * SIZE_MAP];
	char	full_path[50];

	ft_bzero(full_path, 50);
	ft_strcat(ft_strcat(full_path, "./maps/"), str);
	if ((fd = open(full_path, O_RDONLY)) != -1)
	{
		ret = read(fd, strtomap, SIZE_MAP * SIZE_MAP * SIZE_MAP);
		if (ret != SIZE_MAP * SIZE_MAP * SIZE_MAP)
		{
			close(fd);
			return (1);
		}
		ft_memcpy(data->map_to_save, strtomap, SIZE_MAP * SIZE_MAP * SIZE_MAP);
		set_quadrillage(data, step);
		close(fd);
	}
	else
	{
		ft_memset(data->lib.image, 0, HEIGHT * WIDTH * 4);
		ft_memset(data->map_to_save, 0, SIZE_MAP * SIZE_MAP * SIZE_MAP);
	}
	return (0);
}

int					state_editor(t_doom *data)
{
	static int		first = 0;
	static int		step = 0;

	if (!first)
	{
		
		ft_memset(data->lib.image, 0, (HEIGHT * WIDTH) << 2);
		parse_file(data, data->map_name, step);
		data->lib.picked_texture = 0;
		first++;
	}
	ft_memcpy(data->lib.image,
		data->lib.editor_texture[data->editor_mode]->pixels,
		WIDTH * HEIGHT * 4);
	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_ShowCursor(SDL_TRUE);
	set_quadrillage(data, step);
	while (SDL_PollEvent(&data->lib.event))
		editor_commands(data, data->map_name, &step, &first);
	show_picked_texture(data);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	display_info(data, data->map_name, step);
	SDL_RenderPresent(data->lib.renderer);
	return (0);
}
