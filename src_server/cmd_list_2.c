/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/06 14:24:10 by galy              #+#    #+#             */
/*   Updated: 2018/08/06 14:25:16 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

void	list_dtp_response(t_vault *vault)
{
	char			*msg;

	msg = search_dir_info(vault);
	// ft_printf("info: [%s]\n", msg);
	if (ft_strlen(msg) == 0)
		exit(99);
	msg = reparsing_dir_info(msg);
	// ft_printf("info: [%s]\n", msg);
	sender_dtp(vault, msg);
	free(msg);
}

void	list_cmd_response(t_vault *vault, int status, int wstatus)
{
	char *msg;

	msg = "";
	if (status == 0)
	{
		if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 0)
			msg = "250 Requested file action completed..\x0a\x0d";
		else if ((WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 0) || \
		WIFSIGNALED(wstatus))
			msg = "451 Local error in processing...\x0a\x0d";
		else if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 99)
			msg = "450 Requested Directory action not taken. \
			Directory unavailable...\x0a\x0d";
	}
	else if (status == 1)
		msg = "125 Data connection already open; transfer starting.\x0a\x0d";
	else if (status == 2)
		msg = "250 Requested file action completed.\x0a\x0d";
	else if (status == 5)
		msg = "425 Error opening data connection.\x0a\x0d";
	sender_sock(vault, msg);
}
