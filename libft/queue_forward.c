/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_forward.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:42:53 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/02 13:44:53 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void		queue_forward(t_queue **begin)
{
	t_queue		*next;

	if (!begin)
		return ;
	if (!*begin)
		return ;
	next = (*begin)->next;
	free(*begin);
	*begin = next;
}
