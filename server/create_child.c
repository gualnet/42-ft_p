/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 14:27:34 by galy              #+#    #+#             */
/*   Updated: 2018/06/13 14:34:07 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		read_sock(int cs)
{
	char	buff[1024];
	int		rs;
	size_t	b_size;

	b_size = 1023;
	while ((rs = read(cs, buff, b_size)) > 0)
	{
		buff[rs - 1] = '\0';
		ft_printf("[%d]Receive: [%s]\n", getpid(), buff);
	}
	return (0);
}

/*
**	cp : child process
*/

int		create_child_process(int cs)
{
	pid_t	cp_pid;
	
	if ((cp_pid = fork()) < 0)
	{
		ft_printf("fork failed..\n");
		return (-1);
	}
	else if (cp_pid == 0)
	{
		ft_printf("[%d]Closing new connexion socket in parent process\n", (int)getpid());
		close(cs);
		cs = -1;
	}
	else
	{
		ft_printf("fork successed: PID[%d] - PPID[%d]\n", (int)getpid(), (int)getppid());
		printf("\n[%d]CS[%d]\n", getpid(), cs);
		read_sock(cs);
	}
	return (1);
}