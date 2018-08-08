/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_put_file_2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/01 17:58:50 by galy              #+#    #+#             */
/*   Updated: 2018/08/08 15:57:05 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

int		rsp_handler_put(char *rsp)
{
	int		code;

	code = ft_atoi(rsp);
	if (100 < code && code < 300)
		return (1);
	free(rsp);
	return (-1);
}

int		srv_com_exchange_put_2(t_vault *vault, t_file_info *file)
{
	int		ret;
	// char	*rsp;

	if ((ret = send(vault->csd, file->fdump, \
	(size_t)file->fstat.st_size, 0)) < 0)
	{
		ft_printf("[!] (2)Command not sent or truncated. [%ld / %ld]\n", \
		ret, file->fstat.st_size);
	}
	ft_printf("RET [%d]\n", ret);
	if (send(vault->csd, "\x0a\x0d", 2, 0) < 2)
	{
		ft_printf("[ERROR] Unable to send the command.\n");
		return (-1);
	}
	ft_printf("02COUCOU\n");
	// rsp = cmd_receiver(vault->csc);
	ft_printf("03COUCOU\n");
	// if (rsp == NULL || rsp_handler_put(rsp) < 0)
	// {
	// 	ft_printf("[!] (2)Bad / Unhandled answer from server.\n");
	// 	return (-1);
	// }
	ft_printf("04COUCOU\n");
	return (1);
}

int		srv_com_exchange_put(t_vault *vault, char *cmd, t_file_info *file)
{
	char	*rsp;
	ssize_t	ret;

	if ((ret = send(vault->csc, cmd, ft_strlen(cmd), 0)) < 0)
	{
		ft_printf("[!] (1)Command not sent or truncated. [%ld / %ld]\n", \
		ret, file->fstat.st_size);
		return (-1);
	}
	rsp = cmd_receiver(vault->csc);
	if (rsp == NULL || rsp_handler_put(rsp) < 0)
	{
		ft_printf("[!] (1)Bad / Unhandled answer from server.\n");
		return (-1);
	}
	free(rsp);
	if (srv_com_exchange_put_2(vault, file) < 0)
		return (-1);
	return (1);
}
