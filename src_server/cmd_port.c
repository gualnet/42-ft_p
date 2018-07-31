/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_port.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 16:39:42 by galy              #+#    #+#             */
/*   Updated: 2018/06/26 16:41:08 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		cmd_port(t_vault *vault)
{
	char *msg;

	msg = "500 Illegal PORT command.\x0a\x0d";
	sender_sock(vault, msg);
	return (0);
}
