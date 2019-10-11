/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strfreejoin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 19:57:41 by dacuvill          #+#    #+#             */
/*   Updated: 2018/11/26 14:22:02 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strfreejoin(const char *s1, const char *s2, int c)
{
	char	*sj;
	size_t	i;
	size_t	j;

	i = 0;
	j = ft_strlen(s2);
	if ((!(s1)) || (!(s2)))
		return (NULL);
	if (!(sj = (char *)malloc(sizeof(char) * (ft_strlen(s1) + j) + 1)))
		return (NULL);
	j = 0;
	while (s1[j] != '\0')
		sj[i++] = s1[j++];
	j = 0;
	while (s2[j] != '\0')
		sj[i++] = s2[j++];
	sj[i] = '\0';
	if (c == 1 || c == 3)
		free((char *)s1);
	if (c == 2 || c == 3)
		free((char *)s2);
	return (sj);
}
