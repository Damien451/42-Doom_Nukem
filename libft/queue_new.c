/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue_new.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:43:04 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/02 13:44:56 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_queue		*queue_new(void *ptr, int size, int pos)
{
	t_queue	*new;

	if (!(new = (t_queue*)malloc(sizeof(t_queue))))
		return (NULL);
	ft_memset(new, 0, sizeof(t_queue));
	if (ptr)
		new->ptr = ptr;
	else
		new->ptr = NULL;
	new->size = size;
	new->pos = pos;
	return (new);
}
