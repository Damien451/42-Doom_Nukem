#include "entities.h"
#include "doom.h"
#include <math.h>

static double	distance(t_vec3d a, t_vec3d b)
{
	return (vec3d_length2(vec3d_sub(a, b)));
}


static t_vec3d	calculate_position(t_entity entity, t_camera camera)
{
	static double minmaxpos[4] = {0,0,0,0};
	t_vec3d dir;
	t_vec3d fr;
	t_vec3d up;
	t_vec3d rg;
	t_vec3d pos;
	double theta;
	double phi;
	double rgs;
	double ups;

	t_vec3d proj_rg;
	t_vec3d proj_up;

	fr = camera.direction;
	up = camera.up;
	rg = camera.right;

//	printf("up %f, %f, %f\n", up.x, up.y, up.z);
//	printf("rg %f, %f, %f\n\n", rg.x, rg.y, rg.z);

	dir = vec3d_sub(entity.pos, camera.origin);

	proj_rg = vec3d_unit(vec3d_sub(dir, vec3d_scalar(rg, vec3d_dot(dir, rg))));

	proj_up = vec3d_unit(vec3d_sub(dir, vec3d_scalar(up, vec3d_dot(dir, up))));

	// printf("dir = %f, %f, %f\n", dir.x, dir.y, dir.z);
	theta = acos(vec3d_dot(proj_rg, fr));
	phi = acos(vec3d_dot(proj_up, fr));
	// dir.x /= camera.origin.x;
	// dir.y /= camera.origin.y;
	// dir.z /= camera.origin.z;
	// printf("camera = %f, %f, %f\n", camera.origin.x, camera.origin.y, camera.origin.z);
	// printf("dir = %f, %f, %f\n", dir.x, dir.y, dir.z);
	// dir = vec3d_unit(dir);
	// printf("dir unit = %f, %f, %f\n", dir.x, dir.y, dir.z);
	// dir = vec3d_unit(dir);
	// phi = acos(vec3d_dot(vec3d_unit(vec3d(vec3d_dot(pos, fr), 0, vec3d_dot(pos, rg))), vec3d_unit(vec3d(fr.x, fr.y, fr.z))));

//	printf("phi = %f\n", phi);

	if (phi > FOV)
		return ((t_vec3d){-1,-1,-1});
	if (theta > POV)
	 	return ((t_vec3d){-1,-1,-1});
//	printf("theta = %f\n", theta);
//	printf("phi = %f\n", phi);
/*
	rgs = vec3d_dot(dir, rg);
	ups = vec3d_dot(dir, up);

	printf("ups = %f; rgs = %f\n", ups, rgs);

	if (rgs > 0)
		pos.x = WIDTH * phi / (FOV);
	else
		pos.x = -WIDTH * phi / (FOV);
	if (ups > 0)
		pos.y = HEIGHT * theta / (POV);
	else
		pos.y = -HEIGHT * theta / (POV);

*/
/*	printf("camera.origin %f, %f, %f\n", camera.origin.x, camera.origin.y, camera.origin.z);
	printf("entity.pos %f, %f, %f\n", entity.pos.x, entity.pos.y, entity.pos.z);
	printf("dir %f, %f, %f\n", dir.x, dir.y, dir.z);
	printf("fr %f, %f, %f\n", fr.x, fr.y, fr.z);
	printf("up %f, %f, %f\n", up.x, up.y, up.z);
	printf("rg %f, %f, %f\n\n", rg.x, rg.y, rg.z);
*/

	// pos = (t_vec3d){((dir.x * (rg.y * fr.z - rg.z * fr.y)
	// 					+ dir.y * (fr.x * rg.z - fr.z * rg.x)
	// 					+ dir.z * (rg.x * fr.y - rg.y * fr.x))),
	// 				(dir.x * (up.y * fr.z - up.z * fr.y)
	// 					+ dir.y * (fr.x * up.z - fr.z * up.x)
	// 					+ dir.z * (up.x * fr.y - up.y * fr.x)), 
	// 				((dir.x * (up.y * rg.z - rg.y * up.z)
	// 					+ dir.y * (rg.x * up.z - up.x * rg.z)
	// 					+ dir.z * (up.x * rg.y - rg.x * up.y)))};
	
//	printf("pos %f, %f, %f\n", pos.x, pos.y, pos.z);

	// if (pos.x < minmaxpos[0])
	// 	minmaxpos[0] = pos.x;
	// if (pos.x > minmaxpos[1])
	// 	minmaxpos[1] = pos.x;
	// if (pos.y < minmaxpos[2])
	// 	minmaxpos[2] = pos.y;
	// if (pos.y > minmaxpos[3])
	// 	minmaxpos[3] = pos.y;
	// printf("posx min %f posx max %f posy min %f posy max %f\n", minmaxpos[0], minmaxpos[1], minmaxpos[2], minmaxpos[3]);
	// pos = (t_vec3d){1,1,1};

	//pos = vec3d_unit(pos);

	// pos.x = (pos.x + 1) * 2 * WIDTH / M_PI;
	// pos.y = (pos.y + 1) * HEIGHT / M_PI;
	return (pos);
}

void		create_entity(t_entity **entities, t_vec3d pos, SDL_Surface *texture)
{
	t_entity *entity;

	if (!(entity = (t_entity*)ft_memalloc(sizeof(t_entity))))
		return ;
	entity->next = NULL;
	entity->pos = pos;
	entity->texture = texture;
	entity->id = 0;
	if (!*entities)
		*entities = entity;
	else
	{
		entity->id = (*entities)->id + 1;
		entity->next = *entities;
		*entities = entity;
	}
}

int			init_zbuf(t_zbuf *zbuf)
{
	if (!zbuf->zdist)
		if (!(zbuf->zdist = ft_memalloc(HEIGHT * WIDTH * sizeof(double))))
			return (0);
	if (zbuf->zdist)
		ft_memset(zbuf->zdist, 0, HEIGHT * WIDTH * sizeof(double));
	if (!zbuf->zcolor)
		if (!(zbuf->zcolor = ft_memalloc(HEIGHT * WIDTH * sizeof(int))))
			return (0);
	if (zbuf->zcolor)
		ft_memset(zbuf->zcolor, 0xff000000, HEIGHT * WIDTH * sizeof(int));
	return (1);

}

static void	place_in_zbuf(t_entity *entities, t_player player, t_zbuf *zbuf)
{
	double	dist;
	t_vec3d pos;
	int 	text_height;
	int		text_width;
	int 	x;
	int 	y;
	int		*img;


	img = (int*)entities->texture->pixels;
	dist = sqrt(distance(player.camera.origin, entities->pos));
	dist = 1;
	// printf("entity pos :%f %f %f \n player pos :%f %f %f\n dist :%lf\n", entities->pos.x, entities->pos.y, entities->pos.z, player.camera.origin.x, player.camera.origin.y, player.camera.origin.z, dist);
	text_height = entities->texture->h;
	text_width = entities->texture->w;
	pos = calculate_position(*entities, player.camera);

	if (pos.z > 0)
		return;
	//pos = (t_vec3d){text_width / 2, text_height / 2,0};
	//printf("%f, %f, %f\n", pos.x, pos.y, pos.z);
	x = pos.x - text_width / 2;
	// printf("x %d\n", x);
	while (x < pos.x + text_width / 2)
	{
		y = pos.y - text_height / 2 ;
		while (y < pos.y + text_height / 2)
		{
			if (x <= WIDTH && x >= 0 && y <= HEIGHT && y >= 0 && (dist < zbuf->zdist[x + y * WIDTH] || zbuf->zdist[x + y * WIDTH] == 0.0))
			{
				// printf("%d %d %f %f %d %d\n", x, y, x - pos.x + text_width / 2, y - pos.y + text_height / 2, text_width, text_height);
				zbuf->zdist[x + y * WIDTH] = dist,
				zbuf->zcolor[x + y * WIDTH] = img[(int)((int)(x - pos.x + text_width / 2) + (int)(y - pos.y + text_height / 2) * text_width)]; 
			}
			y++;
		}
		x++;
	}
	// int i = 0;
	// int j = 0;
	// while (i < text_width && i < WIDTH)
	// {
	// 	j = 0;
	// 	while (j < text_height)
	// 	{
	// 		if (j < HEIGHT)
	// 		{
	// 			zbuf->zdist[i + j * WIDTH] = 1;
	// 			zbuf->zcolor[i + j * WIDTH] = img[i + j * text_width];
	// 		}
	// 		j++;
	// 	}
	// 	i++;
	// }
}

void		z_buffer(t_entity *entities, t_player player, t_zbuf *zbuf)
{
	t_entity	*ptr;

	ptr = entities;
	ft_memset(zbuf->zdist, 0, HEIGHT * WIDTH * sizeof(double));
	ft_memset(zbuf->zcolor, 0xff000000, HEIGHT * WIDTH * sizeof(int));
	while (ptr)
	{
		place_in_zbuf(ptr, player, zbuf);
		ptr = ptr->next;
	}
}
