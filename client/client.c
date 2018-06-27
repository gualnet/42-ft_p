/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 14:05:56 by galy              #+#    #+#             */
/*   Updated: 2018/06/27 17:11:29 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"


int		create_cmd_sock(t_vault *vault, char **argv)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	ft_printf("vault[%p]\n", vault);
	if ((proto = getprotobyname("tcp")) == NULL)
		return (-1);
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) < 0)
		return (-2);
	
	sin.sin_family = AF_INET;
	sin.sin_port = htons(ft_atoi(argv[2]));
	if ((sin.sin_addr.s_addr = inet_addr(argv[1])) == INADDR_NONE)
		return (-3);
	
	if (connect(sock, (struct sockaddr*)&sin, sizeof(sin)) < 0)
		return (-4);
	ft_printf("Connected ?\n");
	return (sock);
}


int		main(int argc, char **argv)
{
	t_vault		vault;
	int			sock;

	if (argc != 3)
	{
		usage(argv[0]);
		return (-1);
	}
	printf("argc[%d] addr[%s] port[%s]\n", argc, argv[1], argv[2]);

	if ((sock = create_cmd_sock(&vault, argv)) < 0)
	{
		ft_printf("sock creation NOK error code [%d]\n", sock);
		return (-1);
	}
	write(sock, "salut", 6);
	ft_printf("LAAA\n");
	// init_cmd_connect(&vault, argv);



	return (1);
}
