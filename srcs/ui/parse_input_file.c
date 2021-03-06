/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input_file.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:43:10 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/15 16:43:11 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "libft.h"
#include "inputs.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

static int	check_eof(int fd)
{
	char			c;

	if (read(fd, &c, 1))
		return (1);
	return (0);
}

static void	fill_tabinputs(t_doom *data, unsigned int tab[NB_MODIF_INPUTS])
{
	int				i;

	i = -1;
	while (++i < NB_MODIF_INPUTS)
		data->tabinputs.keycode[i] = tab[i];
}

static int	read_input_file(t_doom *data, int fd)
{
	int				nbinput;
	int				rd;
	unsigned char	buff[4 * NB_MODIF_INPUTS];
	unsigned int	tab[NB_MODIF_INPUTS];

	rd = -1;
	if (read(fd, buff, 4 * NB_MODIF_INPUTS) != 4 * NB_MODIF_INPUTS)
		return (1);
	if (check_eof(fd) == 1)
		return (1);
	while (++rd < NB_MODIF_INPUTS)
		tab[rd] = *((int*)&buff[rd * 4]);
	rd = -1;
	while (++rd < NB_MODIF_INPUTS)
	{
		nbinput = rd;
		while (++nbinput < NB_MODIF_INPUTS)
		{
			if (tab[rd] == tab[nbinput])
				return (1);
		}
	}
	fill_tabinputs(data, tab);
	return (0);
}

int			parse_input_file(t_doom *data, char *input_file)
{
	int		fd;

	if ((fd = open(input_file, O_RDONLY)) == -1)
		return (get_default_inputs(data));
	if ((read_input_file(data, fd)) != 0)
		return (get_default_inputs(data));
	close(fd);
	return (0);
}
