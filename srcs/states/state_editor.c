/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_editor.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 15:09:25 by roduquen          #+#    #+#             */
/*   Updated: 2020/03/02 12:50:12 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include <fcntl.h>
#include <unistd.h>
#include "vec3.h"
#include "octree.h"

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
	put_string_on_renderer(data, point(WIDTH / 3.9, HEIGHT / 1.018),
		label(info, (SDL_Color){0, 0, 0, 0}), data->lib.ptrfont[4]);
	free(str_step);
	return (0);
}

static void			set_quadrillage3(void *thread,
	t_doom *data, int k, double alpha)
{
	int			i;
	int			j;

	i = ((t_thread*)thread)->num;
	while (i < SIZE_MAP)
	{
		j = -1;
		while (++j < SIZE_MAP)
			if ((int)data->map_to_save[i][k][j] != 0)
				color_rectangle(data, (t_vec3l){i, j, 0}, k, alpha);
		i += NBR_THREAD;
	}
}

static void			*set_quadrillage2(void *thread)
{
	int			k;
	double		alpha;
	double		nbr;
	int			step;
	t_doom		*data;

	step = ((t_thread*)thread)->frame;
	data = ((t_thread*)thread)->data;
	nbr = 1.0;
	if (step > 0)
		nbr = (1.0 / ((double)step + 1)) < 0.1 ? 0.1
			: 1.0 / ((double)step + 1);
	k = step - data->lib.editor.alpha < -1 ? -1
		: step - data->lib.editor.alpha;
	alpha = (data->lib.editor.alpha == 10) ? nbr : 1;
	while (++k <= step)
	{
		set_quadrillage3(thread, data, k, alpha);
		alpha += nbr;
	}
	pthread_exit(0);
}

void				set_quadrillage(t_doom *data, int step)
{
	int			i;
	t_thread	thread[NBR_THREAD];

	i = 0;
	while (i < NBR_THREAD)
	{
		thread[i].num = i;
		thread[i].data = data;
		thread[i].frame = step;
		if (pthread_create(&thread[i].thread, NULL,
			(*set_quadrillage2), &thread[i]) < 0)
			return ;
		i++;
	}
	i = 0;
	while (i < NBR_THREAD)
		pthread_join(thread[i++].thread, NULL);
}

int					state_editor(t_doom *data)
{
	static int		first = 0;
	static int		step = 0;

	if (!first)
	{
		ft_memset(data->lib.image, 0, (HEIGHT * WIDTH) << 2);
		if (load_map(data, data->map_name) != 0)
			switch_state(data, EDITOR, EDITOR_MENU);
		init_editor(&data->lib.editor);
		first++;
	}
	loop_music(data->mix.sounds[2], 2);
	ft_memcpy(data->lib.image, data->lib.texture_editor[data->lib.editor.mode],
		(WIDTH * HEIGHT) << 2);
	set_quadrillage(data, step);
	while (SDL_PollEvent(&data->lib.event))
		editor_commands(data, data->map_name, &step, &first);
	show_selected_params(data);
	SDL_RenderCopy(data->lib.renderer, data->lib.texture, NULL, NULL);
	display_info(data, data->map_name, step);
	SDL_RenderPresent(data->lib.renderer);
	return (0);
}
