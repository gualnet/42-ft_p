/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_server.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:52:10 by galy              #+#    #+#             */
/*   Updated: 2018/06/15 18:06:04 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		new_socket(t_vault *vault, int port, int sock_type)
{
	int					sock;
	int					ret_l;
	struct protoent		*proto;
	struct sockaddr_in	*sin; //socket address info internet form - here the cmd sock

	if ((proto = getprotobyname("tcp")) == NULL)
		return (-1);
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) < 0)
		return (-2);
	sin = &vault->n_info.cmd_sin;
	sin->sin_family = AF_INET;
	sin->sin_port = htons(port);
	sin->sin_addr.s_addr = htonl(INADDR_ANY);
	if (bind(sock, (const struct sockaddr*)sin, sizeof(*sin)) < 0)
	{
		ft_printf("Binding error\n");
		return (-1);
	}
	if (sock_type == CMD_SOCK)
		ret_l = listen(sock, CMD_SOCK_QUEUE);
	else if (sock_type == DTP_SOCK)
		ret_l = listen(sock, DTP_SOCK_QUEUE);
	if ((sock_type == CMD_SOCK || sock_type == DTP_SOCK) && ret_l != 0)
	{
		ft_printf("Listening error\n");
		return (-1);
	}
	return (sock);
}

int		create_server(t_vault *vault, int port)
{
	int					sock;

	sock = new_socket(vault, port, CMD_SOCK);
	if (sock < 1)
	{
		ft_printf("new_socket error\n");
		return (-1);
	}

	ft_printf("Server is listening on port :%d\n", \
	ntohs(vault->n_info.cmd_sin.sin_port) );
	return (sock);
}
