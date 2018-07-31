/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_rmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 18:47:07 by galy              #+#    #+#             */
/*   Updated: 2018/06/26 19:13:52 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

void	rmd_cmd_response(t_vault *vault, int status)
{
	char *msg;

	msg = "";
	if (status == 1)
		msg = "250 Requested directory action completed.\x0a\x0d";
	else if (status == -1)
		msg = "451 Requested directory action aborted, "
		"local processing error.\x0a\x0d";
	else if (status == -2)
		msg = "450 Requested directory action not taken, "
		"directory unavailable\x0a\x0d";
	else if (status == -5)
		msg = "501 Syntax error in parameters or arguments\x0a\x0d";
	sender_sock(vault, msg);
}

int		del_dir(char *dir)
{
	pid_t	pid;
	int		status;
	int		option;
	struct	rusage rusage;

	option = 0;
	if ((pid = fork()) < 0) //echec
		return (-4);
	if (pid == 0) // fork
	{
		execl("/bin/rm", "rm", "-r", dir, NULL);
		exit(0);
	}
	if (pid != 0) // father
		wait4(pid, &status, option, &rusage);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
	{
		ft_printf("le dir \"%s\" n'est pas dispo return[%d]\n", dir);
		return (-2);
	}
	ft_printf("le dir \"%s\" a ete supp return[%d]\n", dir);
	return (1);
}

char	*prep_dir_name(char *cmd)
{
	char	*dir;
	char	*tmp;

	if ((dir = ft_strdup(cmd + 4)) == NULL)
		return (NULL);
	if ((tmp = ft_strchr(dir, '\r')) != NULL)
		tmp[0] = '\0';
	return (dir);
}

int		cmd_rmd(t_vault *vault, char *cmd)
{
	char	*dir;
	int		ret;

	if (verif_cmd_minimum_len(cmd, ML_RMD) != 1)
	{
		rmd_cmd_response(vault, -5);
		return (-1);
	}
	if ((dir = prep_dir_name(cmd)) == NULL)
	{
		rmd_cmd_response(vault, -1);
		return (-1);
	}
	ft_printf("DIR TO DELETE[%s]\n", dir);
	ret = del_dir(dir);
	rmd_cmd_response(vault, ret);
	free(dir);
	return (0);
}
