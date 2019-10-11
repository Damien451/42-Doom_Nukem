/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:40:39 by roduquen          #+#    #+#             */
/*   Updated: 2019/07/11 01:01:54 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static void	init_data(unsigned long data[], int c)
{
	data[0] = 0x101010101010101;
	data[1] = c | c << 8;
	data[1] |= data[1] << 16;
	data[1] |= data[1] << 32;
}

static void	find_char_in_long(unsigned long data[], unsigned long **str
	, size_t *n)
{
	while (*n >= sizeof(unsigned long))
	{
		data[2] = **str ^ data[1];
		if ((((data[2] - data[0]) & ~data[2]) & (data[0] << 7)) != 0)
			break ;
		(*str)++;
		*n -= sizeof(unsigned long);
	}
}

void		*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*str;
	unsigned long	*long_str;
	unsigned long	data[3];

	str = (unsigned char*)s;
	while (n > 0 && (size_t)str % sizeof(unsigned long) != 0)
	{
		if (*str == (unsigned char)c)
			return ((void*)str);
		str++;
		n--;
	}
	long_str = (unsigned long*)str;
	init_data(data, c);
	find_char_in_long(data, &long_str, &n);
	str = (unsigned char*)long_str;
	while (n > 0)
	{
		if (*str == (unsigned char)c)
			return ((void*)str);
		n--;
		str++;
	}
	return (NULL);
}
