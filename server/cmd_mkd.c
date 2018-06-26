/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mkd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 19:30:13 by galy              #+#    #+#             */
/*   Updated: 2018/06/26 15:41:44 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"


void	mkd_cmd_response(t_vault *vault, int status)
{
	char *msg;

	msg = "";
	if (status == 1)
		msg = "257 New directory created.\x0a\x0d";
	else if (status == -4)
		msg = "451 File transfer aborted, local processing error.\x0a\x0d";
	else if (status == -5)
		msg = "501 Syntax error in parameters or arguments\x0a\x0d";
	sender_sock(vault, msg);	
}

int		create_dir(char *dir_name)
{
	pid_t	pid;
	int		status;
	int		option;
	struct	rusage rusage;

	option = 0;
	if ((pid = fork()) < 0) //echec
	{
		// ft_printf("MKD fork failed\n");
		return (-4);
	}
	if (pid == 0) // fork
	{
		execl("/bin/mkdir", "mkdir", "-p", dir_name, NULL);
		exit(0);
	}
	if (pid != 0) // father
		wait4(pid, &status, option, &rusage);
	return (1);
}

char	*prep_dir_creat(char *cmd)
{
	char *dir;
	char *tmp;


	if ((dir = ft_strdup(cmd + 4)) == NULL)
		return (NULL);
	// ft_printf("STEP1[%s]\n", dir);
	if ((tmp = ft_strchr(dir, '\r')) != NULL)
		tmp[0] = '\0';
	// ft_printf("STEP2[%s]\n", dir);
	return (dir);
	
}

int		cmd_mkd(t_vault *vault, char *cmd)
{
	int ret;
	char *tmp;

	ret = 0;
	if (verif_cmd_minimum_len(cmd, ML_MKD) != 1)
		mkd_cmd_response(vault, -5);
	else if ((tmp = prep_dir_creat(cmd)) == NULL)
		mkd_cmd_response(vault, -4);
	else if ((ret = create_dir(tmp)) < 0)
		mkd_cmd_response(vault, ret);
	mkd_cmd_response(vault, ret);
	return (1);
}

// int		cmd_mkd(t_vault *vault, char *cmd)
// {
// 	int ret;

// 	if (verif_cmd_minimum_len(cmd, ML_MKD) != 1)
// 	{
// 		mkd_cmd_response(vault, -5);
// 		return (-1);
// 	}
// 	if (ret = prep_dir_creat(vault, cmd) < 0)
// 	{
// 		mkd_cmd_response(vault, ret);
// 		return (-1);
// 	}
// 	if ((ret = create_dir(vault)) < 0)
// 	{
// 		mkd_cmd_response(vault, ret);
// 		return (-1)
// 	}
// 	mkd_cmd_response(vault, ret);
// 	return (1);
// }