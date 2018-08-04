/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_dtp_socket.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/04 18:48:14 by galy              #+#    #+#             */
/*   Updated: 2018/08/02 14:57:01 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

char	*bit_play_2(int *port, char **split, char *tmp2, char *tmp3)
{
	int		i;

	if (split[3] != NULL)
		tmp2 = ft_strjoin(tmp3, split[3]);
	else
		return (NULL);
	free(tmp3);
	if ((tmp3 = ft_strtrim(tmp2)) != tmp2)
		free(tmp2);
	tmp2 = tmp3;
	*port = ft_atoi(split[4]);
	*port = *port << 8;
	*port += ft_atoi(split[5]);
	i = 0;
	while (split[i] != NULL)
	{
		free(split[i]);
		i++;
	}
	free(split);
	return (tmp2);
}

char	*bit_play(char *params, int *port)
{
	int		i;
	char	*tmp;
	char	*tmp2;
	char	*tmp3;
	char	**split;

	split = ft_strsplit(params + 3, ',');
	i = 0;
	tmp = NULL;
	tmp3 = ft_strdup("");
	while (split[i] && i < 3)
	{
		tmp = ft_strjoin(split[i], ".");
		tmp2 = ft_strjoin(tmp3, tmp);
		free(tmp);
		free(tmp3);
		tmp3 = tmp2;
		i++;
	}
	tmp2 = bit_play_2(port, split, tmp2, tmp3);
	ft_printf("RETURN BITPLAY [%s]\n", tmp2);
	return (tmp2);
}

int		dtp_connect(t_vault *vault, struct sockaddr_in	sin)
{
	if (connect(vault->csd, (struct sockaddr*)&sin, sizeof(sin)) < 0)
	{
		ft_printf("\n[*]Error code [%d]: Server unreachable or too busy\n" \
		, vault->csd);
		return (-4);
	}
	ft_printf("[*] Data conection established !\n");
	return (1);
}

int		create_dtp_sock(t_vault *vault, char *params)
{
	char				*addr;
	int					port;
	struct protoent		*proto;
	struct sockaddr_in	sin;

	if ((addr = bit_play(params, &port)) == NULL)
	{
		ft_printf("[*] Error determining addr and port for data connection\n");
		return (-1);
	}
	ft_printf("Addr [%s] Params [%s]\n", addr, params);
	free(params);
	if ((proto = getprotobyname("tcp")) == NULL)
		return (-1);
	ft_printf("vault->csd [%d]\n", vault->csd);
	if ((vault->csd = socket(PF_INET, SOCK_STREAM, proto->p_proto)) < 0)
		return (-2);
	ft_printf("vault->csd [%d]\n", vault->csd);
	sin.sin_family = AF_INET;
	sin.sin_port = htons(port);
	if ((sin.sin_addr.s_addr = inet_addr(addr)) == INADDR_NONE)
	{
		ft_printf("ECHEC dtp sock crea\n");
		return (-3);
	}
	if (dtp_connect(vault, sin) < 0)
		return (-4);
	return (1);
}
