/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 18:31:27 by galy              #+#    #+#             */
/*   Updated: 2018/07/03 19:12:24 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

int		trait(char *cmd)
{
	if (ft_strncmp(cmd, "220", 3) == 0)
		ft_printf("[*] Server processing..\n");
	else if (ft_strncmp(cmd, "257", 3) == 0)
		ft_printf("[*] PWD \'%s\'", cmd + 4);
	else
		ft_printf("\nESLE ??????\n"); // test
	return (1);
}

int		cmd_pwd(int sock, char *str)
{
	char	*cmd;

	free(str); // str is useless in this case
	if ((cmd = ft_strdup("PWD\r\n")) == NULL)
		return (-1);
	if (send(sock, cmd, ft_strlen(cmd), 0) < 0)
		ft_printf("[*] Error sendind ls command \n");
	free(cmd); //free after sending cmd
	cmd = cmd_receiver(sock);
	if (trait(cmd) < 0)
	{
		// retour d'un message d'erreur du serveur
		// ou erreur de traitement - voir code de retour de trait()
		return (-1);
	}
	free(cmd); // free after receiving cmd
	cmd = cmd_receiver(sock);
	if (trait(cmd) < 0)
	{
		// retour d'un message d'erreur du serveur
		// ou erreur de traitement - voir code de retour de trait()
		return (-1);
	}
	free(cmd); // free after receiving cmd
	return (1);
}

