/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_syst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 17:15:25 by galy              #+#    #+#             */
/*   Updated: 2018/08/06 17:54:28 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

void	syst_response(t_vault *vault)
{
	char	*msg;

	msg = "";
	if (SYST_ID == 1)
		msg = "200 UNIX\x0a\x0d";
	if (SYST_ID == 2)
		msg = "200 MACHOS\x0a\x0d";
	sender_sock(vault, msg);
}

int		cmd_syst(t_vault *vault)
{
	syst_response(vault);
	return (0);
}
