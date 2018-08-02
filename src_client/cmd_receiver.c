/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_receiver.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 14:10:48 by galy              #+#    #+#             */
/*   Updated: 2018/08/02 17:05:51 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

char	*rcv_step_1(char *cmd)
{
	char	*tmp;

	if (cmd != NULL)
		tmp = cmd;
	else
		tmp = ft_strdup("");
	return (tmp);
}

char	*cmd_receiver(int sock)
{
	char	buf[BUF_SIZE + 1];
	char	*cmd;
	char	*tmp;
	ssize_t	size;

	cmd = NULL;
	while (1)
	{
		ft_bzero(buf, BUF_SIZE + 1);
		if ((size = recv(sock, buf, BUF_SIZE, 0)) < 0)
			ft_printf("[*] Error receiving message from server !\n");
		if ((tmp = rcv_step_1(cmd)) == NULL)
			return (NULL);
		if (size == BUF_SIZE)
		{
			cmd = ft_strjoin(tmp, buf);
			free(tmp);
			if ((tmp = ft_strchr(cmd, '\r')) != NULL)
			{
				tmp[0] = '\0';
				break ;
			}
		}
		else if (size == 0)
		{
			if (cmd == NULL)
				ft_printf("[ERROR] No response from server !\n");
			break ;
		}
		else if (size > 0 && size < BUF_SIZE)
		{
			cmd = ft_strjoin(tmp, buf);
			free(tmp);
			if ((tmp = ft_strchr(cmd, '\r')) != NULL)
				tmp[0] = '\0';
			break ;
		}
	}
	return (cmd);
}
