/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 18:31:27 by galy              #+#    #+#             */
/*   Updated: 2018/07/19 16:31:10 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

void	print_pwd(t_vault *vault)
{
	ft_printf("[SUCCESS] PWD [%s]\n", vault->s_cwd);
}

int		trait(t_vault *vault, char *cmd)
{
	// char	*tmp;
	if (ft_strncmp(cmd, "220", 3) == 0)
	{
		ft_printf("[*] Server processing..\n");
		return (2);
	}
	else if (ft_strncmp(cmd, "257", 3) == 0)
	{
		// if ((tmp = ft_strchr(cmd, '\r')) != NULL || \
		// (tmp = ft_strchr(cmd, '\n')) != NULL)
		// 	cmd[ft_strlen(cmd) - 1] = '\0';
		// ft_printf("[*] PWD \'%s\'", cmd + 4);
		if (vault->s_cwd != NULL)
			free(vault->s_cwd);
		vault->s_cwd = ft_strdup(cmd + 4);
		truncate_end_signs(vault->s_cwd);
		// ft_printf("[*] vault->s_cwd \'%s\'\n", vault->s_cwd);
	}
	else
		ft_printf("\nESLE [%s]??????\n", cmd); // test
	return (1);
}

int		cmd_pwd(t_vault *vault, char *str, int print)
{
	char	*cmd;
	short	ret;

	free(str); // str is useless in this case
	if ((cmd = ft_strdup("PWD\r\n")) == NULL)
		return (-1);
	ft_printf("CMD TO SENT [%s]\n", cmd);
	if (send(vault->csc, cmd, ft_strlen(cmd), 0) < 0)
		ft_printf("[*] Error sendind ls command \n");
	free(cmd); //free after sending cmd
	cmd = cmd_receiver(vault->csc);
	if ((ret = trait(vault, cmd)) < 0)
	{
		// retour d'un message d'erreur du serveur
		// ou erreur de traitement - voir code de retour de trait()
		return (-1);
	}
	free(cmd); // free after receiving cmd
	if (print != 0)
		print_pwd(vault);
	if (ret != 2)
		return (1);
	cmd = cmd_receiver(vault->csc);
	if (trait(vault, cmd) < 0)
	{
		// retour d'un message d'erreur du serveur
		// ou erreur de traitement - voir code de retour de trait()
		return (-1);
	}
	free(cmd); // free after receiving cmd
	return (1);
}
