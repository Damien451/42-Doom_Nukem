/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dictionnary_binary_tex.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/16 13:41:11 by roduquen          #+#    #+#             */
/*   Updated: 2020/02/03 19:02:14 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include <stdio.h>

void			dictionnary_binary_tex(t_doom *data)
{
	int			i;

	i = 0;
	while (i < 42)
	{
		sprintf(data->lib.texture_dic[i]
			, "/sgoinfre/goinfre/Perso/dacuvill/blocks_binary/%d.binary", i);
		i++;
	}
}

void			dictionnary_binary_models(t_doom *data)
{
	int			i;

	i = 0;
	while (i < NBR_TEXTURES_OBJECTS)
	{
		sprintf(data->dic_obj[i]
			, "ressources/models/%d.binary", i);
		i++;
	}
}
