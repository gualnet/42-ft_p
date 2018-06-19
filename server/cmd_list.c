/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 15:18:27 by galy              #+#    #+#             */
/*   Updated: 2018/06/19 18:22:30 by galy             ###   ########.fr       */
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

int		search_dir_info(void)
{
	int		tube[2];
	int		pid;
	char	buf[1024];
	int		b_size;
	int		ret;
	b_size = 1023;
	if (pipe(tube) == -1)
	{
		ft_printf("SDI_ error creating pipe\n");
		exit(97);
	}
	if ((pid = fork()) == -1)
	{
		ft_printf("SDI_ error creating pipe\n");
		exit(96);
	}
	if (pid == 0) //fils
	{
		dup2 (tube[1], STDOUT_FILENO);
		close(tube[0]);
		close(tube[1]);
		execl("/bin/sh", "ls -la", NULL);
		exit(0);
	}
	if (pid != 0) //parent
	{
		close(tube[1]);
		ret = read(tube[0], buf, b_size);
		ft_printf("SORTIE TUBE: (%s)\n", buf);

	}
	return (0);
}

void	list_dtp_response(t_vault *vault)
{
	// char			*msg;
	// char			*tmp1;
	//
	struct dirent	*dirent;
	DIR				*fdrep;

	ft_printf("DIR to open [%s]\n", vault->cwd);
	if ((fdrep = opendir(vault->cwd)) == NULL)
		exit(98);
	dirent = (void*)1;

	search_dir_info();
	while (dirent != NULL)
	{
		dirent = readdir(fdrep);
		if (dirent != NULL)
		{



			// msg = ft_strjoin(dirent->d_name, " ");
			// tmp1 = ft_strjoin(msg, ft_itoa(dirent->d_type));
			// free(msg);
			// msg = ft_strjoin(tmp1, " \x0a\x0d");
			// free(tmp1);
			// if (sender_dtp(vault, msg) == -1)
			// {
			// 	ft_printf("C'est la meeeeeeeeeerrde !!!!\n");
			// 	exit(99);
			// }
			// free(msg);
			
		}
	}
	closedir(fdrep);
	
	// struct dirent {
    // ino_t          d_ino;       /* numéro d'inœud */
    // off_t          d_off;       /* décalage jusqu'à la dirent suivante */
    // unsigned short d_reclen;    /* longueur de cet enregistrement */
    // unsigned char  d_type;      /* type du fichier */
    // char           d_name[256]; /* nom du fichier */
	// };
	
}

void	list_cmd_response(t_vault *vault, int status, int wstatus)
{
	char *msg;
	
	msg = "";
	if (status == 0)
	{
		if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 0)
		{
			ft_printf("LE FILS A QUITTE CORRECTEMENT\n");
			msg = "250 Service fichier terminé..\x0a\x0d";
		}
		else if ((WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 0) || \
		WIFSIGNALED(wstatus))
		{
			ft_printf("LE FILS A QUITTE sur erreur\n");
			msg = "451 Erreur locale de traitement..\x0a\x0d";
		}
	}
	else if (status == 1)
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

int		cmd_list(t_vault *vault)
{
	int		status;
	int		option;
	struct	rusage rusage;
	pid_t	cp_pid;
	//check data connexion
	if ((cp_pid = wait_for_conn(vault)) == -1)
		list_cmd_response(vault, 5, 0);
	if (vault->csc != -1)
		list_cmd_response(vault, 1, 0);
	if (vault->csd != -1)
	{
		list_dtp_response(vault);
		ft_printf("[%d] fork dtp close\n", getpid());
		exit(0);
	}
	sleep(1); // test
	
	option = 0;
	ft_printf("TOTO1\n");
	if (vault->csc != -1)
	{
		wait4(cp_pid, &status, option, &rusage);
		// ft_printf("[%d] TEST {status[%d]}{optin[%d]}} \n", \
		// status, option);
		// 
		// if (WIFSIGNALED(status))
		// 	ft_printf("LE FILS A QUITTE SUR SIGNAL\n");
		list_cmd_response(vault, 0, status);
	}
	ft_printf("TOTO2\n");

	return (0);
}

// msg = malloc(15 * sizeof(void*));
// 	msg[0] = "drwxr-xr-x  14 kriz  staff   448B 18 jui 19:22 .git";
// 	msg[1] = "-rw-r--r--   1 kriz  staff   430B 12 jui 14:41 .gitignore";
// 	msg[2] = "drwxr-xr-x   5 kriz  staff   160B 14 jui 11:05 .vscode";
// 	msg[3] = "-rw-r--r--@  1 kriz  staff   2,8K 18 jui 18:38 Makefile";
// 	msg[4] = "-rw-r--r--   1 kriz  staff   132B 12 jui 14:41 README.md";
// 	msg[5] = "drwxr-xr-x   2 kriz  staff    64B 12 jui 14:43 client";
// 	msg[6] = "-rwxr-xr-x   1 kriz  staff    98K 18 jui 19:18 ftp_server";
// 	msg[7] = "drwxr-xr-x   7 kriz  staff   224B 13 jui 18:57 inc"; 
// 	msg[8] = "drwxr-xr-x   7 kriz  staff   224B 18 jui 19:18 libft";
// 	msg[9] = "drwxr-xr-x   3 kriz  staff    96B 18 jui 19:18 obj";
// 	msg[10] = "drwxr-xr-x  18 kriz  staff   576B 18 jui 18:22 server";
// 	msg[11] = NULL;
// 	msg[12] = NULL;
// 	msg[13] = NULL;
// int i = 0;
// while (msg[i] != NULL)
// {
// 	if (sender_dtp(vault, msg[i]) == -1)
// 	{
// 		ft_printf("C'est la meeeeeeeeeerrde !!!!\n");
// 		exit(99);
// 	}
// 	i++;
// }