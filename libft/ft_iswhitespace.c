/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iswhitespace.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: roduquen <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/01 11:39:47 by roduquen          #+#    #+#             */
/*   Updated: 2019/04/02 13:26:43 by roduquen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_iswhitespace(int c)
{
	if (c < -128 || c > 127)
		return (0);
	if (c == ' ' || c == '\n' || c == '\t')
		return (1);
	return (0);
}
