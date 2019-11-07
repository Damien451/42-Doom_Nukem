
#include "doom.h"
#include "libft.h"
#include "graphic_lib.h"
#include "player.h"
#include "thread.h"
#include "octree.h"
#include "vec3.h"
#include <pthread.h>
#include <math.h>
#include <fcntl.h>
#include <unistd.h>

static inline unsigned int	fill_percent(double a, double b, int size
	, unsigned int tab[512 * 512])
{
	double			percent[2];
	int				coord[2];

	percent[0] = a * size;
	percent[1] = b * size;
	coord[0] = percent[0];
	coord[0] *= size;
	coord[1] = percent[1];
	return (tab[coord[0] + coord[1]]);
}

unsigned int				add_skybox(t_vec3d intersect)
{
	int					fd;
	static unsigned int	tabl[6][512 * 512];

	if (tabl[0][0] == 0)
	{
		fd = open("test.binary", O_RDONLY);
		read(fd, tabl[0], 512 * 512 * 4);
		close(fd);
		fd = open("test2.binary", O_RDONLY);
		read(fd, tabl[1], 512 * 512 * 4);
		close(fd);
		fd = open("test3.binary", O_RDONLY);
		read(fd, tabl[2], 512 * 512 * 4);
		close(fd);
		fd = open("test4.binary", O_RDONLY);
		read(fd, tabl[3], 512 * 512 * 4);
		close(fd);
		fd = open("test5.binary", O_RDONLY);
		read(fd, tabl[4], 512 * 512 * 4);
		close(fd);
		fd = open("test6.binary", O_RDONLY);
		read(fd, tabl[5], 512 * 512 * 4);
		close(fd);
	}
	if (intersect.x == 64.0)
		return (fill_percent((64.0 - intersect.y) / 64.0, intersect.z / 64.0, 512, tabl[0]));
	else if (intersect.x == 0.0)
		return (fill_percent((64.0 - intersect.y) / 64.0, (64.0 - intersect.z) / 64.0, 512, tabl[2]));
	else if (intersect.y == 64.0)
		return (fill_percent(intersect.x / 64.0, intersect.z / 64.0, 512, tabl[4]));
	else if (intersect.y == 0.0)
		return (fill_percent(intersect.x / 64.0, intersect.z / 64.0, 512, tabl[5]));
	else if (intersect.z == 64.0)
		return (fill_percent((64.0 - intersect.y) / 64.0, (64.0 - intersect.x) / 64.0, 512, tabl[1]));
	return (fill_percent((64.0 - intersect.y) / 64.0, intersect.x / 64.0, 512, tabl[3]));
}

unsigned int				add_texture(t_vec3d intersect, t_octree *node, int type)
{
	int	fd;
	static unsigned int	tabl[512*512];

	if (tabl[0] == 0)
	{
		fd = open("/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/andesite.binary", O_RDONLY);
		read(fd, tabl, 512 * 512 * 4);
		close(fd);
	}
	if (type == -1)
		return (fill_percent(1.0 - (intersect.y - floor(intersect.y)), intersect.z - floor(intersect.z), 512, tabl));
	else if (type == -2)
		return (fill_percent(1.0 - (intersect.y - floor(intersect.y)), 1.0 - (intersect.z - floor(intersect.z)), 512, tabl));
	else if (type == -3)
		return (fill_percent(intersect.x - floor(intersect.x), intersect.z - floor(intersect.z), 512, tabl));
	else if (type == -4)
		return (fill_percent(intersect.x - floor(intersect.x), intersect.z - floor(intersect.z), 512, tabl));
	else if (type == -5)
		return (fill_percent(1.0 - (intersect.y - floor(intersect.y)), intersect.x - floor(intersect.x), 512, tabl));
	return (fill_percent(1.0 - (intersect.y - floor(intersect.y)), 1.0 - (intersect.x - floor(intersect.x)), 512, tabl));
}
