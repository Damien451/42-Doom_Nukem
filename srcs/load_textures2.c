/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 13:59:18 by roduquen          #+#    #+#             */
/*   Updated: 2020/04/20 16:14:18 by damien           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_strcat_2(char str[25], int i)
{
	char	buf[3];

	buf[0] = i < 10 ? i + '0' : i / 10 + '0';
	buf[1] = i >= 10 ? i % 10 + '0' : 0;
	buf[2] = 0;
	str[0] = 0;
	ft_strcat(str, "ressources/sounds/");
	ft_strcat(str, buf);
	ft_strcat(str, ".wav");
}
