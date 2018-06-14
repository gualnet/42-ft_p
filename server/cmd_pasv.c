/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pasv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 18:34:21 by galy              #+#    #+#             */
/*   Updated: 2018/06/14 18:41:42 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

char	*build_pasive_addr(t_vault *vault)
{
	printf("[%d] \n", getpid(), inet_ntoa(vault->) );
}

void	pasv_response(t_vault *vault)
{
	char *msg;

	msg = "227 \x0a\x0d";
	
	build_pasive_addr();

	sender_sock(vault, msg);
	exit(0);
}

int		cmd_pasv(t_vault *vault)
{
	type_response(vault);
	return (0);
}