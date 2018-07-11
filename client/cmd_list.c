/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 12:43:41 by galy              #+#    #+#             */
/*   Updated: 2018/07/11 12:33:39 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

void	print_dir_content(t_vault *vault)
{
	int		i;
	char	**line;

	i = 1;
	ft_printf("\n\033[36;1;4mDir:\033[0m\n");
	while (vault->dir_content[i] != NULL)
	{
		line = ft_strsplit(vault->dir_content[i], ' ');
		if (line[0][0] == 'd' && line[8] != NULL)
			ft_printf("\033[36m%s\t\033[0m", line[8]);
		ft_freestrsplited(line);
		i++;
	}
	i = 1;
	ft_printf("\n\n\033[36;1;4mFile:\033[0m\n");
	while (vault->dir_content[i] != NULL)
	{
		line = ft_strsplit(vault->dir_content[i], ' ');
		if (line[0][0] != 'd' && line[8] != NULL)
			ft_printf("%s\t", line[8]);
		ft_freestrsplited(line);
		i++;
	}
	ft_printf("\n");
}

int		check_data_connection(t_vault *vault)
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

char	*join_names(char *full_old, char *new_part)
{
	char	*full_new;

	full_new = ft_strjoin3(full_old, "\t\n", new_part);
	free(full_old);

	return (full_new);
}

int		data_process(t_vault *vault, char *data)
{
	char	**data_lines;

	if ((data_lines = ft_strsplit(data, '\n')) == NULL)
	{
		ft_printf("NO DATA TO BE PRINTED");
		return (-1);
	}
	vault->dir_content = data_lines;
	return (1);
}

int		cmd_list(t_vault *vault, char *str)
{
	char	*data;
	short	ret;

	ret = check_data_connection(vault);
	free(str);
	if (ret < 0)
		return (ret);

	str = "LIST \r\n";
	send(vault->csc, str, ft_strlen(str), 0);

	str = cmd_receiver(vault->csc);
	free(str);
	data = cmd_receiver(vault->csd);
	if (vault->dir_content_name != NULL)
	{
		free(vault->dir_content_name);
		vault->dir_content_name = NULL;
	}
	data_process(vault, data);
	print_dir_content(vault);
	str = cmd_receiver(vault->csc);
	// ft_printf("ICI la liste [%s]\n", data);
	return (1);
}
