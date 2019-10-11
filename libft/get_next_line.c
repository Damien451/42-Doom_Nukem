/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dacuvill <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/02 17:50:41 by dacuvill          #+#    #+#             */
/*   Updated: 2019/08/19 12:10:30 by dacuvill         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>
#include <unistd.h>

static t_lst	*ft_init_lst(t_lst **head, const int fd)
{
	t_lst	*lst_tmp;

	if (!(*head))
	{
		if (!((*head) = ft_memalloc(sizeof(t_lst))))
			return (NULL);
		(*head)->file_d = fd;
	}
	lst_tmp = (*head);
	while (lst_tmp->next != NULL && lst_tmp->file_d != fd)
		lst_tmp = lst_tmp->next;
	if (lst_tmp->next == NULL && lst_tmp->file_d != fd)
	{
		if (!(lst_tmp->next = ft_memalloc(sizeof(t_lst))))
			return (NULL);
		lst_tmp->next->file_d = fd;
		lst_tmp = lst_tmp->next;
	}
	return (lst_tmp);
}

static int		ft_newline(char **str, char **line, int rd)
{
	char	*sub;
	size_t	i;

	sub = ft_strchr(*str, '\n');
	if (sub == NULL && *str != NULL && rd == 0)
	{
		if (ft_strlen(*str) == 0)
			return (0);
		*line = ft_strdup(*str);
		ft_strdel(str);
		return (1);
	}
	i = sub - *str;
	if (!(*line = ft_strsub(*str, 0, i)))
		return (-1);
	if (!(sub = ft_strdup(&(*str)[i + 1])))
		return (-1);
	ft_strdel(str);
	*str = sub;
	return (1);
}

int				get_next_line(const int fd, char **line)
{
	ssize_t			rd;
	char			buf[BUFF_SIZE + 1];
	static t_lst	*head;
	t_lst			*lst;

	if (fd < 0 || read(fd, &buf, 0) || !(lst = ft_init_lst(&head, fd)))
		return (-1);
	while ((rd = read(fd, &buf, BUFF_SIZE)) > 0)
	{
		buf[rd] = '\0';
		lst->content = ((!(lst->content)) ?
				ft_strdup(buf) : ft_strfreejoin(lst->content, buf, 1));
		if (ft_strchr(lst->content, '\n'))
			return (ft_newline(&(lst->content), line, rd));
	}
	return (lst->content == NULL ? 0 : ft_newline(&(lst->content), line, rd));
}
