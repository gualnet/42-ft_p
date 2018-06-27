/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_sender.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 12:37:11 by galy              #+#    #+#             */
/*   Updated: 2018/06/24 10:49:06 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		read_sock(t_vault *vault, char *buff)
{
	int		rs;
	int		b_size;

	b_size = R_BUFF_SIZE - 1;
	ft_bzero(buff, b_size);
	if ((rs = read(vault->csc, buff, b_size)) > 0)
	{
		ft_printf("[%d]Receive: [%s]\n", getpid(), buff);
		// ft_printf("MESSLEN{%d}", ft_strlen(buff));
	}
	return (0);
}

int		sender_sock(t_vault *vault, char *msg)
{
	if (write(vault->csc, msg, ft_strlen(msg) + 1) != \
		(ssize_t)(ft_strlen(msg) + 1))
	{
		ft_printf("[%d]Echec envoi..\n", getpid());
		return (-1);
	}
	else
		ft_printf("[%d] sent : [%s]\n", getpid(), msg);

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
	else
		ft_printf("[%d] sent : [%s]\n", getpid(), msg);
	return (1);
}

int		sender_dtp_bin(t_vault *vault, void *msg, size_t len)
{
	int ret;

	ft_printf("---------%d----------\n", vault->csd);
	ft_printf("---------%d----------\n", vault->dtp_sock);
	if ((ret = send(vault->csd, msg, len, 0)) < 0)
	{
		ft_printf("pb dans sender_dtp_bin\n");
		return (-1);
	}
	ft_printf("[%d] sent_bin : [%d]\n", getpid(), ret);
	return (1);
}

// int		dtp_receiver(t_vault *vault)
// {

// }