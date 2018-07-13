/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_get_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 19:37:31 by galy              #+#    #+#             */
/*   Updated: 2018/07/13 18:02:52 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

/*
** Calling RETR (nom rfc)
*/

int		cmd_rsp_handler(char *rsp)
{
	int	code;

	code = ft_atoi(rsp);
	if (code > 99 && code < 300)
		ft_printf("[*] Data transfert in progress..\n");
	else if (code > 450 && code < 560)
	{
		ft_printf("[*] Data transfert aborted.\n");
		return (-1);
	}
	else
		ft_printf("[*] Response from server UNHANDLED \nMessage from server: [%s]\n", rsp);
	return (1);
}

int		data_rsp_handler(char *data, char *file_name)
{
	int		fd;
	// int		i;
	// char	*tmp;

	// i = 1;
	if ((fd = open(file_name, O_CREAT | O_WRONLY, 0644)) < 0)
	{
		// pour dl plusieurs fois le meme fichier
		// while (i < 25)
		// {
		// 	if ((tmp = ft_strchr(file_name, '_')) != NULL)
		// 		tmp[0] = '\0';
		// 	tmp = file_name;
		// 	file_name = ft_strjoin3(file_name, "_", ft_itoa(i));
		// 	free(tmp);
		// 	if ((fd = open(file_name, O_WRONLY)) > 0)
		// 		break ;
		// 	i++;
		// }
		if (fd < 0)
		{
			ft_printf("[ERROR] Unable to open \'%s\'\n", file_name);
			return (fd);
		}
	}
	ft_printf("write in fd[%d]\n", fd);
	if (write(fd, data, ft_strlen(data)) < 0)
	{
		ft_printf("[Error] An error has occured while writing the new file\n");
		return (-1);
	}
	close(fd);
	return (1);
}

int		cmd_get_file(t_vault *vault, char *str)
{
	char	*file_name;
	char	*tmp;

	char	*data;

	data = NULL;
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
	ft_printf("TMP01[%s]\n", tmp);
	if (cmd_rsp_handler(tmp) == 1)
	{
		data = cmd_receiver(vault->csd);
		if (data != NULL && data_rsp_handler(data, file_name) == 1)
		{
			ft_printf("[SUCCESS] File \'%s\' %d bytes transfered.\n", \
			file_name, ft_strlen(data));

		}
		else
			return (-1);
	}
	ft_printf("ici\n");
	free(tmp);
	tmp = cmd_receiver(vault->csc);
	ft_printf("TMP02[%s]\n", tmp);
	free(tmp);
	free(data);
	free(file_name);
	if (close(vault->csd) == -1)
		ft_printf("vault->csd not closed properly\n");
	else
	{
		vault->csd = 0;
		ft_printf("[*] Data conection closed\n");
	}
	return (1);
}