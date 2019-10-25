/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 22:34:08 by roduquen          #+#    #+#             */
/*   Updated: 2019/10/17 23:40:03 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned char	*cpy_char[2];
	unsigned long	*cpy_long[2];

	cpy_long[0] = (unsigned long*)dst;
	cpy_long[1] = (unsigned long*)src;
	while (n >= 8)
	{
		*cpy_long[0]++ = *cpy_long[1]++;
		n -= 8;
	}
	cpy_char[0] = (unsigned char*)cpy_long[0];
	cpy_char[1] = (unsigned char*)cpy_long[1];
	while (n > 0)
	{
		*cpy_char[0]++ = *cpy_char[0]++;
		n--;
	}
	return (dst);
}
