/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_mkd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 15:02:06 by galy              #+#    #+#             */
/*   Updated: 2018/08/20 16:34:28 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

void	handle_mkd_rsp(char *rsp)
{
	int		code;

	code = ft_atoi(rsp);
	if (code == 257)
		ft_printf("[SUCCESS] %s\n", rsp);
	else if (code > 400)
		ft_printf("[ERROR] %s\n", rsp);
	else
		ft_printf("[ERROR] Unhandled response: [%s]\n", rsp);
}

int		check_folder_name(char *folder)
{
	int		i;

	i = 0;
	while (folder[i] != '\0')
	{
		if (ft_isprint(folder[i]) != 1)
			return (0);
		i++;
	}
	return (1);
}

int		cmd_mkd(t_vault *vault, char *str)
{
	char *rsp;

	str[ft_strlen(str) - 1] = '\0';
	if (check_folder_name(str + 4) != 1)
	{
		ft_printf("[ERROR] The folder name contain non printable char\n");
		free(str);
		return (0);
	}
	if (send(vault->csc, str, ft_strlen(str), 0) != (ssize_t)ft_strlen(str))
		ft_printf("[ERROR] Message not sent properly.\n");
	if ((rsp = cmd_receiver(vault->csc)) == NULL)
		ft_printf("[ERROR] Message not received properly.\n");
	else
	{
		handle_mkd_rsp(rsp);
		free(rsp);
	}
	free(str);
	return (1);
}
