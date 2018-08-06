/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pasv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 18:34:21 by galy              #+#    #+#             */
/*   Updated: 2018/08/06 18:53:26 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

/*
**	struct hostent
**	{
**		char	*h_name;		Nom officiel de l'hôte.
**		char	**h_aliases;	Liste d'alias.
**		int		h_addrtype;		Type d'adresse de l'hôte.
**		int		h_length;		Longueur de l'adresse.
**		char	**h_addr_list;	Liste d'adresses.
**	}
*/
int		test_gethostbyname(void)
{
	ft_printf("\nCALL TEST...\n");

	struct hostent	*hostent;

	if ((hostent = gethostbyname("localhost")) == NULL)
	{
		ft_printf("ERREUR sur l'appel de gethostbyname !\n");
		return (-1);
	}
	ft_printf("\n----START-----\n");
	ft_printf("h_name [%s]\n", hostent->h_name);
	ft_printf("\n----------------\n");
	for (int i = 0; hostent->h_aliases[i] != NULL; i++)
		ft_printf("h_aliases[%d] [%s]", i, hostent->h_aliases[i][0]);
	ft_printf("\n----------------\n");
	ft_printf("h_addrtype [%d]\n", hostent->h_addrtype);
	ft_printf("\n----------------\n");
	ft_printf("h_length [%d]\n", hostent->h_length);
	ft_printf("\n----------------\n");
	ft_printf("h_addr [%d][%s]\n", hostent->h_addr, hostent->h_addr);
	ft_printf("\n---------\n");
	for (int i = 0; hostent->h_addr_list[i] != NULL; i++)
	{
		ft_printf("h_addr_list[%d] [%d][%s]\n", i, hostent->h_addr_list[i], hostent->h_addr_list[i]);
	}
	ft_printf("\n----END------\n");
	return (0);
}

char	*build_pasive_addr(t_vault *vault)
{
	struct sockaddr_in	*sin;
	char				*msg;
	char				*tmp;
	char				*tmp2;
	int					port;

	sin = &vault->n_info.dtp_sin;
	/*
	** BESOIN D'UN PLAN POUR RECUP L'IP
	*/
	if (ntohs(sin->sin_port) != 0)
		msg = "127,0,0,1,";
	else
		msg = "123,123,123,123,";
	port = ntohs(sin->sin_port);
	tmp = ft_strjoin(ft_itoa(port >> 8), ",");
	tmp2 = ft_strjoin(msg, tmp);
	free(tmp);
	tmp = ft_strjoin(tmp2, ft_itoa(port & 255));
	free(tmp2);
	return (tmp);
}

void	pasv_response(t_vault *vault)
{
	char *msg;
	char *tmp;

	test_gethostbyname(); // test
	msg = build_pasive_addr(vault);
	tmp = ft_strjoin("227 ", msg);
	free(msg);
	msg = ft_strjoin(tmp, "\x0a\x0d");
	sender_sock(vault, msg);
	free(tmp);
	free(msg);
}

int		cmd_pasv(t_vault *vault)
{
	if (vault->dtp_sock == 0)
		vault->dtp_sock = create_dtp_socket(vault);
	pasv_response(vault);
	return (0);
}
