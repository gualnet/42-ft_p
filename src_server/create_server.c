/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_server.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 15:52:10 by galy              #+#    #+#             */
/*   Updated: 2018/08/06 18:04:41 by galy             ###   ########.fr       */
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

int		type_spe(int sock, int sock_type)
{
	int		ret_l;

	if (sock_type == CMD_SOCK)
		ret_l = listen(sock, CMD_SOCK_QUEUE);
	else if (sock_type == DTP_SOCK)
		ret_l = listen(sock, DTP_SOCK_QUEUE);
	if ((sock_type == CMD_SOCK || sock_type == DTP_SOCK) && ret_l != 0)
	{
		ft_printf("Listening error\n");
		return (-1);
	}
	return (1);
}

/*
** socket address info internet form - here the cmd sock
*/

int		new_socket(t_vault *vault, int port, int sock_type)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	*sin;

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
		return (-3);
	}
	if (type_spe(sock, sock_type) == -1)
		return (-4);
	return (sock);
}

void	init_vault(t_vault *vault)
{
	vault->dtp_sock = 0;
	vault->cwd = loop_getcwd();
	vault->root_wd = ft_strdup(vault->cwd);
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
	cmd_pwd(vault);
	ft_printf("Server is listening on port :%d\n", \
	ntohs(vault->n_info.cmd_sin.sin_port));
	return (sock);
}
