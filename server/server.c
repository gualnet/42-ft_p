/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 14:44:23 by galy              #+#    #+#             */
/*   Updated: 2018/06/13 15:22:29 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

/*
**	Test serveur basique
**	
*/

int		main(int argc, char **argv)
{
	int					port;
	int					sock;
	struct sockaddr_in	csin;
	int					cs;
	unsigned int		cslen;
	
	if (argc != 2)
	{
		usage(argv[0]);
		return (-1);
	}

	ft_printf("MASTER PROCESS PID: [%d]\n", (int)getpid());
	port = ft_atoi(argv[1]);
	if ((sock = create_server(port)) < 0)
		return (-1);
	while (1)
	{
		if ((cs = accept(sock, (struct sockaddr*)&csin, &cslen)) < 0)
			ft_printf("Accept error\n");
		else
		{
			ft_printf("New connection accepted...\n");
			if (create_child_process(cs) > 0)
				printf("[%d] Continue on accept\n", (int)getpid());
			else
			{
				ft_printf("[%d] BREAKING LOOP\n", getpid());
				break;
			}
		}
	}
	// if (cs != -1)
	// 	close(cs);
	close(sock);
	return (1);
}