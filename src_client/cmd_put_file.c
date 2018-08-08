/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_put_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/17 17:35:36 by galy              #+#    #+#             */
/*   Updated: 2018/08/08 15:27:53 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

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
	{
		ft_printf("[Error] Unable to open \'%s\'\n", filename);
		return (-2);
	}
	if (fstat(file->fd, &file->fstat) == -1)
		return (-3);
	if ((file->fdump = (void*)mmap(NULL, file->fstat.st_size, PROT_READ, \
	MAP_FILE | MAP_PRIVATE, file->fd, 0)) == MAP_FAILED)
		return (-4);
	ft_printf("PREP DATA OK\n");
	return (1);
}

int		cmd_put_file_2(t_vault *vault, char *filename)
{
	char		*cmd;
	int			ret;
	t_file_info	file;

	if ((ret = prep_data(filename, &file)) < 0)
	{
		ft_printf("00COUCOU\n");
		if (ret < -2)
			ft_printf("[Error] (%d) Abort file transfer.\n", ret);
		return (-1);
	}
	ft_printf("01COUCOU\n");
	if ((cmd = ft_strjoin3("STOR ", filename, "\x0a\x0d")) == NULL)
		return (-1);
	if (srv_com_exchange_put(vault, cmd, &file) < 0)
		return (-1);
	return (1);
}

int		cmd_put_file(t_vault *vault, char *str)
{
	char		*filename;

	if (check_data_conection(vault) < 0)
		return (-1);
	if ((filename = extract_filename(str)) == NULL)
		return (-1);
	free(str);
	if (cmd_put_file_2(vault, filename) < 0)
		return (-1);
	ft_printf("[SUCCESS] \'%s\' sent.\n", filename);
	free(filename);
	if (close(vault->csd) == -1)
		ft_printf("[!] Data socket not closed properly.\n");
	else
		vault->csd = 0;
	return (1);
}
