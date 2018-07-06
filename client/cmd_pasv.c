/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pasv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 15:59:16 by galy              #+#    #+#             */
/*   Updated: 2018/07/04 17:04:34 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

char	*pasv(t_vault *vault)
{
	char	*str;

	ft_printf("retirn %d\n", vault->csc);

	str = "PASV \r\n";
	send(vault->csc, str, ft_strlen(str), 0);

	str = cmd_receiver(vault->csc);
	ft_printf("from cmd pasv[%s]\n", str);
	
	return (str);
}
