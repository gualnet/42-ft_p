/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dtp_receiver.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 17:25:41 by galy              #+#    #+#             */
/*   Updated: 2018/08/02 14:59:37 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

char	*dtp_receiver_2(char *buf, char *msg, ssize_t *size, ssize_t size_2)
{
	char	*tmp;

	if (msg != NULL)
	{
		tmp = msg;
		if ((msg = malloc(*size)) == NULL)
			return (NULL);
		ft_memcpy(msg, tmp, size_2);
		ft_memcpy(msg + size_2, buf, *size - size_2);
		free(tmp);
	}
	else
	{
		msg = malloc(*size);
		ft_memcpy(msg, buf, *size);
	}
	return (msg);
}

char	*dtp_receiver(int sock, ssize_t *size)
{
	char	buf[BUF_SIZE + 1];
	void	*msg;
	void	*tmp;
	ssize_t size_2;

	msg = NULL;
	tmp = NULL;
	*size = 0;
	while (1)
	{
		ft_bzero(buf, BUF_SIZE + 1);
		size_2 = *size;
		if ((*size += recv(sock, buf, BUF_SIZE, 0)) < 0)
			ft_printf("[*] Error receiving message from server !\n");
		if (*size == size_2)
			break ;
		msg = dtp_receiver_2(buf, msg, size, size_2);
	}
	return (msg);
}
