/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 14:31:42 by galy              #+#    #+#             */
/*   Updated: 2018/07/26 12:49:48 by galy             ###   ########.fr       */
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
	else if (strncmp(buff, "LIST", 4) == 0)
		return (cmd_list(vault));
	else if (strncmp(buff, "CWD", 3) == 0)
		return (cmd_cwd(vault, buff));
	else if (strncmp(buff, "RETR", 4) == 0)
		return (cmd_retr(vault, buff));
	else if (strncmp(buff, "STOR", 4) == 0)
		return (cmd_stor(vault, buff));
	else if (strncmp(buff, "MKD", 3) == 0)
		return (cmd_mkd(vault, buff));
	else if (strncmp(buff, "MODE", 4) == 0)
		return (cmd_mode(vault));
	else if (strncmp(buff, "PORT", 4) == 0)
		return (cmd_port(vault));
	else if (strncmp(buff, "DELE", 4) == 0)
		return (cmd_dele(vault, buff));
	else if (strncmp(buff, "RMD", 3) == 0)
		return (cmd_rmd(vault, buff));
	else if (strncmp(buff, "NOOP", 4) == 0)
		return (cmd_noop(vault));
	else if (strncmp(buff, "QUIT", 4) == 0 || buff[0] == '\0')
	{
		ft_printf("QUIT BYEBYE\n");
		return (999);
	}
	else
	{
		ft_printf("[%d] Commande non implem ", getpid());
		sender_sock(vault, "502 \x0a\x0d");
	}


	return (0);
}
