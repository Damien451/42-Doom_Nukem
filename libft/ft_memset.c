/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 22:03:00 by roduquen          #+#    #+#             */
/*   Updated: 2019/06/16 17:25:53 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

static void	set_magicint_and_long(unsigned int *mint, unsigned long *mlong
	, unsigned char c)
{
	*mint = c;
	*mint |= c << 8;
	*mint |= *mint << 16;
	*mlong = *mint;
	*mlong |= *mlong << 32;
}

static int	do_long_work(unsigned long mlong, size_t *len, unsigned long *slong)
{
	int			i;
	int			wait;

	i = 0;
	wait = (*len - *len % 8);
	*len -= wait;
	wait /= 8;
	while (i < wait)
		slong[i++] = mlong;
	return (wait);
}

static int	do_int_work(unsigned int mint, size_t *len, unsigned int *sint)
{
	*sint = mint;
	*len -= 4;
	return (4);
}

static void	do_char_work(char c, size_t len, unsigned char *str)
{
	size_t		i;

	i = 0;
	while (i < len)
		str[i++] = c;
}

void		*ft_memset(void *b, int c, size_t len)
{
	unsigned char	*setchar;
	unsigned long	*setlong;
	unsigned int	*setint;
	unsigned int	magicint;
	unsigned long	magiclong;

	if (len == 0)
		return (b);
	setchar = (unsigned char*)b;
	setint = (unsigned int*)b;
	setlong = (unsigned long*)b;
	set_magicint_and_long(&magicint, &magiclong, c);
	if (len >= 8)
		magiclong = do_long_work(magiclong, &len, setlong);
	else
		magiclong = 0;
	if (len >= 4)
		magicint = do_int_work(magicint, &len, setint + (magiclong * 2));
	else
		magicint = 0;
	if (len)
		do_char_work(c, len, setchar + (magiclong * 8 + magicint));
	return (b);
}
