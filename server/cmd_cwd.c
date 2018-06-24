/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 16:20:17 by galy              #+#    #+#             */
/*   Updated: 2018/06/22 18:21:12 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

// 501 Erreur de syntaxe dans le paramètres ou arguments.
// 550 Service fichier non traité. Fichier non accessible (ex., fichier non trouvé, accèsrefusé).

void	cwd_dtp_response(t_vault *vault, int status)
{
	char *msg;
	
	if (status == 1)
		msg = "150 \x0a\x0d";
	else if (status == 5)
		msg = "501 Syntaxe Error.. \x0a\x0d";
	else
		msg = "550 \x0a\x0d";
	sender_sock(vault, msg);
}

void	cwd_cmd_response(t_vault *vault, int status)
{
	char *msg;
	
	msg = "";
	if (status == 1)
	{
		msg = "125 \x0a\x0d";
	}
	else if (status == 2)
	{
		msg = "250 \x0a\x0d";
	}
	else if (status == 5)
	{
		msg = "425 \x0a\x0d";
	}
		sender_sock(vault, msg);
}

void	goto_new_rep(t_vault *vault, char *cmd)
{
	char	*tmp;
	// char	*tmp2;

	free(vault->cwd);
	vault->cwd = ft_strdup(cmd + 4);
	ft_printf("=========%s========\n", vault->cwd);
	tmp = ft_strchr(vault->cwd, '\r');
	if (tmp != NULL)
	{
		tmp[0] = '\0';
		ft_printf("=========%s========\n", vault->cwd);

	}

}

int		cmd_cwd(t_vault *vault, char *cmd)
{

	goto_new_rep(vault, cmd);
	
		
	cwd_cmd_response(vault, 2);
	return (0);
}
