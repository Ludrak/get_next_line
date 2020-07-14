/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lrobino <lrobino@student.42lyon.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 22:28:48 by lrobino           #+#    #+#             */
/*   Updated: 2020/07/14 17:01:06 by lrobino          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE	32
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>

# define FREE_FIRST		1
# define FREE_LAST		2
# define FREE_BOTH		3
# define FREE_NONE		0

typedef int		t_free_mode;

typedef struct	s_buff_tail
{
	int					fd;
	char				*line;
	struct s_buff_tail	*next;
}				t_buff_tail;

typedef struct	s_nl_info
{
	int					status;
	int					length;
	int					fd;
}				t_nl_info;

void			gnl_bzero(char *buf, int len);
t_nl_info		gnl_strchr(char *buf, int len, int fd);
char			*gnl_join(char *a, char *b, int len, t_free_mode fm);
void			gnl_add_buffer(t_buff_tail **b, char **buffer, int len, int fd);
int				gnl_strlen(char *s);
int				get_next_line(int fd, char **line);

#endif
