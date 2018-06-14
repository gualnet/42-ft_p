/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reader_sender.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 12:37:11 by galy              #+#    #+#             */
/*   Updated: 2018/06/14 12:41:45 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

#define R_BUFF_SIZE

int		read_sock(t_vault *vault)
{
	char	buff[1024];
	int		rs;
	size_t	b_size;

	b_size = 1023;
	ft_bzero(buff, b_size);
	if ((rs = read(vault->cs, buff, b_size)) > 0)
	{
		ft_printf("[%d]Receive: [%s]\n", getpid(), buff);
		// ft_printf("MESSLEN{%d}", ft_strlen(buff));
	}
	if (strncmp(buff, "AUTH", 4) == 0)
		return (1);
	else if (strncmp(buff, "USER", 4) == 0)
		return (store_user(vault, buff));
	else if (strncmp(buff, "QUIT", 4) == 0)
		return (999);
	else
	{
		ft_printf("[%d] Commande non implem ");
		sender_sock(vault, "502 \x0a\x0d");
		exit(-1);
	}
	
	return (0);
}

int		sender_sock(t_vault *vault, char *msg)
{
	if (write(vault->cs, msg, ft_strlen(msg) + 1) != \
		(ssize_t)(ft_strlen(msg) + 1))
		ft_printf("[%d]Echec envoi..\n", getpid());
	else
		ft_printf("[%d] sent : [%s]\n", getpid(), msg);
}

int		dispatcher(t_vault *vault, char *buff)
{

}