/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_noop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 16:03:51 by galy              #+#    #+#             */
/*   Updated: 2018/06/26 16:05:15 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

void	noop_response(t_vault *vault)
{
	char *msg;

	msg = "200 NOOP OK MAGGLE ;).\x0a\x0d";
	
	sender_sock(vault, msg);
}

int		cmd_noop(t_vault *vault)
{
	noop_response(vault);
	return (0);
}
