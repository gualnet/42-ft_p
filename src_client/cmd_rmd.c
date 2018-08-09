/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_rmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/09 15:34:12 by galy              #+#    #+#             */
/*   Updated: 2018/08/09 15:46:47 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

void	handle_rmd_rsp(char *rsp)
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

int		cmd_rmd(t_vault *vault, char *str)
{
	char *rsp;

	ft_printf("str [%s]\n", str);
	str[ft_strlen(str) - 1] = '\0';
	ft_printf("str [%s]\n", str);
	if (send(vault->csc, str, ft_strlen(str), 0) != (ssize_t)ft_strlen(str))
		ft_printf("[ERROR] Message not sent properly.\n");
	if ((rsp = cmd_receiver(vault->csc)) == NULL)
		ft_printf("[ERROR] Message not received properly.\n");
	else
	{
		handle_rmd_rsp(rsp);
		free(rsp);
	}
	return (1);
}
