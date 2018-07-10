/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 12:43:41 by galy              #+#    #+#             */
/*   Updated: 2018/07/10 18:49:39 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"


int		check_data_connection(t_vault *vault)
{
	char	*con_param;
	char	**split;
	con_param = pasv(vault);
	ft_printf("CON PARAM [%s]\n", con_param);
	split = ft_strsplit(con_param, ' ');
	if (ft_strncmp("227", split[0], 3) == 0)
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
	char	**data_lines = NULL;
	
	data_lines = ft_strsplit(data, '\n');
	vault->dir_content = data_lines;
	return (1);
}
// int		data_process(t_vault *vault, char *data)
// {
// 	char	*names;
// 	char	**line;
// 	char	**split2;
// 	int		i;
// 	int		y;

// 	line = ft_strsplit(data, '\n');
// 	i = 1;
// 	names = NULL;
// 	while (line[i] != NULL)
// 	{
// 		split2 = ft_strsplit(line[i], ' ');
// 		y = 0;
// 		while (split2[y] != NULL)
// 		{
// 			if (split2[y + 1] == NULL)
// 			{
// 				if (names == NULL)
// 				{
// 					// ft_printf("This is usefull\n");
// 					free(names);
// 				}
// 				if ((names = join_names(names, split2[y])) == NULL)
// 					return (-1);
// 			}
// 			free(split2[y]);
// 			y++;
// 		}
// 		free(split2);
// 		i++;
// 	}

// 	vault->dir_content_name = names;
// 	return (1);
// }

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
	str = cmd_receiver(vault->csc);
	ft_printf("ICI la liste [%s]\n", data);
	return (1);
}
