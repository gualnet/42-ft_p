/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 17:37:42 by galy              #+#    #+#             */
/*   Updated: 2018/06/14 12:39:02 by galy             ###   ########.fr       */
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
	
	return (0);
}

/*
	State..
	0 - connexion init .. the client tries to connect wait for welcome msg
	1 - AUTH methode request... (this server have no auth protection) return 502 Commande non implémentée
	2 - srv waiting for cmd USER


*/

int		state_machine(t_vault *vault, uint state)
{
	while (state != 999)
	{
		if (state == 1)
		{
			TLS_non_implem(vault->cs);
		}
		// if (state == 2)
		// 	ft_printf("[%d] state 2 confirmed\n", getpid());
		state = read_sock(vault);
	}
	return (-1);
}