/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_rgb_files_to_binary.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 13:10:09 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/01 21:06:44 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

# define SIZE_X 64
# define SIZE_Y 64
# define ORIGIN_PATH "/sgoinfre/goinfre/Perso/dacuvill/Imp-Doom-sprite.rgb"
# define DESTINATION_PATH "/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/ennemy.binary"

int		main(void)
{
	int			i;
	int			j;
	unsigned char			tab[4];
	static unsigned char	tabi[3 * SIZE_X * SIZE_Y];
	static unsigned int		tabl[4 * SIZE_X * SIZE_Y];
	int						fd;

	fd = open(ORIGIN_PATH, O_RDONLY);
	read(fd, tabi, 3 * SIZE_X * SIZE_Y);
	close(fd);
	i = 0;
	while (i < SIZE_X)
	{
		j = 0;
		while (j < SIZE_Y)
		{
			tab[0] = tabi[i * SIZE_Y * 3 + 3 * j + 2];
			tab[1] = tabi[i * SIZE_Y * 3 + 3 * j + 1];
			tab[2] = tabi[i * SIZE_Y * 3 + 3 * j];
			tab[3] = 0;
			tabl[i * SIZE_Y + j] = *((unsigned int *)&tab);
			j++;
		}
		i++;
	}
	i = open(DESTINATION_PATH, O_TRUNC | O_WRONLY | O_CREAT, 0777);
	write(i, tabl, SIZE_X * SIZE_Y * 4);
	close(i);
    return (0);
}
