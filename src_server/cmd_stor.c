/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_stor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 08:49:15 by galy              #+#    #+#             */
/*   Updated: 2018/08/20 17:58:50 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

/*
** 125 Canal de données déjà ouvert; début de transfert.
** 150 Statut de fichier vérifié; ouverture de canal de données en cours
** 226 Fermeture du canal de données.
**	Service terminé (par exemple, transfert de fichier ou avortement).
** 250 Service fichier terminé.
** 425 Erreur d'ouverture du canal de données.
** 426 Connexion fermée, transfert interrompu
** 451 Service interrompu. Erreur locale de traitement.
** 501 Erreur de syntaxe dans le paramètres ou arguments.
*/

void	stor_cmd_response(t_vault *vault, int status)
{
	char *msg;

	msg = "";
	if (status == 1)
		msg = "150 File checked, opening data connection...\x0a\x0d";
	else if (status == 2)
		msg = "125 Data connection open...\x0a\x0d";
	else if (status == 3)
		msg = "226 Requested file action successful, "
		"closing data connection.\x0a\x0d";
	else if (status == -1)
		msg = "451 Requested action aborted: "
		"local error in processing\x0a\x0d";
	else if (status == -2)
		msg = "425 Error opening data connection.\x0a\x0d";
	else if (status == -5)
		msg = "501 Syntax error in parameters or arguments\x0a\x0d";
	ft_printf("MSG TO SEND [%s]\n", msg);
	sender_sock(vault, msg);
}

int		stor_dtp_listen(t_vault *vault, t_file_info *fi)
{
	char	*data;
	ssize_t	data_size;

	data_size = 0;
	if ((data = dtp_receiver(vault->csd, &data_size)) == NULL)
	{
		ft_printf("[ERROR] Data reception failed\n");
		return (-1);
	}
	if (write(fi->fd, data, data_size) < 0)
		ft_printf("[ERROR] Unable to write into \'%s\'\n", fi->path);
	return (1);
}

int		prep_transfer_stor(t_vault *vault, char *file_name, t_file_info *fi)
{
	char	*tmp;

	tmp = ft_strjoin(vault->cwd, "/");
	fi->path = ft_strjoin(tmp, file_name);
	free(tmp);
	if ((tmp = ft_strstr(fi->path, "\x0a\x0d")) != NULL)
		tmp[0] = '\0';
	else if ((tmp = ft_strchr(fi->path, '\x0a')) != NULL)
		tmp[-1] = '\0';
	else
		return (-5);
	if ((fi->fd = open(fi->path, O_RDWR | O_NONBLOCK | O_CREAT, 0640)) < 0)
		return (-1);
	return (1);
}

void	stor_father_fork_work(t_vault *vault, t_file_info *fi, pid_t cp_pid)
{
	int				status;
	int				option;
	struct rusage	rusage;

	option = 0;
	if (vault->csc != -1)
		stor_cmd_response(vault, 2);
	if (vault->csd != -1)
	{
		if (stor_dtp_listen(vault, fi) < 0)
			exit(1);
		ft_printf("[%d] fork dtp close\n", getpid());
		exit(0);
	}
	wait4(cp_pid, &status, option, &rusage);
}

int		cmd_stor(t_vault *vault, char *cmd)
{
	t_file_info	fi;
	char		*file_name;
	int			ret;
	pid_t		cp_pid;

	ft_printf("CMD [%s]\n", cmd);
	if (verif_cmd_minimum_len(cmd, ML_STOR) != 1)
	{
		stor_cmd_response(vault, -5);
		return (-1);
	}
	file_name = ft_strdup(cmd + 5);
	ft_printf("filename [%s]\n", file_name);
	if ((ret = prep_transfer_stor(vault, file_name, &fi)) < 0)
		stor_cmd_response(vault, ret);
	if (ret < 0)
		return (-1);
	if ((cp_pid = wait_for_conn(vault)) == -1)
		stor_cmd_response(vault, -2);
	stor_father_fork_work(vault, &fi, cp_pid);
	close(fi.fd);
	free(fi.path);
	free(file_name);
	return (0);
}
