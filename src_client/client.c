/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/27 14:05:56 by galy              #+#    #+#             */
/*   Updated: 2018/08/20 15:21:09 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

int		welcome_msg(t_vault *vault)
{
	char *welcome;

	welcome = cmd_receiver(vault->csc);
	if (welcome != NULL && ft_strstr(welcome, "220 ") != NULL)
	{
		ft_printf("[*]Connection SUCCESS\n\n");
		free(welcome);
		return (1);
	}
	else
		return (-1);
}

char	*verified_addr(char **argv)
{
	char	*tmp1;
	char	*tmp2;
	int		i;

	if ((tmp1 = ft_strdup(argv[1])) == NULL)
		return (NULL);
	if ((tmp2 = ft_strtrim(tmp1)) == NULL)
		return (NULL);
	free(tmp1);
	i = 0;
	while (tmp2[i] != '\0')
	{
		tmp2[i] = ft_tolower(tmp2[i]);
		i++;
	}
	if (ft_strcmp("localhost", tmp2) == 0)
	{
		free(tmp2);
		return ("TRUE");
	}
	free(tmp2);
	return (NULL);
}

int		create_cmd_sock(t_vault *vault, char **argv)
{
	struct protoent		*proto;
	struct sockaddr_in	sin;
	char				*v_addr;

	ft_printf("[%d]Connecting to [%s : %s]...\n", getpid(), argv[1], argv[2]);
	v_addr = (verified_addr(argv) == NULL) ? argv[1] : "127.0.0.1";
	if ((proto = getprotobyname("tcp")) == NULL)
		return (-1);
	if ((vault->csc = socket(PF_INET, SOCK_STREAM, proto->p_proto)) < 0)
		return (-2);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(ft_atoi(argv[2]));
	if ((sin.sin_addr.s_addr = inet_addr(v_addr)) == INADDR_NONE)
	{
		ft_printf("\n[ERROR] Addres not well formated\n");
		return (-3);
	}
	if (connect(vault->csc, (struct sockaddr*)&sin, sizeof(sin)) < 0)
	{
		ft_printf("\n[ERROR] Server unreachable or too busy\n");
		return (-4);
	}
	if (welcome_msg(vault) != 1)
		return (-5);
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
	init_vault(&vault);
	if (create_cmd_sock(&vault, argv) < 0)
		return (-1);
	running_loop(&vault, argv[0]);
	return (1);
}
