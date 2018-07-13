/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_data_conection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 20:53:39 by galy              #+#    #+#             */
/*   Updated: 2018/07/13 17:50:29 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

int		check_data_conection(t_vault *vault)
{
	char	*con_param;
	char	**split;

	con_param = pasv(vault);
	// ft_printf("CON PARAM [%p][%s]\n", con_param, con_param);
	split = ft_strsplit(con_param, ' ');
	// ft_printf("SPLIT [%p][%s]\n", split, split[0]);
	if (split[0] != NULL && ft_strncmp("227", split[0], 3) == 0)
	{
		create_dtp_sock(vault, con_param);
	}
	else
	{
		ft_printf("PAS BINGO - Bad response from server no data "
		"connection has been initiated\n");
		return (-1);
	}
	return (1);
}