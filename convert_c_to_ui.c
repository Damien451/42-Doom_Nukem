#include <fcntl.h>

static inline void	init_map_colors2(unsigned int map_colors[40])
{
	map_colors[21] = 0x661813;
	map_colors[22] = 0x46241d;
	map_colors[23] = 0x898280;
	map_colors[24] = 0xd3d3d3;
	map_colors[25] = 0xd3d3d3;
	map_colors[26] = 0xd3d3d3;
	map_colors[27] = 0x8b8b8b;
	map_colors[28] = 0xffffff;
	map_colors[29] = 0x2f2d3d;
	map_colors[30] = 0x971a28;
	map_colors[31] = 0x276107;
	map_colors[32] = 0x078eae;
	map_colors[33] = 0xf6ce78;
	map_colors[34] = 0x7c7c86;
	map_colors[35] = 0x5b4526;
	map_colors[36] = 0xe0b378;
	map_colors[37] = 0x352916;
	map_colors[38] = 0x2f241b;
	map_colors[39] = 0x41291e;
	map_colors[40] = 0xffffff;
}

void				init_map_colors(unsigned int map_colors[40])
{
	map_colors[0] = 0x585949;
	map_colors[1] = 0x7b716e;
	map_colors[2] = 0x8c8174;
	map_colors[3] = 0xbcbcb9;
	map_colors[4] = 0x956250;
	map_colors[5] = 0xc3a58a;
	map_colors[6] = 0xcfb48f;
	map_colors[7] = 0xcfb48f;
	map_colors[8] = 0xcfb48f;
	map_colors[9] = 0xcfb48f;
	map_colors[10] = 0x525252;
	map_colors[11] = 0x525252;
	map_colors[12] = 0x989898;
	map_colors[13] = 0x686a6f;
	map_colors[14] = 0x33332f;
	map_colors[15] = 0x33332f;
	map_colors[16] = 0x33332f;
	map_colors[17] = 0x93908e;
	map_colors[18] = 0x656261;
	map_colors[19] = 0x656261;
	map_colors[20] = 0x989898;
	init_map_colors2(map_colors);
}

int main(int ac, char **av)
{
	int		fd;
	int		fd2;
	char	map[64][64][64];
	unsigned int map2[64][64][64];
	unsigned int map_colors[40];

	init_map_colors(map_colors);
	fd = open(av[1], O_RDONLY);
	read(fd, map, 2000000000);
	int i,j,k;
	i = 0;
	while (i < 64)
	{
		j = 0;
		while (j < 63)
		{
			k = 0;
			while (k < 64)
			{
				if ((fd2 = map[i][j][k]) != 0)
					map2[i][j][k] = map_colors[fd2];
				k++;
			}
			j++;
		}
		i++;
	}
	fd2 = open(av[1], O_TRUNC | O_WRONLY);
	write(fd2, map2, 1048576);
	return (0);
}
