/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sender_receiver.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 14:10:48 by galy              #+#    #+#             */
/*   Updated: 2018/07/10 22:53:04 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"



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

		if (cmd != NULL)
			tmp = cmd;
		else
			tmp = ft_strdup("");
		// ft_printf("SSIZE[%d]\n", size);
		if (size == BUF_SIZE)
		{
			// ft_printf("\033[33m[INFO] size == BUF_SIZE\n\033[0m");
			// ft_printf("CONTENT BUF[%s]\n", buf);

			cmd = ft_strjoin(tmp, buf);
			free(tmp);

			// ft_printf("CONTENT CMD[%s]\n", cmd);
			if ((tmp = ft_strchr(cmd, '\r')) != NULL)
			{
				tmp[0] = '\0';
				break ;
			}
		}
		else if (size == 0)
		{
			ft_printf("\033[33m[INFO] size == 0\n\033[0m");
			ft_printf("\033[35m NOT HANDLED\n\033[0m");
			ft_printf("CONTENT BUF[%s]\n", buf);
			ft_printf("CONTENT CMD[%s]\n", cmd);
			break ;
		}
		else if (size > 0 && size < BUF_SIZE)
		{
			// ft_printf("\033[33m[INFO] size > 0 && size < BUF_SIZE\n\033[0m");
			// ft_printf("CONTENT BUF[%s]\n", buf);

			cmd = ft_strjoin(tmp, buf);
			free(tmp);
			if ((tmp = ft_strchr(cmd, '\r')) != NULL)
				tmp[0] = '\0';
			// ft_printf("CONTENT CMD[%s]\n", cmd);

			break ;
		}
		else
		{
			ft_printf("\033[33m[INFO] ELSE...\n\033[0m");
			ft_printf("\033[35m NOT HANDLED\n\033[0m");
			ft_printf("CONTENT BUF[%s]\n", buf);
			ft_printf("CONTENT CMD[%s]\n", cmd);
		}
	}
	// ft_printf("CMD RECEIVER END[%s]\n", cmd);
	return (cmd);
}
