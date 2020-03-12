/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_inventory_strings.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <dacuvill@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/10 21:20:52 by dacuvill          #+#    #+#             */
/*   Updated: 2020/03/10 22:02:26 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom.h"
#include "graphic_lib.h"
#include "player.h"
#include "libft.h"

static void			display_ammo_stock(t_doom *data, t_graphic_lib *lib,
	t_player *player)
{
	static char	ammo_stock[7];
	char		*left;

	ft_bzero(ammo_stock, 7);
	left = ft_itoa(player->inventory.ammo_stock);
	ft_strcat(ft_strcat(ammo_stock, " I "), left);
	put_string_on_renderer(data, point((16 * (player->inventory.ammo + 1))
		+ WIDTH / 1.155 + player->inventory.ammo, 16 + HEIGHT / 3.4505),
		label(ammo_stock, (SDL_Color){255, 0, 0, 0}), data->lib.ptrfont[2]);
	free(left);
}

void				display_inventory_strings(t_doom *data,
	t_graphic_lib *lib, t_player *player, long state)
{
    if (state == PLAYING)
        display_ammo_stock(data, lib, player);
}
