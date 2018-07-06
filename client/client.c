/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 14:05:56 by galy              #+#    #+#             */
/*   Updated: 2018/07/04 18:48:35 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"


int		create_cmd_sock(t_vault *vault, char **argv)
{
	// int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	ft_printf("[*]Connecting to [%s : %s] : ", argv[1], argv[2]);
	vault->csd = 0;
	if ((proto = getprotobyname("tcp")) == NULL)
		return (-1);
	if ((vault->csc = socket(PF_INET, SOCK_STREAM, proto->p_proto)) < 0)
		return (-2);

	sin.sin_family = AF_INET;
	sin.sin_port = htons(ft_atoi(argv[2]));
	if ((sin.sin_addr.s_addr = inet_addr(argv[1])) == INADDR_NONE)
	{
		ft_printf("\n[*]Error code [%d]: addres not well formated\n", vault->csc);
		return (-3);
	}
	if (connect(vault->csc, (struct sockaddr*)&sin, sizeof(sin)) < 0)
	{
		ft_printf("\n[*]Error code [%d]: Server unreachable or too busy\n", vault->csc);
		return (-4);
	}

	char *welcome;
	ft_printf("Waiting for server response\n");
	welcome = cmd_receiver(vault->csc);
	if (welcome != NULL && ft_strstr(welcome, "220 ") != NULL)
		ft_printf("[*]Connection SUCCESS\n\n");
	else
		return (-4);
	return (1);
}

int		main(int argc, char **argv)
{
	t_vault		vault;

	if (argc != 3)
	{
		usage(argv[0]);
		return (-1);
	}
	if (create_cmd_sock(&vault, argv) < 0)
		return (-1);

	read_send_loop(&vault, argv[0]);

	return (1);
}
