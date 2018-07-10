/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 18:31:27 by galy              #+#    #+#             */
/*   Updated: 2018/07/10 13:34:45 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

int		trait(char *cmd)
{
	char	*tmp;
	if (ft_strncmp(cmd, "220", 3) == 0)
	{
		ft_printf("[*] Server processing..\n");
		return (2);
	}
	else if (ft_strncmp(cmd, "257", 3) == 0)
	{
		if ((tmp = ft_strchr(cmd, '\r')) != NULL || \
		(tmp = ft_strchr(cmd, '\n')) != NULL)
			cmd[ft_strlen(cmd) - 1] = '\0';
		ft_printf("[*] PWD \'%s\'", cmd + 4);
	}
	else
		ft_printf("\nESLE ??????\n"); // test
	return (1);
}

int		cmd_pwd(t_vault *vault, char *str)
{
	char	*cmd;
	short	ret;

	free(str); // str is useless in this case
	if ((cmd = ft_strdup("PWD\r\n")) == NULL)
		return (-1);
	if (send(vault->csc, cmd, ft_strlen(cmd), 0) < 0)
		ft_printf("[*] Error sendind ls command \n");
	free(cmd); //free after sending cmd
	cmd = cmd_receiver(vault->csc);
	if ((ret = trait(cmd)) < 0)
	{
		// retour d'un message d'erreur du serveur
		// ou erreur de traitement - voir code de retour de trait()
		return (-1);
	}
	free(cmd); // free after receiving cmd
	if (ret != 2)
		return (1);
	cmd = cmd_receiver(vault->csc);
	if (trait(cmd) < 0)
	{
		// retour d'un message d'erreur du serveur
		// ou erreur de traitement - voir code de retour de trait()
		return (-1);
	}
	free(cmd); // free after receiving cmd
	return (1);
}
