/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pasv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 15:59:16 by galy              #+#    #+#             */
/*   Updated: 2018/07/27 11:52:41 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

char	*pasv(t_vault *vault)
{
	char	*str;
	char	*tmp;

	// ft_printf("return %d\n", vault->csc);
	str = "PASV \r\n";
	send(vault->csc, str, ft_strlen(str), 0);

	if ((str = cmd_receiver(vault->csc)) == NULL)
		return (NULL);
	if ((tmp = ft_strchr(str, '\r')) != NULL || \
	(tmp = ft_strchr(str, '\n')) != NULL)
	{
		tmp[0] = '\0';
	}
	// ft_printf("from cmd pasv[%s]\n", str);
	return (str);
}
