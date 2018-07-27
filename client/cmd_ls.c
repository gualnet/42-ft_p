/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 12:43:41 by galy              #+#    #+#             */
/*   Updated: 2018/07/27 11:54:31 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

void	ls_cmd_response_handler(char *str)
{
	int		code;

	code = 0;
	code = ft_atoi(str);
	if (code == 250)
		ft_printf("[SUCCESS] Command ended without error.\n");
	else if (code > 400)
		ft_printf("[ERROR] An error has occured in the server process.\n");
	else if (code == 0)
		ft_printf("[!] Unhandled message [%s]\n", str);
	free(str);
}

void	print_dir_content(t_vault *vault)
{
	int		i;
	char	**line;
	int		cpt;

	i = 1;
	cpt = 0;
	ft_printf("\n\033[36;1;4mDir:\033[0m\n");
	while (vault->s_dir_content[i] != NULL)
	{
		line = ft_strsplit(vault->s_dir_content[i], ' ');
		if (line[0][0] == 'd' && line[8] != NULL)
		{
			ft_printf("\033[36m%s\t\033[0m", line[8]);
			cpt++;
		}
		ft_freestrsplited(line);
		if (cpt != 0 && ((cpt % 4) == 0))
		{
			ft_printf("\n", cpt);
			cpt = 0;
		}
		i++;
	}
	i = 1;
	cpt = 0;
	ft_printf("\n\n\033[36;1;4mFile:\033[0m\n");
	while (vault->s_dir_content[i] != NULL)
	{
		line = ft_strsplit(vault->s_dir_content[i], ' ');
		if (line[0][0] != 'd' && line[8] != NULL)
			ft_printf("%s\t", line[8]);
		ft_freestrsplited(line);
		if (cpt != 0 && ((cpt % 4) == 0))
		{
			ft_printf("\n", cpt);
			cpt = 0;
		}
		i++;
	}
	ft_printf("\n\n");
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
	// ft_printf("DATA [%s]\n", data);
	if ((data_lines = ft_strsplit(data, '\n')) == NULL)
	{
		ft_printf("NO DATA TO BE PRINTED");
		return (-1);
	}
	vault->s_dir_content = data_lines;
	return (1);
}

int		cmd_ls(t_vault *vault, char *str, int	print)
{
	char	*data;
	short	ret;

	ret = check_data_conection(vault);
	free(str);
	if (ret < 0)
		return (ret);

	str = "LIST \r\n";
	send(vault->csc, str, ft_strlen(str), 0);

	if ((str = cmd_receiver(vault->csc)) == NULL)
		return (-1);
	ls_cmd_response_handler(str);
	if ((data = cmd_receiver(vault->csd)) == NULL)
	{
		ft_printf("[Error] No data received from server\n)");
		return (-1);
	}
	if (vault->s_dir_content_name != NULL)
	{
		free(vault->s_dir_content_name);
		vault->s_dir_content_name = NULL;
	}
	data_process(vault, data);
	if (print != 0)
		print_dir_content(vault);
	if ((str = cmd_receiver(vault->csc)) == NULL)
		return (-1);
	ls_cmd_response_handler(str);
	if (close(vault->csd) == -1)
		ft_printf("vault->csd not closed properly\n");
	else
	{
		vault->csd = 0;
		// ft_printf("[*] Data conection closed\n");
	}
	// ft_printf("ICI la liste [%s]\n", data);
	return (1);
}
