/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_retr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/21 16:52:44 by galy              #+#    #+#             */
/*   Updated: 2018/07/12 21:28:01 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

// 125 Canal de données déjà ouvert; début de transfert.
// 150 Statut de fichier vérifié; ouverture de canal de données en cours.
// 226 Fermeture du canal de données. Service terminé (par exemple, transfert defichier ou avortement)
// 250 Service fichier terminé.
// 421 Service non disponible, canal de contrôle fermé. Répondu à toute commande lorsque la fermeture imminente du service est prévue.
// 425 Erreur d'ouverture du canal de données.
// 426 Connexion fermée, transfert interrompu.
// 450 Service fichier non traité. Fichier non disponible (ex., fichier verrouillé par un autre utilisateur).
// 451 Service interrompu. Erreur locale de traitement.
// 452 Service interrompu. Espace insuffisant.
// 500 Erreur de syntaxe, commande non reconnue. Inclut le cas d'une ligne de commande trop longue.
// 501 Erreur de syntaxe dans le paramètres ou arguments.
// 530 Session non ouverte.
// 551 Service interrompu. Type de page inconnu.
// 552 Service fichier interrompu. Quota dépassé (pour le répertoire ou compte courant).

void	retr_cmd_response(t_vault *vault, int status)
{
	char	*msg;

	msg = "";
	if (status == 1)
		msg = "150 File checked, opening data connection...\x0a\x0d";
	else if (status == 2)
		msg = "125 Data connection open, transfert starting...\x0a\x0d";
	else if (status == 3)
		msg = "226 Requested file action successful, closing data connection.\x0a\x0d";
	else if (status == -2)
		msg = "425 Error opening data connection.\x0a\x0d";
	else if (status == -3)
		msg = "501 Syntax error in parameters or arguments\x0a\x0d";
	else
		msg = "451 File transfer aborted, local processing error.\x0a\x0d";
	
	sender_sock(vault, msg);
}

void	retr_dtp_response(t_vault *vault, t_file_info *fi)
{
	if (fi->fstat.st_size < 80000000)
	{
		// ft_printf("DTP FILE SENDER START\n");
		if (sender_dtp_bin(vault, fi->fdump, fi->fstat.st_size) < 0)
		{
			// ft_printf("DTP FILE SENDER NOK\n");
			exit(-1);
		}
	}
	exit(0);
}

int		prep_transfer_retr(t_vault *vault, char *file, t_file_info *fi)
{
	char		*tmp;

	tmp = ft_strjoin(vault->cwd, "/");
	fi->path = ft_strjoin(tmp, file);
	// ft_printf("file path to download[%s]\n", fi->path);
	free(tmp);
	truncate_end_signs(fi->path);
	// ft_printf("file path to download[%s]\n", fi->path);
	if ((fi->fd = open(fi->path, O_RDONLY | O_NONBLOCK)) < 0)
		return (-1);
	if (fstat(fi->fd, &fi->fstat) == -1)
		return (-2);
	if ((fi->fdump = (void*)mmap(NULL, fi->fstat.st_size, PROT_READ, \
	MAP_FILE | MAP_PRIVATE, fi->fd, 0)) == MAP_FAILED)
		return (-3);
	return (1);
}

void	clear_fi(t_file_info *fi)
{
	free(fi->path);

}

int		cmd_retr(t_vault *vault, char *cmd)
{
	int			fd;
	char		*file;
	pid_t		cp_pid;
	t_file_info	fi;

	if (verif_cmd_minimum_len(cmd, ML_RETR) != 1)
	{
		retr_cmd_response(vault, -3);
		return (-1);
	}
	file = cmd + 5;
	// ft_printf("file to download[%s]\n", file);
	if ((fd = prep_transfer_retr(vault, file, &fi)) < 0)
	{
		// ft_printf("[%d] Pb in prep_transfert fd[%d]\n", getpid(), fd);
		retr_cmd_response(vault, 1); //file check.. open dtp
		return (-1);
	}
	if ((cp_pid = wait_for_conn(vault)) == -1)
		retr_cmd_response(vault, -2); // dtp connexion error
	if (vault->csc != -1)
		retr_cmd_response(vault, 2);
	if (vault->csd != -1)
	{
		retr_dtp_response(vault, &fi);
		// ft_printf("[%d] fork dtp close\n", getpid());
		exit(0);
	}
	close(fd);
	munmap(fi.fdump, fi.fstat.st_size);
	clear_fi(&fi);
	retr_cmd_response(vault, 3);

	return (0);
}