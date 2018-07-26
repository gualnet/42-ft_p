/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data_conection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 20:53:39 by galy              #+#    #+#             */
/*   Updated: 2018/07/26 12:09:30 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

int		check_data_conection(t_vault *vault)
{
	char	*con_param;
	char	**split;

	con_param = pasv(vault);
	split = ft_strsplit(con_param, ' ');
	if (split[0] != NULL && ft_strncmp("227", split[0], 3) == 0)
	{
		create_dtp_sock(vault, con_param);
	}
	else
	{
		ft_printf("Bad response from server, data "
		"connection failed.\n");
		return (-1);
	}
	return (1);
}