/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_send.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 12:07:18 by galy              #+#    #+#             */
/*   Updated: 2018/06/28 12:41:53 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

char	*overflow_prot(int rs, char *buf)
{
	char	*tmp;

	while (1)
	{
		ft_bzero(buf, BUF_SIZE);
		if ((rs = read(1, buf, BUF_SIZE)) < 1)
			break ;
		if (rs != 0 && rs < BUF_SIZE)
		{
			ft_printf("\nlast line [%d]!!!\n", ft_strlen(buf));
			buf[ft_strlen(buf) - 1] = 'A';
		}
		buf[BUF_SIZE - 1] = '\0';
		ft_printf("INNER [%s]\n", buf);

		ft_strjoin()

	}




	return (NULL);
}

int		read_send_loop(char *name, int sock)
{
	char	buf[BUF_SIZE + 1];
	int		rs;
	char	*tmp;
	int		i;

	ft_printf("*%s > ", name);
	while (1)
	{
		tmp = NULL;
		ft_bzero(buf, BUF_SIZE);
		if ((rs = read(1, buf, BUF_SIZE)) != 0)
			ft_printf("*%s > %s", name, buf);
		ft_printf("*%s > ", name);
		i = 0;
		while (buf[i] != '\0' && i < BUF_SIZE)
			i++;
		ft_printf("rs = %d - i = %d", rs + 1, i);
		if (rs > BUF_SIZE - 2)
		{
			ft_printf("CAS01\n");
			tmp = overflow_prot(rs, buf);
		}
		else
		{
			ft_printf("CAS02\n");
			buf[i - 1] = '\r';
			buf[i] = '\n';
			tmp = buf;
		}
		send(sock, tmp, rs + 1, 0);
	}
}