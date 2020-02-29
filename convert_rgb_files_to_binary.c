/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_rgb_files_to_binary.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 13:10:09 by dacuvill          #+#    #+#             */
/*   Updated: 2020/02/29 14:10:14 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>

# define SIZE_X 1920
# define SIZE_Y 1440
# define ORIGIN_PATH "/sgoinfre/goinfre/Perso/dacuvill/eclair.rgb"
# define DESTINATION_PATH "/sgoinfre/goinfre/Perso/dacuvill/textures_binary/eclair.binary"

int		main(void)
{
	int			i;
	int			j;
	unsigned char			tab[4];
	static unsigned char	tabi[3 * SIZE_X * SIZE_Y];
	static unsigned int		tabl[4 * SIZE_X * SIZE_Y];
	int						fd;


	/*int						k;
	char					destpath[70] = "/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/";
	char					full_destpath[100];
	char					originpath[60] = "/sgoinfre/goinfre/Perso/dacuvill/obj_rgb/";
	char					full_originpath[80];

	k = -1;
	while (++k < 20)
	{
		ft_bzero(full_originpath, 80);
		ft_bzero(full_destpath, 100);
		ft_strcat(ft_strcat(ft_strcat(full_originpath, originpath), ft_itoa(k)), ".rgb");
		ft_strcat(ft_strcat(ft_strcat(full_destpath, destpath), ft_itoa(k + 42)), ".binary");
		tab[0] = 0;*/
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
	//}
    return (0);
}
