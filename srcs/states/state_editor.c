/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_editor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:12:25 by roduquen          #+#    #+#             */
/*   Updated: 2019/10/29 16:06:45 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include "vec3.h"
#include "octree.h"

#include "stdio.h"

static inline int	display_info(t_doom *data, char *map_name, int step)
{
	char	info[70];
	char	*str_step;
	char	*is_valid;
	char	*tmp;

	ft_bzero(&info, 50);
	if (!(str_step = ft_itoa(step)))
		return (1);
	ft_strcat(ft_strcat(info, "Map : "), map_name);
	ft_strcat(ft_strcat(info, ", step : "), str_step);
	ft_strcat(info, is_valid = (check_map_validity(data) == 0 ?
		", Map Valid" : ", Map Invalid"));
	tmp = &info[0];
	printf("len info = %zu\n", ft_strlen(tmp));
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

	i = 0;
	while (i < SIZE_MAP)
	{
		j = 0;
		while (j < SIZE_MAP)
		{
			color_rectangle(data, (t_vec3l){i, j, 0}, step);
			j++;
		}
		i++;
	}
}

static inline int	parse_file(t_doom *data, char *str, int step)
{
	int		fd;
	int		ret;
	char	str_to_map[SIZE_MAP * SIZE_MAP * SIZE_MAP];

	if ((fd = open(str, O_RDONLY)) != -1)
	{
		ret = read(fd, str_to_map, SIZE_MAP * SIZE_MAP * SIZE_MAP);
		if (ret != SIZE_MAP * SIZE_MAP * SIZE_MAP)
		{
			close(fd);
			return (1);
		}
		ft_memcpy(data->map_to_save, str_to_map, SIZE_MAP * SIZE_MAP
			* SIZE_MAP);
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

void				aff_octree(t_octree *node, t_doom *data, int oct[3])
{
	int i;

	i = 0;
	while (i < 8)
	{
		if (node->child[i])
			aff_octree(node->child[i], data, oct);
		i++;
	}
	if (node->leaf == FULL)
		oct[0]++;
	else if (node->leaf == EMPTY)
		oct[1]++;
	else
		oct[2]++;
}

int					state_editor(t_doom *data)
{
	static int		first = 0;
	static int		map = 0;
	static char		*str = "dacuvill's really cool ' map";
	int				oct[3];

	oct[0] = 0;
	oct[1] = 0;
	oct[2] = 0;
	if (!first)
	{
		ft_memset(data->lib.image, 0, (HEIGHT * WIDTH) << 2);
		parse_file(data, str, map);
		create_octree(data);
		aff_octree(data->octree, data, oct);
		printf("empty = %d, full = %d, inside = %d, total = %d\n"
			, oct[1], oct[0], oct[2], oct[0] + oct[1] + oct[2]);
		data->lib.picked_texture = 0;
		first++;
	}
	ft_memcpy(data->lib.image, data->lib.editor_texture[data->editor_mode]->pixels
		, WIDTH * HEIGHT * 4);
	SDL_SetRelativeMouseMode(SDL_FALSE);
	SDL_ShowCursor(SDL_TRUE);
	set_quadrillage(data, map);
	while (SDL_PollEvent(&data->lib.event))
		editor_commands(data, str, &map, &first);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	display_info(data, str, map);
	SDL_RenderPresent(data->lib.renderer);
	return (0);
}
