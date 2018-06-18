/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 15:18:27 by galy              #+#    #+#             */
/*   Updated: 2018/06/18 19:30:25 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

// 125 Canal de données déjà ouvert; début de transfert.
// 150 Statut de fichier vérifié; ouverture de canal de données en cours.
// 226 Fermeture du canal de données. Service terminé (par exemple, transfert de fichier ou avortement).
// 250 Service fichier terminé
// 425 Erreur d'ouverture du canal de données.
// 426 Connexion fermée, transfert interrompu.
// 450 Service fichier non traité. Fichier non disponible (ex., fichier verrouillé par un autre utilisateur).
// 451 Service interrompu. Erreur locale de traitement.

void	list_dtp_response(t_vault *vault)
{
	char	**msg;
	int		i;

	msg = malloc(15 * sizeof(void*));

	msg[0] = "drwxr-xr-x  14 kriz  staff   448B 18 jui 19:22 .git";
	msg[1] = "-rw-r--r--   1 kriz  staff   430B 12 jui 14:41 .gitignore";
	msg[2] = "drwxr-xr-x   5 kriz  staff   160B 14 jui 11:05 .vscode";
	msg[3] = "-rw-r--r--@  1 kriz  staff   2,8K 18 jui 18:38 Makefile";
	msg[4] = "-rw-r--r--   1 kriz  staff   132B 12 jui 14:41 README.md";
	msg[5] = "drwxr-xr-x   2 kriz  staff    64B 12 jui 14:43 client";
	msg[6] = "-rwxr-xr-x   1 kriz  staff    98K 18 jui 19:18 ftp_server";
	msg[7] = "drwxr-xr-x   7 kriz  staff   224B 13 jui 18:57 inc"; 
	msg[8] = "drwxr-xr-x   7 kriz  staff   224B 18 jui 19:18 libft";
	msg[9] = "drwxr-xr-x   3 kriz  staff    96B 18 jui 19:18 obj";
	msg[10] = "drwxr-xr-x  18 kriz  staff   576B 18 jui 18:22 server";
	msg[11] = NULL;
	msg[12] = 
	msg[13] = NULL;

	i = 0;
	while (msg[i] != NULL)
	{
		if (sender_dtp(vault, msg[i]) == -1)
		{
			ft_printf("C'est la meeeeeeeeeerrde !!!!\n");
			break ;
		}
		i++;
	}
}

void	list_cmd_response(t_vault *vault, int status)
{
	char *msg;
	
	if (status == 1)
	{
		msg = "125 \x0a\x0d";
		sender_sock(vault, msg);
	}
	else if (status == 2)
	{
		msg = "250 \x0a\x0d";
		sender_sock(vault, msg);
	}
	else if (status == 5)
	{
		msg = "425 \x0a\x0d";
		sender_sock(vault, msg);
	}
	
}

int		cmd_list(t_vault *vault)
{
	//check data connexion
	if (wait_for_conn(vault) == -1)
		list_cmd_response(vault, 5);
	if (vault->csc != -1)
		list_cmd_response(vault, 1);
	if (vault->csd != -1)
	{
		list_dtp_response(vault);
		ft_printf("[%d] fork dtp close", getpid());
		exit(0);
	}
	if (vault->csc != -1)
		list_cmd_response(vault, 2);

	return (0);
}
