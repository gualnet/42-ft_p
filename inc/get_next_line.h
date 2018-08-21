/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_next_line.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 20:30:03 by galy              #+#    #+#             */
/*   Updated: 2017/03/09 13:26:39 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_GET_NEXT_LINE_H
# define FT_GET_NEXT_LINE_H

# include "libft.h"
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>

# define BUFF_SIZE 32
# define EVENT_1 1
# define EVENT_3 3

typedef struct		s_fdlink
{
	int				fd;
	char			*stk[2];
	void			*next;
}					t_fdlink;

int					get_next_line(const int fd, char **line);
t_fdlink			*check_fd(int fd, t_fdlink **fdlst);
int					read_fd(int fd, t_fdlink *lnk);
int					check_endl(t_fdlink *lnk, int ret);
int					event(char *str_inter, t_fdlink *lnk, int event);

#endif
