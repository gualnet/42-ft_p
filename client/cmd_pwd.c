/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_ls.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 18:31:27 by galy              #+#    #+#             */
/*   Updated: 2018/06/29 20:00:24 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

char	*rcv_loop(int sock, char *buf)
{
	char	*cmd;
	char	*tmp;

	cmd = ft_strdup(buf);
	ssize_t size;
	while ((size = recv(sock, buf, BUF_SIZE, MSG_DONTWAIT)) > 0)
	{
		tmp = cmd;
		cmd = ft_strjoin(tmp, buf);
		free(tmp);
	}
	cmd[ft_strlen(cmd) - 2] = '\0';
	return (cmd);
}

int		trait(char *buf)
{
	if (ft_strncmp(buf, "220", 3) == 0)
		ft_printf("[*] Server processing..\n");
	else if (ft_strncmp(buf, "257", 3) == 0)
		ft_printf("[*] PWD \'%s\'", buf + 4);
	else
		ft_printf("\nESLE ??????\n"); // test
	return (1);
}

int		ls_receiver(int sock)
{
	char	buf[BUF_SIZE + 1];
	char	*cmd;
	ssize_t	size;

	while (1)
	{
		//step 1..
		if ((size = recv(sock, buf, BUF_SIZE, 0)) < 0)
			ft_printf("[*] Error receiving message from server !\n");
		if (size < BUF_SIZE )
			trait(buf);
		else
		{
			cmd = rcv_loop(sock, buf);
			trait(cmd);
			free(cmd);
		}
	}
	return (size);
}

int		cmd_pwd(int sock, char *str)
{
	char	*cmd;

	// ft_printf("entree[%s]\n", str);
	free(str);

	cmd = ft_strdup("PWD\r\n");
	send(sock, cmd, ft_strlen(cmd), 0);
	free(cmd);
	
	ls_receiver(sock);

	return (1);

}
