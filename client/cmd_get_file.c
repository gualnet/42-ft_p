/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_get_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 17:56:17 by galy              #+#    #+#             */
/*   Updated: 2018/07/16 19:49:42 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

int		rsp_handler(char *rsp)
{
	int		code;

	code = ft_atoi(rsp);
	if (100 < code && code < 300)
		return (1);
	
	return (-1);
}

char	*prep_cmd(char *str)
{
	char	*file;
	char	*tmp;
	char	*cmd;

	truncate_end_signs(str);
	if ((tmp = ft_strdup(str + 4)) == NULL)
		return (NULL);
	file = ft_strtrim(tmp);
	if (file != tmp)
		free(tmp);

	if ((cmd = ft_strjoin3("RETR ", file, "\x0a\x0d")) == NULL)
		return (NULL);
	free(file);

	return (cmd);
}

int		init_data_con(t_vault *vault)
{
	
	if (check_data_conection(vault) < 0)
	{
		ft_printf("Echec 001\n");
		return (-1);
	}
	else
		ft_printf("Data con init OK\n");
	return (1);
}


int		srv_com_echange(t_vault *vault)
{
	char *rsp;
	char *data;

	rsp = cmd_receiver(vault->csc);
	ft_printf("\033[34m RSP{%s}\n\033[0m", rsp);
	
	if (rsp_handler(rsp) < 0)
		return (-1);
	free(rsp);
	data = cmd_receiver(vault->csd);
	ft_printf("\033[32m DATA{%s}\n\033[0m", data);
	
	rsp = cmd_receiver(vault->csc);
	ft_printf("\033[34m RSP{%s}\n\033[0m", rsp);
	free(rsp);


	return (1);
}

int		cmd_get_file(t_vault *vault, char *str)
{
	char	*cmd;

	ft_printf("CMD [%s]\n", str);
	if (init_data_con(vault) < 0)
		return (-1);


	if ((cmd = prep_cmd(str)) == NULL)
		return (-1);
	free(str);
	ft_printf("CMD2SEND [%s]\n", cmd);
	send(vault->csc, cmd, ft_strlen(cmd), 0);


	srv_com_echange(vault);


	if (close(vault->csd) == -1)
		ft_printf("vault->csd not closed properly\n");
	else
	{
		vault->csd = 0;
		ft_printf("[*] Data conection closed\n");
	}


	return (1);
}