/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_editor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:12:25 by roduquen          #+#    #+#             */
/*   Updated: 2019/10/27 20:13:38 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include "vec3.h"
#include "octree.h"

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
	static char		*str = "MAP_CREATOR";
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
	SDL_RenderPresent(data->lib.renderer);
	return (0);
}
