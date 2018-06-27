/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_syst.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 17:15:25 by galy              #+#    #+#             */
/*   Updated: 2018/06/26 15:56:40 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

void	syst_response(t_vault *vault)
{
	char	*msg;

	msg = "";
	#ifdef __gnu_linux__
		msg = "200 UNIX\x0a\x0d";
	#endif
	#ifdef __APPLE__
		msg = "200 MACHOS\x0a\x0d";
	#endif
	#ifdef __MACH__
		msg = "200 MACHOS\x0a\x0d";
	#endif
	sender_sock(vault, msg);
}

int		cmd_syst(t_vault *vault)
{
	syst_response(vault);
	return (0);
}