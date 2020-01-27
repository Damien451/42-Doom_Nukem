/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionnary_binary_tex.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 13:41:11 by roduquen          #+#    #+#             */
/*   Updated: 2020/01/26 17:23:41 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <stdio.h>

void			dictionnary_binary_tex(t_doom *data)
{
	int			i;

	i = 0;
	while (i < NBR_TEXTURES_BLOCKS)
	{
		sprintf(data->lib.texture_dic[i]
			, "/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/%d.binary", i);
		i++;
	}
}
