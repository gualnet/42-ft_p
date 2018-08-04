/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data_conection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 20:53:39 by galy              #+#    #+#             */
/*   Updated: 2018/07/31 18:10:24 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

int		check_data_conection(t_vault *vault)
{
	char	*con_param;
	char	**split;

	if ((con_param = pasv(vault)) == NULL)
		return (-1);
	if ((split = ft_strsplit(con_param, ' ')) == NULL)
		return (-1);
	if (split[0] != NULL && ft_strncmp("227", split[0], 3) == 0)
	{
		if (create_dtp_sock(vault, con_param) < 0)
			return (-1);
	}
	else
	{
		ft_printf("Bad response from server, data "
		"connection failed.\n");
		return (-1);
	}
	return (1);
}
