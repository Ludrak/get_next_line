/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 22:30:02 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/14 17:01:03 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void		gnl_bzero(char *buf, int len)
{
	while (buf && len)
	{
		*buf = 0;
		buf++;
		len--;
	}
}

t_nl_info	gnl_strchr(char *buf, int len, int fd)
{
	t_nl_info	info;
	int			i;

	i = 0;
	while (*buf && len)
	{
		if (*buf == '\n')
		{
			info.status = 1;
			break ;
		}
		i++;
		len--;
		buf++;
	}
	if (*buf != '\n' && i == BUFFER_SIZE)
		info.status = 0;
	else if (*buf == '\0' && i < BUFFER_SIZE)
		info.status = 0;
	info.fd = fd;
	info.length = i;
	return (info);
}

int			gnl_strlen(char *s)
{
	int		i;

	i = 0;
	while (s && *s)
	{
		i++;
		s++;
	}
	return (i);
}

char		*gnl_join(char *a, char *b, int len, t_free_mode fm)
{
	char	*p_a;
	char	*p_b;
	char	*line;
	int		i;

	i = 0;
	p_a = a;
	p_b = b;
	if (!(line = malloc((gnl_strlen(a) + len + 1) * sizeof(char))))
		return (0);
	while (a && *a)
		line[i++] = *a++;
	while (b && *b && len)
	{
		line[i++] = *b++;
		len--;
	}
	if (fm != FREE_LAST && fm != FREE_NONE)
		free(p_a);
	if (fm != FREE_FIRST && fm != FREE_NONE)
		free(p_b);
	line[i] = '\0';
	return (line);
}

void		gnl_add_buffer(t_buff_tail **buf_tail, char **buff, int len, int fd)
{
	t_buff_tail		*buf;
	t_buff_tail		*bf;
	char			*buff_cpy;
	char			*a_b;

	bf = *buf_tail;
	buff_cpy = *buff;
	while (bf && bf->fd != fd)
		bf = bf->next;
	if (bf && bf->fd == fd)
	{
		bf->line[0] = '\0';
		a_b = *buff + len + 1;
		bf->line = gnl_join(bf->line, a_b, BUFFER_SIZE, FREE_FIRST);
		free(*buff);
		return ;
	}
	if (!(buf = malloc(sizeof(t_buff_tail))))
		return ;
	buf->next = *buf_tail;
	*buff += (len + 1) < BUFFER_SIZE ? (len + 1) : BUFFER_SIZE;
	buf->line = gnl_join(NULL, *buff, BUFFER_SIZE - (len + 1), FREE_NONE);
	buf->fd = fd;
	*buf_tail = buf;
	free(buff_cpy);
}
