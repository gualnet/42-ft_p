/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   data_ex_ch.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/18 18:23:01 by galy              #+#    #+#             */
/*   Updated: 2018/08/08 18:34:03 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

pid_t	create_child_dtp_process(t_vault *vault)
{
	pid_t	cp_pid;

	if ((cp_pid = fork()) < 0)
	{
		ft_printf("[ERROR] Fork for data process failed.\n");
		return (-1);
	}
	else if (cp_pid > 0)
	{
		close(vault->csd);
		vault->csd = -1;
	}
	else
	{
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
		if ((vault->csd = accept(vault->dtp_sock, \
		(struct sockaddr*)&csin, &(vault->cslen))) < 0)
		{
			ft_printf("[ERROR] New connection not accepted.\n");
			return (-1);
		}
		else
		{
			cp_pid = create_child_dtp_process(vault);
			break ;
		}
	}
	return (cp_pid);
}

int		wait_for_cmd_conn(t_vault *vault, int cmd_sock)
{
	struct sockaddr_in	csin;

	while (1)
	{
		if ((vault->csc = accept(cmd_sock, \
		(struct sockaddr*)&csin, &(vault->cslen))) < 0)
		{
			ft_printf("[ERROR] New connection not accepted.\n");
			return (-1);
		}
		else
		{
			ft_printf("[INFO] New cmd connection from"
			" [%s]\n", inet_ntoa(csin.sin_addr));
			if (create_child_process(vault) < 0)
				break ;
		}
	}
	return (1);
}
