/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 14:31:42 by galy              #+#    #+#             */
/*   Updated: 2018/06/15 18:11:18 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ftp_server.h"

int	cmd_auth(t_vault *vault)
{
	char *msg;

	msg = "502 \x0a\x0d";
	sender_sock(vault, msg);
	return (1);
}

int		dispatcher(t_vault *vault, char *buff)
{
	// ft_printf("[%d]====DISPATCHER====\n====%s====\n", getpid(), buff);
	if (strncmp(buff, "AUTH", 4) == 0)
		return (cmd_auth(vault));
	else if (strncmp(buff, "USER", 4) == 0)
		return (cmd_user(vault, buff));
	else if (strncmp(buff, "PASS", 4) == 0)
		return (cmd_pass(vault, buff));
	else if (strncmp(buff, "PWD", 3) == 0)
		return (cmd_pwd(vault));
	else if (strncmp(buff, "SYST", 4) == 0)
		return (cmd_syst(vault));
	else if (strncmp(buff, "TYPE", 4) == 0)
		return (cmd_type(vault));
	else if (strncmp(buff, "PASV", 4) == 0)
		return (cmd_pasv(vault));
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
