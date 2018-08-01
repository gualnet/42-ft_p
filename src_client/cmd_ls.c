/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 12:43:41 by galy              #+#    #+#             */
/*   Updated: 2018/08/01 15:02:50 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

void	ls_cmd_response_handler(char *str, int print)
{
	int		code;

	code = 0;
	code = ft_atoi(str);
	if (code == 250 && print != CMD_NOPRINT)
		ft_printf("[SUCCESS] Command ended without error.\n");
	else if (code > 400)
		ft_printf("[ERROR] An error has occured in the server process.\n");
	else if (code == 0)
		ft_printf("[!] Unhandled message [%s]\n", str);
	free(str);
}

int		data_process(t_vault *vault, char *data)
{
	char	**data_lines;

	if ((data_lines = ft_strsplit(data, '\n')) == NULL)
	{
		ft_printf("NO DATA TO BE PRINTED");
		return (-1);
	}
	vault->s_dir_content = data_lines;
	return (1);
}

int		cmd_ls_2(t_vault *vault, char *str, int print)
{
	char	*data;

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
	ls_cmd_response_handler(str, print);
	return (1);
}

int		cmd_ls(t_vault *vault, char *str, int print)
{
	short	ret;

	ret = check_data_conection(vault);
	free(str);
	if (ret < 0)
		return (ret);
	str = "LIST \r\n";
	send(vault->csc, str, ft_strlen(str), 0);
	if ((str = cmd_receiver(vault->csc)) == NULL)
		return (-1);
	ls_cmd_response_handler(str, print);
	cmd_ls_2(vault, str, print);
	if (close(vault->csd) == -1)
		ft_printf("vault->csd not closed properly\n");
	else
		vault->csd = 0;
	return (1);
}
