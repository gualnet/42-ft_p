/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_retr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 16:52:44 by galy              #+#    #+#             */
/*   Updated: 2018/08/06 18:06:39 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

/*
** 125 Canal de données déjà ouvert; début de transfert.
** 150 Statut de fichier vérifié; ouverture de canal de données en cours.
** 226 Fermeture du canal de données.
**	Service terminé (par exemple, transfert defichier ou avortement)
** 250 Service fichier terminé.
** 421 Service non disponible, canal de contrôle fermé. Répondu à toute
**	commande lorsque la fermeture imminente du service est prévue.
** 425 Erreur d'ouverture du canal de données.
** 426 Connexion fermée, transfert interrompu.
** 450 Service fichier non traité.
**	Fichier non disponible (ex., fichier verrouillé par un autre utilisateur).
** 451 Service interrompu. Erreur locale de traitement.
** 452 Service interrompu. Espace insuffisant.
** 500 Erreur de syntaxe, commande non reconnue.
**	Inclut le cas d'une ligne de commande trop longue.
** 501 Erreur de syntaxe dans le paramètres ou arguments.
** 530 Session non ouverte.
** 551 Service interrompu. Type de page inconnu.
** 552 Service fichier interrompu.
**	Quota dépassé (pour le répertoire ou compte courant).
*/

void	retr_cmd_response(t_vault *vault, int status)
{
	char	*msg;

	msg = "";
	if (status == 1)
		msg = "150 File checked, opening data connection...\x0a\x0d";
	else if (status == 2)
		msg = "125 Data connection open, transfert starting...\x0a\x0d";
	else if (status == 3)
		msg = "226 Requested file action successful, "
		"closing data connection.\x0a\x0d";
	else if (status == -2)
		msg = "425 Error opening data connection.\x0a\x0d";
	else if (status == -3)
		msg = "501 Syntax error in parameters or arguments\x0a\x0d";
	else if (status == -4)
		msg = "226 Requested file action unsuccessful, "
		"closing data connection.\x0a\x0d";
	else
		msg = "451 File transfer aborted, local processing error.\x0a\x0d";
	ft_printf("[SEND] [%s]\n", msg);
	sender_sock(vault, msg);
}

void	retr_dtp_response(t_vault *vault, t_file_info *fi)
{
	if (fi->fstat.st_size < 80000000)
	{
		if (sender_dtp_bin(vault, fi->fdump, fi->fstat.st_size) < 0)
		{
			ft_printf("DTP FILE SENDER NOK\n");
			exit(-1);
		}
	}
}

int		cmd_retr_2(t_vault *vault, pid_t cp_pid, int ret, t_file_info *fi)
{
	int				status;
	int				option;
	struct rusage	rusage;

	option = 0;
	if (cp_pid != 0)
		wait4(cp_pid, &status, option, &rusage);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		ft_printf("Une erreur la\n");
		return (-2);
	}
	close(fi->fd);
	munmap(fi->fdump, fi->fstat.st_size);
	free(fi->path);
	if (ret > 0)
		retr_cmd_response(vault, 3);
	return (1);
}

void	retr_father_son_work(t_vault *vault, int ret, t_file_info *fi)
{
	if (vault->csc != -1)
		retr_cmd_response(vault, ret);
	if (vault->csd != -1)
	{
		if (ret > 0)
			retr_dtp_response(vault, fi);
		ft_printf("[%d] fork dtp close\n", getpid());
		exit(0);
	}
}

int		cmd_retr(t_vault *vault, char *cmd)
{
	char		*file;
	pid_t		cp_pid;
	int			ret;
	t_file_info	fi;

	if (verif_cmd_minimum_len(cmd, ML_RETR) != 1)
	{
		retr_cmd_response(vault, -3);
		return (-1);
	}
	file = cmd + 5;
	if ((ret = prep_transfer_retr(vault, file, &fi)) < 0)
	{
		if (ret < -1)
			ft_printf("[%d][ERROR] Abort file transfer.\n", getpid());
	}
	if ((cp_pid = wait_for_conn(vault)) == -1)
		retr_cmd_response(vault, -2);
	retr_father_son_work(vault, ret, &fi);
	return (cmd_retr_2(vault, cp_pid, ret, &fi));
}
