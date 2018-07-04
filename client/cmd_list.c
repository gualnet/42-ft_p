/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 12:43:41 by galy              #+#    #+#             */
/*   Updated: 2018/07/04 12:52:11 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

int		cmd_list(int sock, char *str)
{
	ft_printf("retirn %d %s\n", sock, str);

	free(str);
	str = "LIST \r\n";
	send(sock, str, ft_strlen(str), 0);

	str = cmd_receiver(sock);
	ft_printf("from cmd [%s]\n", str);
	free(str);

	return (1);
}