/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 22:03:00 by roduquen          #+#    #+#             */
/*   Updated: 2019/10/17 20:13:06 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

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
