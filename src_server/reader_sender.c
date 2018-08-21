/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_sender.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 12:37:11 by galy              #+#    #+#             */
/*   Updated: 2018/08/08 18:37:31 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		read_sock(t_vault *vault, char *buff)
{
	int		rs;
	int		b_size;

	b_size = R_BUFF_SIZE - 1;
	ft_bzero(buff, b_size);
	if ((rs = recv(vault->csc, buff, b_size, 0)) > 0)
	{
		ft_printf("[%d]Receive: [%s]\n", getpid(), buff);
	}
	return (0);
}

/*
**	Generates a normal error when starting the server
**	without any valide connection.
*/

int		sender_sock(t_vault *vault, char *msg)
{
	ssize_t att;
	ssize_t ret;

	att = (ssize_t)(ft_strlen(msg) + 1);
	ret = send(vault->csc, msg, att, 0);
	if (ret != att)
	{
		ft_printf("[%d] Error Sending message..\n", getpid());
		return (-1);
	}
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
	return (1);
}
