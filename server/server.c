/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 14:44:23 by galy              #+#    #+#             */
/*   Updated: 2018/06/12 16:37:57 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

/*
**	Test d'un serveur basique
**	
*/

int		create_server(int port)
{
	int					sock;
	struct protoent		*proto;
	struct sockaddr_in	sin;


	if ((proto = getprotobyname("tcp")) == NULL)
		return (-1);
	if ((sock = socket(PF_INET, SOCK_STREAM, proto->p_proto)) < 0)
		return (-2);

	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	sin.sin_addr.s_addr = htonl(INADDR_ANY);

	bind(sock, (const struct sockaddr*)&sin, sizeof(sin));

	listen(sock, 10);

	return (sock);
}

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

	port = ft_atoi(argv[1]);
	if ((sock = create_server(port)) < 0)
		return (-1);
	cs = accept(sock, (struct sockaddr*)&csin, &cslen);

	close(sock);
	close(cs);
}