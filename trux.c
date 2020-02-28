#include <fcntl.h>

int			main(int ac, char **av)
{
	int		fd = open(av[1], O_RDONLY);
	unsigned int	*buffer = malloc(111111111);
	int		ret = read(fd, buffer, 11111111);

	ret /= 4;
	int i = 0;
	unsigned int tmp;
	while (i < ret)
	{
		tmp = buffer[i] & 0xFF;
		buffer[i] >>= 8;
		tmp <<= 24;
		buffer[i] |= tmp;
		i++;
	}
	fd = open(av[2], O_TRUNC | O_CREAT | O_WRONLY, 0777);
	write(fd, buffer, ret);
}
