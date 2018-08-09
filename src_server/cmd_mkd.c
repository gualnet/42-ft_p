/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mkd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 19:30:13 by galy              #+#    #+#             */
/*   Updated: 2018/08/09 15:00:59 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

void	mkd_cmd_response(t_vault *vault, int status)
{
	char	*msg;

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
	pid_t			pid;
	int				status;
	int				option;
	struct rusage	rusage;

	option = 0;
	if ((pid = fork()) < 0)
		return (-4);
	if (pid == 0)
	{
		execl("/bin/mkdir", "mkdir", "-p", dir_name, NULL);
		exit(0);
	}
	if (pid != 0)
		wait4(pid, &status, option, &rusage);
	return (1);
}

char	*prep_dir_creat(char *cmd)
{
	char	*dir;
	char	*tmp;

	if ((dir = ft_strdup(cmd + 4)) == NULL)
		return (NULL);
	if ((tmp = ft_strchr(dir, '\r')) != NULL)
		tmp[0] = '\0';
	return (dir);
}

int		cmd_mkd(t_vault *vault, char *cmd)
{
	int		ret;
	char	*tmp;

	ret = 0;
	if (verif_cmd_minimum_len(cmd, ML_MKD) != 1)
		mkd_cmd_response(vault, -5);
	else if ((tmp = prep_dir_creat(cmd)) == NULL)
		mkd_cmd_response(vault, -4);
	else
	{
		ret = create_dir(tmp);
		mkd_cmd_response(vault, ret);
	}
	return (1);
}
