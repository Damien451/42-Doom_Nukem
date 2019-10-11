/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   btree_apply_by_level.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:38:38 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/02 14:32:19 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	full_queue(t_btree *root, t_queue *begin, int current_level)
{
	t_queue		*last;

	last = begin;
	while (begin)
	{
		while (begin && !begin->ptr)
		{
			if (begin->next && begin->pos == 1)
				begin->next->pos = 1;
			begin = begin->next;
		}
		if (!begin)
			break ;
		root = (t_btree*)begin->ptr;
		if (begin->pos == 1)
			current_level++;
		queue_add(&last, queue_new(root->left, current_level, begin->pos));
		queue_add(&last, queue_new(root->right, current_level, 0));
		begin = begin->next;
	}
}

void		btree_apply_by_level(t_btree *root, void (*applyf)(void *item
			, int current_level, int is_first))
{
	t_queue		*begin;

	if (!root)
		return ;
	begin = NULL;
	if (!(begin = queue_new(root, 0, 1)))
		return ;
	full_queue(root, begin, 0);
	while (begin)
	{
		if (begin->ptr)
		{
			root = (t_btree*)begin->ptr;
			(*applyf)(root->item, begin->size, begin->pos);
		}
		queue_forward(&begin);
	}
}
