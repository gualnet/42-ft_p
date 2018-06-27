/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 14:44:23 by galy              #+#    #+#             */
/*   Updated: 2018/06/18 18:28:30 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

void	free_vault(t_vault *vault)
{
	free(vault->name);
}

/*
**	Test serveur basique
**	
*/

int		main(int argc, char **argv)
{
	int					port;
	int					sock;
	struct sockaddr_in	csin;
	t_vault				vault;
	
	if (argc != 2)
	{
		usage(argv[0]);
		return (-1);
	}

	ft_printf("MASTER PROCESS PID: [%d]\n", (int)getpid());
	port = ft_atoi(argv[1]);
	if ((sock = create_server(&vault, port)) < 0)
		return (-1);
	while (1)
	{
		if ((vault.csc = accept(sock, (struct sockaddr*)&csin, &(vault.cslen))) < 0)
		{
			ft_printf("Accept error\n");
			return (-1);
		}
		else
		{
			ft_printf("New connection accepted...\n");
			if (create_child_process(&vault) > 0)
				printf("[%d] Continue master loop\n", (int)getpid());
			else
			{
				ft_printf("[%d] BREAKING LOOP\n", getpid());
				break;
			}
		}
	}
	ft_printf("\nOUT LOOP\n");
	// if (cs != -1)
	// 	close(cs);
	close(sock);
	free_vault(&vault);
	return (1);
}
