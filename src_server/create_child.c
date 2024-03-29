/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_child.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 14:27:34 by galy              #+#    #+#             */
/*   Updated: 2018/08/06 17:57:04 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

/*
**	cp : child process
*/

int		create_child_process(t_vault *vault)
{
	pid_t	cp_pid;

	if ((cp_pid = fork()) < 0)
	{
		ft_printf("fork failed..\n");
		return (-1);
	}
	else if (cp_pid > 0)
	{
		close(vault->csc);
		vault->csc = -1;
	}
	else
	{
		ft_printf("fork successed: PID[%d] from PPID[%d]\n", \
		(int)getpid(), (int)getppid());
		init_connexion(vault);
		return (state_machine(vault, 0));
	}
	return (1);
}
