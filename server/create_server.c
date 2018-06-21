/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_server.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:52:10 by galy              #+#    #+#             */
/*   Updated: 2018/06/21 16:47:44 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

void	reg_vault_sin_param(t_vault *vault, int port, int sock_type)
{
	if (sock_type == CMD_SOCK)
	{
		vault->n_info.cmd_sin.sin_family = AF_INET;
		vault->n_info.cmd_sin.sin_port = htons(port);
		vault->n_info.cmd_sin.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else if (sock_type == DTP_SOCK)
	{
		vault->n_info.dtp_sin.sin_family = AF_INET;
		vault->n_info.dtp_sin.sin_port = htons(port);
		vault->n_info.dtp_sin.sin_addr.s_addr = htonl(INADDR_ANY);
	}
}

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
	
	reg_vault_sin_param(vault, port, sock_type);
	if (sock_type == CMD_SOCK)
		sin = &vault->n_info.cmd_sin;
	if (sock_type == DTP_SOCK)
		sin = &vault->n_info.dtp_sin;
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

void	init_vault(t_vault *vault)
{
	vault->dtp_sock = 0;
}

int		create_server(t_vault *vault, int port)
{
	int	sock;

	init_vault(vault);
	sock = new_socket(vault, port, CMD_SOCK);
	if (sock < 1)
	{
		ft_printf("new server socket error\n");
		return (-1);
	}

	ft_printf("Server is listening on port :%d\n", \
	ntohs(vault->n_info.cmd_sin.sin_port) );
	return (sock);
}

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
		{
			ft_printf("good sock [%d]\n", sock);
			break ;
		}
			ft_printf("bad sock [%d]\n", sock);
		i++;
	}
	if (sock < 1)
	{
		ft_printf("new dtp socket error (sock[%d])\n", sock);
		return (-1);
	}
	ft_printf("Data transfert socket listening on port :%d\n", \
	ntohs(vault->n_info.dtp_sin.sin_port) );
	return (sock);
}