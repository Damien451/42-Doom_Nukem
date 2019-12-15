/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_default_inputs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/15 16:41:46 by roduquen          #+#    #+#             */
/*   Updated: 2019/12/15 16:41:48 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "inputs.h"

int			get_default_inputs(t_doom *data)
{
	data->tabinputs.keycode[0] = DEFINPUT1;
	data->tabinputs.keycode[1] = DEFINPUT2;
	data->tabinputs.keycode[2] = DEFINPUT3;
	data->tabinputs.keycode[3] = DEFINPUT4;
	data->tabinputs.keycode[4] = DEFINPUT5;
	data->tabinputs.keycode[5] = DEFINPUT6;
	data->tabinputs.keycode[6] = DEFINPUT7;
	data->tabinputs.keycode[7] = DEFINPUT8;
	data->tabinputs.keycode[8] = DEFINPUT9;
	data->tabinputs.keycode[9] = DEFINPUT10;
	data->tabinputs.keycode[10] = DEFINPUT11;
	data->tabinputs.keycode[11] = DEFINPUT12;
	return (0);
}
