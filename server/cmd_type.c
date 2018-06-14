/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 15:50:35 by galy              #+#    #+#             */
/*   Updated: 2018/06/14 18:04:52 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

void	type_response(t_vault *vault)
{
	char *msg;

	msg = "200 \x0a\x0d";
	
	sender_sock(vault, msg);
}

int		cmd_type(t_vault *vault)
{
	type_response(vault);
	return (0);
}