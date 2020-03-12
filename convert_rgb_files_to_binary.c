/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   convert_rgb_files_to_binary.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 13:10:09 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/12 16:25:25 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

# define SIZE_X 64
# define SIZE_Y 64
# define ORIGIN_PATH "/sgoinfre/goinfre/Perso/dacuvill/ennemy"
# define DESTINATION_PATH "/sgoinfre/goinfre/Perso/dacuvill/Doom-Nukem/textures/enemy_binary/enemy"

static void	set_magiclong(unsigned long *mlong, unsigned char c)
{
	*mlong = c;
	*mlong |= *mlong << 8;
	*mlong |= *mlong << 16;
	*mlong |= *mlong << 32;
}

void		*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*setchar;
	unsigned long	*setlong;
	unsigned long	magiclong;

	if (len == 0)
		return (b);
	setchar = (unsigned char*)b;
	while ((size_t)setchar & 7 && len)
		*setchar++ = (unsigned char)c;
	set_magiclong(&magiclong, c);
	setlong = (unsigned long*)setchar;
	while (len >= 8)
	{
		*setlong++ = magiclong;
		len -= 8;
	}
	setchar = (unsigned char*)setlong;
	while (len--)
		*setchar++ = (unsigned char)c;
	return (b);
}

void	ft_bzero(void *s, size_t n)
{
	ft_memset(s, 0, n);
}

char	*ft_strnew(size_t size)
{
	char	*new_str;

	if (!(new_str = (char*)malloc(sizeof(char) * (size + 1))))
		return (NULL);
	ft_bzero(new_str, size + 1);
	return (new_str);
}

char	*ft_itoa(int n)
{
	unsigned int	nbr;
	unsigned int	sign;
	unsigned int	size;
	char			*new_str;

	nbr = (n < 0 ? -n : n);
	sign = (n < 0 ? 1 : 0);
	size = 1;
	while (nbr >= 10)
	{
		nbr /= 10;
		size++;
	}
	if (!(new_str = ft_strnew(size + sign)))
		return (NULL);
	nbr = (n < 0 ? -n : n);
	while (size >= 1)
	{
		new_str[size - 1 + sign] = nbr % 10 + '0';
		nbr /= 10;
		size--;
	}
	if (sign == 1)
		new_str[0] = '-';
	return (new_str);
}

char	*ft_strcat(char *s1, const char *s2)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	while (s1[i])
		i++;
	j = 0;
	while (s2[j])
	{
		s1[i + j] = s2[j];
		j++;
	}
	s1[i + j] = 0;
	return (s1);
}

int		main(void)
{
	int			i;
	int			j;
	unsigned char			tab[4];
	static unsigned char	tabi[3 * SIZE_X * SIZE_Y];
	static unsigned int		tabl[4 * SIZE_X * SIZE_Y];
	int						fd;

	char		origin[150];
	char		destination[150];
	int			k;

	k = 0;
	while (++k < 22)
	{
		ft_bzero(origin, 150);
		ft_bzero(destination, 150);
		ft_bzero(tabi, 3 * SIZE_X * SIZE_Y);
		ft_bzero(tabl, 4 * SIZE_X * SIZE_Y);
		ft_strcat(ft_strcat(ft_strcat(origin, ORIGIN_PATH), ft_itoa(k)), ".rgb");
		printf("origin = %s\n", origin);
		ft_strcat(ft_strcat(ft_strcat(destination, DESTINATION_PATH), ft_itoa(k)), ".binary");
		printf("dest = %s\n", destination);
		fd = open(origin, O_RDONLY);
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
				tab[3] = 0xff;
				tabl[i * SIZE_Y + j] = *((unsigned int *)&tab);
				j++;
			}
			i++;
		}
		i = open(destination, O_TRUNC | O_WRONLY | O_CREAT, 0777);
		write(i, tabl, SIZE_X * SIZE_Y * 4);
		close(i);
	}
    return (0);
}
