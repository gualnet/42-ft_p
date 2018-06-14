/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_connexion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 16:51:48 by galy              #+#    #+#             */
/*   Updated: 2018/06/14 15:00:37 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		init_connexion(t_vault *vault)
{
	char *snd_msg = "220 \x0a\x0d";
	
	printf("[%d]Send :[%s]\n", getpid(), snd_msg);

	sender_sock(vault, snd_msg);
	
	return (0);
}