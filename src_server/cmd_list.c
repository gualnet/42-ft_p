/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 15:18:27 by galy              #+#    #+#             */
/*   Updated: 2018/08/06 14:24:25 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

char	*reparsing_dir_info(char *str)
{
	char	**banana;
	char	*msg;
	char	*tmp;
	int		i;

	i = 1;
	banana = ft_strsplit(str, '\n');
	tmp = banana[0];
	while (banana[i] != NULL)
	{
		tmp = ft_strjoin(tmp, " \n ");
		msg = ft_strjoin(tmp, banana[i]);
		free(tmp);
		tmp = msg;
		i++;
	}
	return (msg);
}

void	fork_work(t_vault *vault, int *tube)
{
	dup2(tube[1], STDOUT_FILENO);
	close(tube[0]);
	close(tube[1]);
	execl("/bin/ls", "ls", "-la", vault->cwd, NULL);
	exit(0);
}

char	*father_work(int *tube, pid_t pid)
{
	int				ret;
	char			*msg;
	char			*tmp;
	char			buf[R_BUFF_SIZE + 1];
	struct rusage	rusage;

	ret = 1;
	close(tube[1]);
	tmp = ft_strnew(1);
	while (ret > 0)
	{
		ft_bzero(buf, R_BUFF_SIZE);
		ret = read(tube[0], buf, R_BUFF_SIZE);
		msg = ft_strjoin(tmp, buf);
		free(tmp);
		tmp = msg;
	}
	ret = 0;
	while (ret == 0)
		ret = wait4(pid, &ret, 0, &rusage);
	return (msg);
}

char	*search_dir_info(t_vault *vault)
{
	int		tube[2];
	int		pid;
	char	*msg;

	if (pipe(tube) == -1)
	{
		ft_printf("[ERROR] SDI_ fork com...\n");
		exit(97);
	}
	if ((pid = fork()) == -1)
	{
		ft_printf("[ERROR] Fork failed to create.\n");
		exit(96);
	}
	if (pid == 0)
		fork_work(vault, tube);
	if (pid != 0)
		msg = father_work(tube, pid);
	return (ft_strdup(msg));
}

int		cmd_list(t_vault *vault)
{
	int				status;
	int				option;
	pid_t			cp_pid;
	struct rusage	rusage;

	if ((cp_pid = wait_for_conn(vault)) == -1)
		list_cmd_response(vault, 5, 0);
	if (vault->csc != -1)
		list_cmd_response(vault, 1, 0);
	if (vault->csd != -1)
	{
		list_dtp_response(vault);
		exit(0);
	}
	option = 0;
	if (vault->csc != -1)
	{
		wait4(cp_pid, &status, option, &rusage);
		list_cmd_response(vault, 0, status);
	}
	return (0);
}
