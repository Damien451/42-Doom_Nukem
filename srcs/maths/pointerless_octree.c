int				fill_node_type(t_octree *node, unsigned int *value)
{
	int			i;
	int			nbr_inside;

	i = 0;
	nbr_inside = 0;
	while (i < 8)
	{
		*value |= node->child[i]->leaf;
		if (node->child[i]->leaf == INSIDE)
			nbr_inside++;
		i++;
		if (i < 8)
			(*value) <<= 2;
	}
	(*value) |= 0xFFFF0000;
	return (nbr_inside);
}

int						create_octree_v2(t_doom *data)
{
	int				i;
	t_octree		*actual;
	t_queue			*queue;
	t_queue			*end;
	unsigned int	index;
	unsigned int	*octree_v2;
	int				j;
	unsigned		nbr_inside;
	int				k;

	octree_v2 = malloc(40 * strlen_of_octree_v2(data->octree));
	ft_memset(octree_v2, 0, 40 * strlen_of_octree_v2(data->octree));
	queue = queue_new(data->octree);
	end = queue;
	index = 0;
	i = 2;
	while (queue)
	{
		actual = (t_octree*)queue->ptr;
		nbr_inside = fill_node_type(actual, &octree_v2[index]);
		if (nbr_inside)
		{
			octree_v2[i++] = index++;
			octree_v2[index++] = i;
			j = 0;
			while (j < 8)
			{
				if (actual->child[j]->leaf == INSIDE)
				{
					i++;
					k = 0;
					while (k < 8)
					{
						if (actual->child[j]->child[k] && actual->child[j]->child[k]->leaf == INSIDE)
						{
							if (fill_node_type(actual->child[j]->child[k], &nbr_inside))
							{
								i++;
								break ;
							}
						}
						k++;
					}
				}
				j++;
			}
		}
		index++;
		j = 0;
		k = 1;
		while (j < 8)
		{
			if (actual->child[j]->leaf == INSIDE)
			{
				end->next = queue_new(actual->child[j]);
				end->next->prev = end;
				end = end->next;
			}
			j++;
		}
		queue = queue->next;
	}
	data->octree_v2 = octree_v2;
	printf("Pointerless bytes used = %d\n", i * 4);
	return (0);
}

