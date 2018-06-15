/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pasv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 18:34:21 by galy              #+#    #+#             */
/*   Updated: 2018/06/15 18:10:35 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

char	*build_pasive_addr(t_vault *vault)
{
	struct sockaddr_in *sin;

	sin = &vault->n_info.cmd_sin;
	printf("[%d]inet : [%x]:[%d] \n", getpid(), \
	ntohl(sin->sin_addr.s_addr), ntohs(sin->sin_port));
	return ("MON CUL\n");
}

void	pasv_response(t_vault *vault)
{
	char *msg;

	msg = "227 \x0a\x0d";
	
	msg = build_pasive_addr(vault);

	sender_sock(vault, msg);
	exit(0);
}

int		cmd_pasv(t_vault *vault)
{
	pasv_response(vault);
	return (0);
}