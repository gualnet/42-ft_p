/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_noop.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 16:03:51 by galy              #+#    #+#             */
/*   Updated: 2018/08/06 14:27:29 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		cmd_noop(t_vault *vault)
{
	char *msg;

	msg = "200 NOOP OK MAGGLE ;).\x0a\x0d";
	sender_sock(vault, msg);
	return (0);
}