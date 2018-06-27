/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 17:37:42 by galy              #+#    #+#             */
/*   Updated: 2018/06/17 14:24:15 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

/*
	State..
	0 - connexion init .. the client tries to connect wait for welcome msg
	1 - AUTH methode request... (this server have no auth protection) return 502 Commande non implémentée
	2 - srv waiting for cmd USER


*/

int		state_machine(t_vault *vault, uint state)
{
	char	buff[R_BUFF_SIZE];

	while (state != 999)
	{
		read_sock(vault, buff);
		state = dispatcher(vault, buff);
	}
	return (-1);
}
