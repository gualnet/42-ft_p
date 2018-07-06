/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 12:43:41 by galy              #+#    #+#             */
/*   Updated: 2018/07/04 19:19:57 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"


int		check_data_connection(t_vault *vault)
{
	char	*con_param;
	char	**split;
	con_param = pasv(vault);
	split = ft_strsplit(con_param, ' ');
	if (ft_strncmp("227", split[0], 3) == 0)
	{
		create_dtp_sock(vault, con_param);
	}
	else
		ft_printf("PAS BINGO - Bad response from server no data "
		"connection has been initiated\n");
	return (1);
}

int		data_process(char *data)
{
	char	**line;
	char	**split2;
	int		y;

	line = ft_strsplit(data, '\n');
	for (int i = 3; line[i] != NULL; i++)
	{
		// ft_printf("[%x]process [%s]\n", vault, line[i]);
		// for (int i = 0; split2[i] != NULL; i++)
		split2 = ft_strsplit(line[i], ' ');
		y = 0;
		while (split2[y] != NULL)
			y++;
		ft_printf("Splited line[%s]\n", split2[y - 1]);
	}

	

	return (1);
}

int		cmd_list(t_vault *vault, char *str)
{
	char	*data;

	ft_printf("retirn %d %s\n", vault->csc, str);
	check_data_connection(vault);

	free(str);
	str = "LIST \r\n";
	send(vault->csc, str, ft_strlen(str), 0);

	str = cmd_receiver(vault->csc);
	ft_printf("from cmd [%s]\n", str);
	free(str);

	data = cmd_receiver(vault->csd);
	data_process(data);
	return (1);
}
