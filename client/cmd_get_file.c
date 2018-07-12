/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_get_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 19:37:31 by galy              #+#    #+#             */
/*   Updated: 2018/07/12 20:57:10 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

/*
** Calling RETR (nom rfc)
*/



int		cmd_get_file(t_vault *vault, char *str)
{
	char	*file_name;
	char	*tmp;

	char	*data;


	ft_printf("=====GET_FILE=====\n", vault);
	truncate_end_signs(str);
	ft_printf("=====%s=====\n", str);

	tmp = ft_strdup(str + 4);
	free(str);
	file_name = ft_strtrim(tmp);
	if (file_name == tmp)
	{
		ft_printf("CASE1 AHAHAHAHAHAHA\n");
		exit(0);
	}
	else if (file_name != tmp)
		free(tmp);
	ft_printf("File name [%s]\n", file_name);

	//**************************************************

	if (check_data_conection(vault) < 0)
	{
		ft_printf("Echec 001\n");
		return (-1);
	}
	tmp = ft_strjoin3("RETR ", file_name, "\x0a\x0d");
	if (send(vault->csc, tmp, ft_strlen(tmp), 0) < 0)
	{
		ft_printf("[ERROR] command not sent or partialy\n");
		return (-1);
	}
	free(tmp);
	tmp = cmd_receiver(vault->csc);
	data = cmd_receiver(vault->csd);
	ft_printf("CMD RSP [%s]\n", tmp);
	ft_printf("==================\n");
	ft_printf("DTP RSP [%s]\n", data);

	free(tmp);









	free(file_name);
	// exit(0);
	return (1);
}