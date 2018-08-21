/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 20:31:43 by galy              #+#    #+#             */
/*   Updated: 2017/03/09 13:37:20 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int			get_next_line(const int fd, char **line)
{
	static t_fdlink	*fdlst;
	t_fdlink		*lnk;
	int				ret;

	if (fd == -1 || (lnk = check_fd(fd, &fdlst)) == NULL)
		return (-1);
	ret = read_fd(fd, lnk);
	if (ret > 0 || ret == -99)
	{
		line[0] = lnk->stk[0];
		return (1);
	}
	else if (ret == 0)
	{
		line[0] = NULL;
		return (0);
	}
	return (-1);
}

t_fdlink	*check_fd(int fd, t_fdlink **fdlst)
{
	t_fdlink	*newlink;
	t_fdlink	*tmplink;

	newlink = NULL;
	tmplink = *fdlst;
	if (tmplink != NULL && fd != -1)
	{
		while (tmplink != NULL && *fdlst != NULL)
		{
			if (tmplink->fd == fd)
				return (tmplink);
			tmplink = tmplink->next;
		}
	}
	if ((*fdlst == NULL || tmplink == NULL) && fd != -1)
	{
		if ((newlink = (t_fdlink*)malloc(sizeof(*newlink))) == NULL)
			return (NULL);
		newlink->fd = fd;
		if ((newlink->stk[1] = ft_strnew(1)) == NULL)
			return (NULL);
		newlink->next = *fdlst;
		*fdlst = newlink;
	}
	return (*fdlst);
}

int			read_fd(int fd, t_fdlink *lnk)
{
	char	buff[BUFF_SIZE + 1];
	int		ret;
	int		endl;
	char	*str_inter;

	ret = BUFF_SIZE;
	endl = (ft_strchr(lnk->stk[1], '\n') != 0) ? 1 : 0;
	while (ret != 0 && endl == 0)
	{
		ft_bzero(buff, BUFF_SIZE);
		if ((ret = read(fd, buff, BUFF_SIZE)) == -1)
			return (-1);
		buff[ret] = '\0';
		if (ret != 0)
		{
			if ((str_inter = ft_strjoin(lnk->stk[1], buff)) == NULL)
				return (-1);
			free(lnk->stk[1]);
			lnk->stk[1] = str_inter;
		}
		if (ft_strchr(lnk->stk[1], '\n') != 0)
			endl = 1;
	}
	return (endl = check_endl(lnk, ret));
}

int			check_endl(t_fdlink *lnk, int ret)
{
	char	*str_inter;

	if ((ret != 0) && ((str_inter = ft_strchr(lnk->stk[1], '\n')) != 0))
		return (event(str_inter, lnk, EVENT_1));
	else if ((ret < BUFF_SIZE && ret > 0) &&\
	(ft_strchr(lnk->stk[1], '\n') == NULL))
	{
		lnk->stk[0] = lnk->stk[1];
		return (ret);
	}
	else if ((ret == 0) && (ft_strchr(lnk->stk[1], '\n') == NULL))
		return (event(str_inter, lnk, EVENT_3));
	return (0);
}

int			event(char *str_inter, t_fdlink *lnk, int event)
{
	if (event == EVENT_1)
	{
		str_inter[0] = '\0';
		if ((lnk->stk[0] = ft_strdup(lnk->stk[1])) == NULL)
			return (-1);
		if ((str_inter = ft_strdup(str_inter + 1)) == NULL)
			return (-1);
		free(lnk->stk[1]);
		lnk->stk[1] = str_inter;
		return (1);
	}
	else if (event == EVENT_3)
	{
		if (ft_strcmp(lnk->stk[1], "") != 0)
		{
			lnk->stk[0] = lnk->stk[1];
			if ((lnk->stk[1] = ft_strnew(1)) == NULL)
				return (-1);
			return (-99);
		}
	}
	return (0);
}
