/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtp_receiver.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 17:25:41 by galy              #+#    #+#             */
/*   Updated: 2018/07/23 10:59:52 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

char	*dtp_receiver(int sock, ssize_t	*size)
{
	char	buf[BUF_SIZE + 1];
	void	*msg;
	void	*tmp;
	ssize_t size_2;

	msg = NULL;
	tmp = NULL;
	*size = 0;
	ft_printf("00DTP RCV SIZE [%d]\n", *size);
	while (1)
	{
		ft_bzero(buf, BUF_SIZE + 1);
		size_2 = *size;
		if ((*size += recv(sock, buf, BUF_SIZE, 0)) < 0)
			ft_printf("[*] Error receiving message from server !\n");
		ft_printf("DTP RCV SIZE [%d]\n", *size);
		if (*size == size_2)
			break ;
		if (msg != NULL)
		{
			tmp = msg;
			msg = malloc(*size);
			ft_memcpy(msg, tmp, size_2);
			ft_memcpy(msg + size_2, buf, *size - size_2);
			free(tmp);
		}
		else
		{
			msg = malloc(*size);
			ft_memcpy(msg, buf, *size);
		}
	}
	ft_printf("11DTP RCV SIZE [%d]\n", *size);
	// for (int i = 0; i < *size; i++)
		// ft_printf("[\'%c\'][\'%d\']\n", msg[i], msg[i]);
	return (msg);
}

// char	*dtp_receiver(int sock, ssize_t	*size)
// {
// 	char	buf[BUF_SIZE + 1];
// 	char	*cmd;
// 	char	*tmp;
// 	ssize_t size_2;

// 	cmd = NULL;
// 	*size = 0;
// 	ft_printf("00DTP RCV SIZE [%d]\n", *size);
// 	while (1)
// 	{
// 		ft_bzero(buf, BUF_SIZE + 1);
// 		size_2 = *size;
// 		if ((*size += recv(sock, buf, BUF_SIZE, 0)) < 0)
// 			ft_printf("[*] Error receiving message from server !\n");
// 		ft_printf("DTP RCV SIZE [%d]\n", *size);
// 		if (size_2 == *size)
// 			break ;
// 		if (cmd != NULL)
// 			tmp = cmd;
// 		else
// 			tmp = ft_strdup("");
// 		if (*size == BUF_SIZE)
// 		{
// 			cmd = ft_strjoin(tmp, buf);
// 			free(tmp);
// 			// if ((tmp = ft_strchr(cmd, '\r')) != NULL)
// 			// {
// 			// 	tmp[0] = '\0';
// 			// 	break ;
// 			// }
// 		}
// 		else if (*size == 0)
// 			break ;
// 		else if (*size > 0 && *size < BUF_SIZE)
// 		{
// 			cmd = ft_strjoin(tmp, buf);
// 			free(tmp);
// 			// if ((tmp = ft_strchr(cmd, '\r')) != NULL)
// 			// 	tmp[0] = '\0';
// 			break ;
// 		}
// 	}
// 	ft_printf("11DTP RCV SIZE [%d]\n", *size);
// 	for (int i = 0; i < *size; i++)
// 		ft_printf("[\'%c\'][\'%d\']\n", cmd[i], cmd[i]);
// 	return (cmd);
// }
