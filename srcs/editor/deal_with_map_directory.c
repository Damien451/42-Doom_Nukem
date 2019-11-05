
#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

char	*get_map_name(int map_to_show)
{
	DIR				*directory;
	struct dirent	*maps;

	directory = NULL;
	maps = NULL;
	if (!(directory = opendir("maps")))
		return ("Error opening directory");
	while ((maps = readdir(directory)))
	{
		if (map_to_show == 0 && maps->d_name[0] != '.')
		{
			closedir(directory);
			return (maps->d_name);
		}
		if (maps->d_name[0] != '.')
			--map_to_show;
	}
	closedir(directory);
	return ("No map in directory");
}

int		count_maps(int *first)
{
	int				nbmaps;
	DIR				*directory;
	struct dirent	*maps;

	directory = NULL;
	maps = NULL;
	nbmaps = 0;
	if (!(directory = opendir("maps")))
		return (-1);
	while ((maps = readdir(directory)))
		if (maps->d_name[0] != '.')
			++nbmaps;
	(*first)++;
	closedir(directory);
	return (nbmaps);
}
