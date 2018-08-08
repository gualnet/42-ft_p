/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 14:44:23 by galy              #+#    #+#             */
/*   Updated: 2018/08/08 18:36:05 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

void	free_vault(t_vault *vault)
{
	free(vault->name);
}

int		main(int argc, char **argv)
{
	int					port;
	int					cmd_sock;
	t_vault				vault;

	if (argc != 2)
	{
		usage(argv[0]);
		return (-1);
	}
	ft_printf("[INFO] MASTER PROCESS PID [%d]\n", (int)getpid());
	port = ft_atoi(argv[1]);
	if ((cmd_sock = create_server(&vault, port)) < 0)
		return (-1);
	wait_for_cmd_conn(&vault, cmd_sock);
	if (vault.csc != -1)
	{
		ft_printf("[%d] closing client socket connector\n", getpid());
		close(vault.csc);
	}
	close(cmd_sock);
	free_vault(&vault);
	return (1);
}
