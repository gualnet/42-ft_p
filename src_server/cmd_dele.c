/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_dele.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 17:46:48 by galy              #+#    #+#             */
/*   Updated: 2018/08/06 14:21:22 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

void	dele_cmd_response(t_vault *vault, int status)
{
	char *msg;

	msg = "";
	if (status == 1)
		msg = "250 Requested file action completed.\x0a\x0d";
	else if (status == -1)
		msg = "451 Requested file action aborted, "
		"local processing error.\x0a\x0d";
	else if (status == -2)
		msg = "450 Requested file action not taken, file unavailable\x0a\x0d";
	else if (status == -5)
		msg = "501 Syntax error in parameters or arguments\x0a\x0d";
	sender_sock(vault, msg);
}

char	*prep_file_name(char *cmd)
{
	char	*file;
	char	*tmp;

	if ((file = ft_strdup(cmd + 5)) == NULL)
		return (NULL);
	if ((tmp = ft_strchr(file, '\r')) != NULL)
		tmp[0] = '\0';
	return (file);
}

int		del_file(char *file)
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
		execl("/bin/rm", "rm", file, NULL);
		exit(0);
	}
	if (pid != 0)
		wait4(pid, &status, option, &rusage);
	if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
		return (-2);
	return (1);
}

int		cmd_dele(t_vault *vault, char *cmd)
{
	char	*file;
	int		ret;

	if (verif_cmd_minimum_len(cmd, ML_DELE) != 1)
	{
		dele_cmd_response(vault, -5);
		return (-1);
	}
	if ((file = prep_file_name(cmd)) == NULL)
	{
		dele_cmd_response(vault, -1);
		return (-1);
	}
	ft_printf("FILE TO DELETE[%s]\n", file);
	ret = del_file(file);
	dele_cmd_response(vault, ret);
	free(file);
	return (0);
}
