/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/17 15:18:27 by galy              #+#    #+#             */
/*   Updated: 2018/06/26 19:14:31 by galy             ###   ########.fr       */
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
		tmp = ft_strjoin(tmp, "\n");
		msg = ft_strjoin(tmp, banana[i]);
		free(tmp);
		tmp = msg;
		i++;
	}
	return (msg);
}

void	fork_work(t_vault *vault, int *tube)
{
	// ft_printf("======FORK WORK=====\n");
	dup2 (tube[1], STDOUT_FILENO);
	close(tube[0]);
	close(tube[1]);
	execl("/bin/ls", "ls", "-la", vault->cwd, NULL);
	exit(0);
}

char	*father_work(int *tube, pid_t pid)
{
	// ft_printf("======Father WORK=====\n");
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
		ret = wait4(pid, &ret, 0, &rusage); //wait pour la fin d'exec du fork pour faire propre
	return (msg);
}

char	*search_dir_info(t_vault *vault)
{
	int		tube[2];
	int		pid;
	char	*msg;

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
		fork_work(vault, tube);
	}
	if (pid != 0) //parent
	{
		msg = father_work(tube, pid);
	}
	return (ft_strdup(msg));
}

void	list_dtp_response(t_vault *vault)
{
	char			*msg;

	// ft_printf("DIR to open [%s]\n", vault->cwd);

	msg = search_dir_info(vault);
	// ft_printf("INTERMED MSG[%d][%s]\n", ft_strlen(msg), msg);
	if (ft_strlen(msg) == 0)
		exit(99);
	msg = reparsing_dir_info(msg);
	sender_dtp(vault, msg);
	free(msg);
}

void	list_cmd_response(t_vault *vault, int status, int wstatus)
{
	char *msg;
	
	msg = "";
	if (status == 0)
	{
		if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 0)
		{
			// ft_printf("LE FILS A QUITTE CORRECTEMENT\n");
			msg = "250 Requested file action completed..\x0a\x0d";
		}
		else if ((WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 0) || \
		WIFSIGNALED(wstatus))
		{
			// ft_printf("LE FILS A QUITTE sur erreur\n");
			msg = "451 Local error in processing...\x0a\x0d";
		}
		else if (WIFEXITED(wstatus) && WEXITSTATUS(wstatus) == 99)
		{
			// ft_printf("LE FILS A QUITTE Erreur le dossier n'existe pas\n");
			msg = "450 Requested Directory action not taken. \
			Directory unavailable...\x0a\x0d";
		}
	}
	else if (status == 1)
		msg = "125 Data connection already open; transfer starting.\x0a\x0d";
	else if (status == 2)
		msg = "250 Requested file action completed.\x0a\x0d";
	else if (status == 5)
		msg = "425 Error opening data connection.\x0a\x0d";
	sender_sock(vault, msg);
}

int		cmd_list(t_vault *vault)
{
	int		status;
	int		option;
	struct	rusage rusage;
	pid_t	cp_pid;
	
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