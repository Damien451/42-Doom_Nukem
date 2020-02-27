#include <fcntl.h>

int			main(int ac, char **av)
{
	int		fd = open(av[1], O_RDONLY);
	char	*buffer = malloc(111111111);
	int		ret = read(fd, buffer, 11111111);

	buffer[ret] = 0;
	int i = 0;
	while (i < ret)
	{
		buffer[i] ^= buffer[i + 3];
		buffer[i + 3] ^= buffer[i];
		buffer[i] ^= buffer[i + 3];
		i += 4;
	}
	fd = open(av[2], O_TRUNC | O_CREAT | O_WRONLY, 0777);
	write(fd, buffer, ret);
}
