/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pasv.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 18:34:21 by galy              #+#    #+#             */
/*   Updated: 2018/06/18 18:38:09 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

char	*build_pasive_addr(t_vault *vault)
{
	struct sockaddr_in	*sin;
	char				*msg;
	char				*tmp;
	char				*tmp2;
	int					port;
	
	

	sin = &vault->n_info.dtp_sin;

	printf("[%d]inet : [%x]:[%d] \n", getpid(), \
	ntohl(sin->sin_addr.s_addr), ntohs(sin->sin_port));
	ft_printf("sizeof(int): %d\n", sizeof(int));
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
	
	msg = build_pasive_addr(vault);
	tmp = ft_strjoin("227 ", msg);
	free(msg);
	msg =  ft_strjoin(tmp, "\x0a\x0d");
	sender_sock(vault, msg);
	free(tmp);
	free(msg);
}

int		cmd_pasv(t_vault *vault)
{

	vault->dtp_sock = create_dtp_socket(vault);
	//boucle d'attente de connexion dtp... ???
	
	pasv_response(vault);
	return (0);
}