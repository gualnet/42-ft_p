/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatcher.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 14:31:42 by galy              #+#    #+#             */
/*   Updated: 2018/06/14 15:25:33 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "ftp_server.h"

int	TLS_non_implem(cs)
{
	// char *snd_msg = "434 \x0a\x0d";
	char *snd_msg = "502 \x0a\x0d";
	
	printf("[%d]Send :[%s]\n", getpid(), snd_msg);

	if (write(cs, snd_msg, ft_strlen(snd_msg) + 1) != (ssize_t)(ft_strlen(snd_msg) + 1))
		ft_printf("[%d]Echec envoi..\n", getpid());
	
	return (1);
}

int		dispatcher(t_vault *vault, char *buff)
{
	// ft_printf("[%d]====DISPATCHER====\n====%s====\n", getpid(), buff);
	if (strncmp(buff, "AUTH", 4) == 0)
		return (TLS_non_implem(vault->cs));
	else if (strncmp(buff, "USER", 4) == 0)
		return (cmd_user(vault, buff));
	else if (strncmp(buff, "PASS", 4) == 0)
		return (cmd_pass(vault, buff));
	// else if (strncmp(buff, "PWD", 3) == 0)
	// 	return (cmd_pwd(vault, buff));
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
