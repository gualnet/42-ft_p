/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 18:31:27 by galy              #+#    #+#             */
/*   Updated: 2018/08/20 16:08:51 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

int		trait(t_vault *vault, char *cmd)
{
	if (ft_strncmp(cmd, "220", 3) == 0)
	{
		ft_printf("[*] Server processing..\n");
		return (2);
	}
	else if (ft_strncmp(cmd, "257", 3) == 0)
	{
		if (vault->s_cwd != NULL)
			free(vault->s_cwd);
		vault->s_cwd = ft_strdup(cmd + 4);
		truncate_end_signs(vault->s_cwd);
	}
	return (1);
}

int		cmd_pwd_2(t_vault *vault, int ret)
{
	char	*cmd;

	if (ret != 2)
		return (1);
	if ((cmd = cmd_receiver(vault->csc)) == NULL)
		return (-1);
	if (trait(vault, cmd) < 0)
	{
		ft_printf("[ERROR] %s\n", cmd);
		return (-1);
	}
	free(cmd);
	return (1);
}

int		cmd_pwd(t_vault *vault, char *str, int print)
{
	char	*cmd;
	short	ret;

	free(str);
	if ((cmd = ft_strdup("PWD\r\n")) == NULL)
		return (-1);
	if (send(vault->csc, cmd, ft_strlen(cmd), 0) < 0)
		ft_printf("[*] Error sendind ls command \n");
	free(cmd);
	if ((cmd = cmd_receiver(vault->csc)) == NULL)
		return (-1);
	if ((ret = trait(vault, cmd)) < 0)
	{
		ft_printf("[ERROR] %s\n", cmd);
		return (-1);
	}
	free(cmd);
	if (print != 0)
		ft_printf("[SUCCESS] PWD \'%s\'\n", vault->s_cwd);
	return (cmd_pwd_2(vault, ret));
}
