/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_receiver.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 14:10:48 by galy              #+#    #+#             */
/*   Updated: 2018/08/02 18:35:21 by galy             ###   ########.fr       */
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

int		rcv_inner_loop(t_strings *bucstr)
{
	if (bucstr->size == 0)
	{
		if (bucstr->cmd == NULL)
			ft_printf("[ERROR] No response from server !\n");
		return (1);
	}
	else
	{
		bucstr->cmd = ft_strjoin(bucstr->tmp, bucstr->buf);
		free(bucstr->tmp);
		if ((bucstr->tmp = ft_strchr(bucstr->cmd, '\r')) != NULL)
		{
			bucstr->tmp[0] = '\0';
			return (1);
		}
	}
	return (0);
}

char	*cmd_receiver(int sock)
{
	t_strings	bucstr;

	bucstr.cmd = NULL;
	while (1)
	{
		ft_bzero(bucstr.buf, BUF_SIZE + 1);
		if ((bucstr.size = recv(sock, bucstr.buf, BUF_SIZE, 0)) < 0)
			ft_printf("[*] Error receiving message from server !\n");
		if ((bucstr.tmp = rcv_step_1(bucstr.cmd)) == NULL)
			return (NULL);
		if (rcv_inner_loop(&bucstr) == 1)
			break ;
	}
	return (bucstr.cmd);
}
