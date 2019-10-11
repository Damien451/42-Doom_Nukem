/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_add.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:42:58 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/02 13:44:50 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	queue_add(t_queue **last, t_queue *new)
{
	if (!last)
		return ;
	if (!*last)
		*last = new;
	else
		(*last)->next = new;
	(*last) = (*last)->next;
}
