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

static inline unsigned int	fill_percent_512(double a, double b
	, unsigned int tab[512 * 512])
{
	return (tab[(int)(a * 512) * 512 + (int)(b * 512)]);
}

unsigned int	fill_percent_128(double a, double b
		, unsigned int tab[128 * 128])
{
	return (tab[(int)(a * 128) * 128 + (int)(b * 128)]);
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
		return (fill_percent_512((64.0 - intersect.y) / 64.0, intersect.z / 64.0, tabl[0]));
	else if (intersect.x == 0.0)
		return (fill_percent_512((64.0 - intersect.y) / 64.0, (64.0 - intersect.z) / 64.0, tabl[2]));
	else if (intersect.y == 64.0)
		return (fill_percent_512(intersect.x / 64.0, intersect.z / 64.0, tabl[4]));
	else if (intersect.y == 0.0)
		return (fill_percent_512(intersect.x / 64.0, intersect.z / 64.0, tabl[5]));
	else if (intersect.z == 64.0)
		return (fill_percent_512((64.0 - intersect.y) / 64.0, (64.0 - intersect.x) / 64.0, tabl[1]));
	return (fill_percent_512((64.0 - intersect.y) / 64.0, intersect.x / 64.0, tabl[3]));
}
