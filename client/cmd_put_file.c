/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_put_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 17:35:36 by galy              #+#    #+#             */
/*   Updated: 2018/07/26 17:52:08 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

int		init_data_con_bis(t_vault *vault)
{
	// ft_printf("init data con START\n");
	if (check_data_conection(vault) < 0)
	{
		ft_printf("Echec 001\n");
		return (-1);
	}
	// else
	// 	ft_printf("Data con init OK\n");
	// ft_printf("init data con END\n");
	return (1);
}

int		rsp_handler_put(char *rsp)
{
	int		code;

	code = ft_atoi(rsp);
	if (100 < code && code < 300)
		return (1);
	free(rsp);
	return (-1);
}

char	*extract_filename(char *str)
{
	char	*filename;
	char	*tmp;

	truncate_end_signs(str);
	if ((tmp = ft_strdup(str + 4)) == NULL)
	{
		free(str);
		return (NULL);
	}
	filename = ft_strtrim(tmp);
	if (filename != tmp)
		free(tmp);
	return (filename);
}

int		prep_data(char *filename, t_file_info *file)
{
	if ((file->fd = open(filename, O_RDONLY | O_NONBLOCK)) < 0)
		return (-2);
	if (fstat(file->fd, &file->fstat) == -1)
		return (-3);
	
	if ((file->fdump = (void*)mmap(NULL, file->fstat.st_size, PROT_READ, \
	MAP_FILE | MAP_PRIVATE, file->fd, 0)) == MAP_FAILED)
		return (-4);
	ft_printf("[dev]PREP DATA OK size [%d]\n", file->fstat.st_size);
	return (1);
}

int		srv_com_exchange_put(t_vault *vault, char *cmd, t_file_info *file)
{
	char	*rsp;
	char	*rsp2;
	ssize_t	ret;

	if ((ret = send(vault->csc, cmd, ft_strlen(cmd), 0)) < 0)
	{
		ft_printf("[!] (1)Command not send or truncated. [%ld / %ld]\n", ret, file->fstat.st_size);
		return (-1);
	}
	rsp = cmd_receiver(vault->csc);
	if (rsp == NULL || rsp_handler_put(rsp) < 0)
	{
		ft_printf("[!] (1)Bad / Unhandled answer from server.\n");
		return (-1);
	}
	if ((ret = send(vault->csd, file->fdump, file->fstat.st_size, 0)) < 0)
	{
		ft_printf("[!] (2)Command not send or truncated. [%ld / %ld]\n", ret, file->fstat.st_size);
		return (-1);
	}
	send(vault->csd, "\x0a\x0d", 2, 0);
	rsp2 = cmd_receiver(vault->csc);
	if (rsp2 == NULL || rsp_handler_put(rsp2) < 0)
	{
		ft_printf("[!] (2)Bad / Unhandled answer from server.\n");
		return (-1);
	}
	return (1);
}

int		cmd_put_file(t_vault *vault, char *str)
{
	char		*cmd;
	char		*filename;
	t_file_info	file;

	if (init_data_con_bis(vault) < 0)
		return (-1);
	if ((filename = extract_filename(str)) == NULL)
		return (-1);
	free(str);
	int ret;
	if ((ret = prep_data(filename, &file)) < 0)
	{
		ft_printf("PB IN PREP DATA...[%d]\n", ret);
		return (-1);
	}
	if ((cmd = ft_strjoin3("STOR ", filename, "\x0a\x0d")) == NULL)
		return (-1);
	free(filename);
	srv_com_exchange_put(vault, cmd, &file);
	ft_printf("[SUCCESS] \'%s\' sent.\n", filename);
	if (close(vault->csd) == -1)
		ft_printf("[!] Data socket not closed properly.\n");
	else
	{
		vault->csd = 0;
		// ft_printf("[*] Data conection closed\n");
	}
	return (1);
}
