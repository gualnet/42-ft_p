/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_connexion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 16:51:48 by galy              #+#    #+#             */
/*   Updated: 2018/06/13 19:10:23 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		init_connexion(t_vault *vault)
{
	char *snd_msg = "220 \x0a\x0d";
	
	printf("[%d]Send :[%s]\n", getpid(), snd_msg);

	if (write(vault->cs, snd_msg, ft_strlen(snd_msg) + 1) != (ssize_t)(ft_strlen(snd_msg) + 1))
		ft_printf("[%d]Echec envoi..\n", getpid());
	
	return (0);
}