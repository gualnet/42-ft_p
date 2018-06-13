/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/12 14:44:23 by galy              #+#    #+#             */
/*   Updated: 2018/06/13 12:36:05 by galy             ###   ########.fr       */
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

	if (bind(sock, (const struct sockaddr*)&sin, sizeof(sin)) < 0)
		ft_printf("Binding error\n");

	if (listen(sock, 10) == 0)
		ft_printf("Server is listening on %ld:%d\n", ntohl(sin.sin_addr.s_addr), ntohs(sin.sin_port) );
	else
		ft_printf("Listening error\n");


	return (sock);
}

int		test_read(int cs)
{
	char	buff[1024];
	int		rs;
	size_t	b_size;

	b_size = 1023;
	while ((rs = read(cs, buff, b_size)) > 0)
	{
		buff[rs - 1] = '\0';
		ft_printf("Receive: [%s]\n", buff);
	}
	return (0);
}

/*
**	cp for child process..
*/
int		create_child_process(int cs)
{
	pid_t	cp_pid; // cp for child process
	
	if ((cp_pid = fork()) < 0)
	{
		ft_printf("fork failed..\n");
		return (-1);
	}
	else if (cp_pid == 0)
	{
		ft_printf("[%d]Closing new connexion socket in parent process\n", (int)getpid());
		close(cs);
	}
	else
	{
		ft_printf("fork successed: PID[%d] - PPID[%d]\n", (int)getpid(), (int)getppid());
		test_read(cs);
	}

	
	return (1);
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

	ft_printf("MASTER PROCESS PID: [%d]\n", (int)getpid());
	port = ft_atoi(argv[1]);
	if ((sock = create_server(port)) < 0)
		return (-1);
	while (1)
	{
		if ((cs = accept(sock, (struct sockaddr*)&csin, &cslen)) < 0)
		{
			ft_printf("Accept error\n");
		}
		else
		{
			ft_printf("New connection accepted...\n");
			if (create_child_process(cs) > 0)
				printf("[%d] Continue on accept\n", (int)getpid());
			else
				break;
		}
	}
	// if (cs != -1)
	// 	close(cs);
	close(sock);
	return (1);
}