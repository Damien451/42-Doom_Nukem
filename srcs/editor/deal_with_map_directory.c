/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_with_map_directory.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/25 22:47:02 by dacuvill          #+#    #+#             */
/*   Updated: 2020/04/18 21:45:05 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <dirent.h>
#include <fcntl.h>
#include <unistd.h>
#include "libft.h"

char	*get_map_name(int map_to_show, char *dir_path)
{
	DIR				*directory;
	struct dirent	*maps;

	directory = NULL;
	maps = NULL;
	if (!(directory = opendir(dir_path)))
		return (NULL);
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
	return (NULL);
}

int		count_maps(int *first, char *dir_path)
{
	int				nbmaps;
	DIR				*directory;
	struct dirent	*maps;

	directory = NULL;
	maps = NULL;
	nbmaps = 0;
	if (!(directory = opendir(dir_path)))
		return (-1);
	while ((maps = readdir(directory)))
		if (maps->d_name[0] != '.')
			++nbmaps;
	(*first)++;
	closedir(directory);
	return (nbmaps);
}
