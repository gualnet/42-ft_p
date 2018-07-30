/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_get_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/16 17:56:17 by galy              #+#    #+#             */
/*   Updated: 2018/07/27 15:07:35 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

int		rsp_handler(char *rsp)
{
	int		code;

	code = ft_atoi(rsp);
	free(rsp);
	if (100 < code && code < 300)
		return (1);
	if (code > 400)
		return (-1);
	
	return (-1);
}

char	*prep_cmd(char *str, char	**file)
{
	char	*tmp;
	char	*cmd;

	truncate_end_signs(str);
	if ((tmp = ft_strdup(str + 4)) == NULL)
		return (NULL);
	*file = ft_strtrim(tmp);
	if (*file != tmp)
		free(tmp);

	if ((cmd = ft_strjoin3("RETR ", *file, "\x0a\x0d")) == NULL)
		return (NULL);
	// free(file);

	return (cmd);
}

int		init_data_con(t_vault *vault)
{
	
	if (check_data_conection(vault) < 0)
	{
		ft_printf("Echec 001\n");
		return (-1);
	}
	return (1);
}

char	*srv_com_echange(t_vault *vault, ssize_t *size)
{
	char	*rsp;
	char	*data;

	if ((rsp = cmd_receiver(vault->csc) )== NULL)
		return (NULL);
	ft_printf("01 [%s]\n", rsp);
	if (rsp_handler(rsp) < 0)
		return (NULL);
	// if (init_data_con(vault) < 0)
	// 	return (NULL);
	data = dtp_receiver(vault->csd, size);
	if ((rsp = cmd_receiver(vault->csc)) == NULL)
		return (NULL);
	ft_printf("02 [%s]\n", rsp);
	return (data);
}


int		data_to_file(char *file_name, char *data, ssize_t size)
{
	int		fd;

	if ((fd = open(file_name, O_CREAT | O_RDWR, 0640)) < 0)
	{
		ft_printf("[ERROR] Unable to open \'%s\'\n", file_name);
		return (-1);
	}
	write(fd, data, (size_t)size);
	close(fd);
	free(data);
	ft_printf("[SUCCESS] \'%s\' created.\n", file_name);
	return (1);
}

int		cmd_get_file(t_vault *vault, char *str)
{
	char	*cmd;
	char	*file_name;
	ssize_t	size;

	file_name = NULL;
	if ((cmd = prep_cmd(str, &file_name)) == NULL)
		return (-1);
	free(str);

	if (init_data_con(vault) < 0)
		return (-1);
	if (send(vault->csc, cmd, ft_strlen(cmd), 0) < 0)
		ft_printf("[Error] Unexpected error "
		"while sending initial cmd to the server.\n");
	ft_printf("00 [%s]\n", cmd);
	if ((str = srv_com_echange(vault, &size)) == NULL)
		return (-1);
	if (str != NULL && size > 0)
		data_to_file(file_name, str, size);

	if (close(vault->csd) == -1)
		ft_printf("[!] Data socket not closed properly.\n");
	else
	{
		vault->csd = 0;
		// ft_printf("[*] Data conection closed\n");
	}
	return (1);
}
