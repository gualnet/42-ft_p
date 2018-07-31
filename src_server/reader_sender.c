/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_sender.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 12:37:11 by galy              #+#    #+#             */
/*   Updated: 2018/07/26 17:19:46 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		read_sock(t_vault *vault, char *buff)
{
	int		rs;
	int		b_size;

	b_size = R_BUFF_SIZE - 1;
	ft_bzero(buff, b_size);
	// if ((rs = read(vault->csc, buff, b_size)) > 0)
	if ((rs = recv(vault->csc, buff, b_size, 0)) > 0)
	{
		ft_printf("[%d]Receive: [%s]\n", getpid(), buff);
		// ft_printf("MESSLEN{%d}", ft_strlen(buff));
	}
	return (0);
}

/*
**	Generates a normal error when starting the server
**	without any valide connection.
*/

int		sender_sock(t_vault *vault, char *msg)
{
	ssize_t att = (ssize_t)(ft_strlen(msg) + 1);
	ssize_t ret = send(vault->csc, msg, att, 0);

	if (ret != att)
	{
		ft_printf("[%d] Error Sending message..\n", getpid());
		return (-1);
	}
	// else
	// 	ft_printf("[%d] sent : [%s]\n", getpid(), msg);

	return (1);
}

int		sender_dtp(t_vault *vault, char *msg)
{
	if (write(vault->csd, msg, ft_strlen(msg) + 1) != \
		(ssize_t)(ft_strlen(msg) + 1))
	{
		ft_printf("[%d]Echec envoi..\n", getpid());
		return (-1);
	}
	// else
	// 	ft_printf("[%d] sent : [%s]\n", getpid(), msg);
	return (1);
}

int		sender_dtp_bin(t_vault *vault, void *msg, size_t len)
{
	int ret;

	if ((ret = send(vault->csd, msg, len, 0)) < 0)
	{
		ft_printf("pb dans sender_dtp_bin\n");
		return (-1);
	}
	ft_printf("[%d] sent_bin : [%d]\n", getpid(), ret);
	return (1);
}

char	*dtp_receiver(int sock, ssize_t	*size)
{
	char	buf[R_BUFF_SIZE + 1];
	void	*msg;
	void	*tmp;
	ssize_t size_2;

	msg = NULL;
	tmp = NULL;
	*size = 0;
	while (1)
	{
		ft_bzero(buf, R_BUFF_SIZE + 1);
		size_2 = *size;
		if ((*size += recv(sock, buf, R_BUFF_SIZE, 0)) < 0)
			ft_printf("[*] Error receiving message from server !\n");
		if (*size == size_2)
			break ;
		if (msg != NULL)
		{
			tmp = msg;
			msg = malloc(*size);
			ft_memcpy(msg, tmp, size_2);
			ft_memcpy(msg + size_2, buf, *size - size_2);
			free(tmp);
		}
		else
		{
			msg = malloc(*size);
			ft_memcpy(msg, buf, *size);
		}
	}
	return (msg);
}