/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 22:30:16 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/14 17:01:04 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

t_buff_tail	*gnl_clear_buffer(t_buff_tail *curr, int fd)
{
	t_buff_tail	*next;

	if (!curr)
		return (NULL);
	if (curr->fd == fd)
	{
		next = curr->next;
		free(curr->line);
		free(curr);
		return (next);
	}
	curr->next = gnl_clear_buffer(curr->next, fd);
	return (curr);
}

void		gnl_get_last_buffer(char **buff, t_buff_tail **tail, int fd)
{
	t_buff_tail	*buf;

	**buff = '\0';
	buf = *tail;
	while (buf)
	{
		if (buf->fd == fd)
		{
			free(*buff);
			*buff = gnl_join(NULL, buf->line, BUFFER_SIZE, FREE_FIRST);
			return ;
		}
		buf = buf->next;
	}
}

int			apl_info(t_nl_info i, char **buf, t_buff_tail **buf_t, char **line)
{
	if (i.status == 1)
	{
		if ((*line = gnl_join(*line, *buf, i.length, FREE_FIRST)) == 0)
			return (-1);
		gnl_add_buffer(buf_t, buf, i.length, i.fd);
		return (1);
	}
	else if (i.status == 0)
	{
		if ((*line = gnl_join(*line, *buf, i.length, FREE_BOTH)) == 0)
			return (-1);
		if (!(*buf = malloc((BUFFER_SIZE + 1) * sizeof(char))))
			return (-1);
		**buf = '\0';
	}
	return (0);
}

int			gnl_eof(char **line, char **buf, t_nl_info info, t_buff_tail **tail)
{
	if (!(*line = gnl_join(*line, *buf, info.length, FREE_BOTH)))
		return (-1);
	*tail = gnl_clear_buffer(*tail, info.fd);
	return (0);
}

int			get_next_line(int fd, char **line)
{
	static t_buff_tail	*buffer_tail = NULL;
	t_nl_info			info;
	char				*buffer;
	int					r_len;
	int					apply_ret;

	if (!line || fd < 0 || !(buffer = malloc((BUFFER_SIZE + 1) * sizeof(char))))
		return (-1);
	*line = NULL;
	gnl_get_last_buffer(&buffer, &buffer_tail, fd);
	r_len = (*buffer) ? gnl_strlen(buffer) : 0;
	while ((*buffer) ? (1) : (r_len = read(fd, buffer, BUFFER_SIZE)) >= 0)
	{
		buffer[r_len] = '\0';
		info = gnl_strchr(buffer, BUFFER_SIZE, fd);
		if ((apply_ret = apl_info(info, &buffer, &buffer_tail, line)) != 0)
			return (apply_ret);
		if (r_len == 0)
			return (gnl_eof(line, &buffer, info, &buffer_tail));
	}
	buffer_tail = gnl_clear_buffer(buffer_tail, fd);
	free(buffer);
	return (-1);
}
