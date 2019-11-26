#include "entity.h"

double		distance(t_vec2d a, t_vec2d b)
{
	return (vec3d_length2(vec3d_sub(a, b)));
}

// int			nb_entities(t_entity *entities)
// {
// 	int i;

// 	i = 0;
// 	while (entities)
// 	{
// 		entities = entities->next;
// 		i++;
// 	}
// 	return (i);
// }

void		calculate_position(t_vec2l *start, t_vec2l *size)
{
	
}

int init_zbuf(t_zbuf *zbuf)
{
	if (zbuf->zdist)
		ft_memset(zbuf->zdist, HEIGHT * WIDTH * sizeof(double), -1);
	if (!zbuf->zdist)
		if (!(zbuf->zdist = ft_memalloc(HEIGHT * WIDTH * sizeof(double))))	
			return (0);
	if (!zbuf->zcolor)
		if (!(zbuf->zcolor = ft_memalloc(HEIGHT * WIDTH * sizeof(int))))
			return (0);
	if (zbuf->zcolor)
		ft_memset(zbuf->zcolor, HEIGHT * WIDTH * sizeof(int), 0);
	return (1)
}

void	place_in_zbuf(t_entity *entities, t_player player, t_zbuf *zbuf)
{
	double dist;

	dist = distance(player.position, entities.pos);

}

t_zbuf		z_buffer(t_entity *entities, t_player player)
{
	t_zbuf		zbuf;
	t_entity	*ptr;

	if (!(init_zbuf(&zbuf)))
		return (zbuf);	
	ptr = entities;
	while (ptr)
	{
		place_in_zbuf(ptr, player);
		ptr = ptr->next;
	}
}