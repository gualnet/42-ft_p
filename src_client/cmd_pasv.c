/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pasv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 15:59:16 by galy              #+#    #+#             */
/*   Updated: 2018/08/01 17:34:44 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

char	*pasv(t_vault *vault)
{
	char	*str;
	char	*tmp;

	str = "PASV \r\n";
	if (send(vault->csc, str, ft_strlen(str), 0) < 0)
	{
		ft_printf("[ERROR] Unable to send the command.\n");
		return (NULL);
	}
	if ((str = cmd_receiver(vault->csc)) == NULL)
		return (NULL);
	if ((tmp = ft_strchr(str, '\r')) != NULL || \
	(tmp = ft_strchr(str, '\n')) != NULL)
		tmp[0] = '\0';
	return (str);
}
