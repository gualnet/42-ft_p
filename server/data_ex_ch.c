/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_ex_ch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 18:23:01 by galy              #+#    #+#             */
/*   Updated: 2018/06/19 13:02:25 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

pid_t	create_child_dtp_process(t_vault *vault)
{
	pid_t	cp_pid;
	
	if ((cp_pid = fork()) < 0)
	{
		ft_printf("DATA fork failed..\n");
		return (-1);
	}
	else if (cp_pid > 0) // if parent
	{
		ft_printf("[%d][%d]father closing dtp\n", (int)getpid(), (int)getppid());
		close(vault->csd);
		vault->csd = -1;
	}
	else // sinon fils
	{
		ft_printf("DATA fork successed: PID[%d] - PPID[%d]\n", (int)getpid(), (int)getppid());
		ft_printf("[%d][%d]fork closing cmd\n", (int)getpid(), (int)getppid());
		close(vault->csc);
		vault->csc = -1;

	}
	return (cp_pid);
}

int		wait_for_conn(t_vault *vault)
{
	struct sockaddr_in	csin;
	pid_t				cp_pid;

	while (1)
	{
		if ((vault->csd = accept(vault->dtp_sock, (struct sockaddr*)&csin, &(vault->cslen))) < 0)
		{
			ft_printf("Accept error\n");
			return (-1);
		}
		else
		{
			ft_printf("New connection accepted...\n");
			if ((cp_pid = create_child_dtp_process(vault)) > 0)
			{
				ft_printf("[%d] Parent BREAKING LOOP\n", getpid());
				break ;
			}
			else
			{
				ft_printf("[%d] Child BREAKING LOOP\n", getpid());
				break ;
			}
		}
	}
	return (cp_pid);
}