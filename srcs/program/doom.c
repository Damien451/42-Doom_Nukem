/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   doom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 13:46:03 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/21 16:28:24 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <SDL.h>
#include "libft.h"
#include "doom.h"

static int	display_errors(int type)
{
	if (type == 0)
		ft_putendl_fd("Initialization error", 2);
	return (0);
}

int			main(void)
{
	t_doom	*data;

	data = malloc(sizeof(t_doom));
	ft_memset(data, 0, sizeof(t_doom));
	if (init_program(data))
		return (display_errors(0));
	program(data);
	leave_program(data, 0);
	return (0);
}
