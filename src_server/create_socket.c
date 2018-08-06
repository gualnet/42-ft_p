/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_socket.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 18:04:08 by galy              #+#    #+#             */
/*   Updated: 2018/08/06 18:07:57 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		create_dtp_socket(t_vault *vault)
{
	int	sock;
	int i;
	int port;

	i = 1;
	while (i < 10)
	{
		port = ntohs(vault->n_info.cmd_sin.sin_port);
		port += i * 2;
		ft_printf("DTP PORT [%d] - ", port);
		if ((sock = new_socket(vault, port, DTP_SOCK)) > 1)
			break ;
		i++;
	}
	if (sock < 1)
	{
		ft_printf("new dtp socket error (sock[%d])\n", sock);
		return (-1);
	}
	ft_printf("Data transfert socket listening on port :%d\n", \
	ntohs(vault->n_info.dtp_sin.sin_port));
	return (sock);
}
