/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 12:07:18 by galy              #+#    #+#             */
/*   Updated: 2018/07/27 12:46:51 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

char	*overflow_prot(int rs, char *buf)
{
	char	*tmp;
	char	*input;

	ft_printf("\t=====Overflow Prot=====\n");
	tmp = ft_strdup(buf);
	if (ft_strlen(tmp) >= BUF_SIZE)
		tmp[BUF_SIZE] = '\0';

	if (ft_strlen(tmp) == BUF_SIZE)
		return (tmp);

	input = NULL;

	if (ft_strlen(tmp) < BUF_SIZE)
		return (tmp);

	while (1)
	{
		ft_printf("000\n");
		ft_bzero(buf, BUF_SIZE);
		rs = read(1, buf, BUF_SIZE);
		if (rs < 1)
		{
			ft_printf("break1\n");
			break ;
		}
		ft_printf("001\n");
		if (input != NULL)
		{
			ft_printf("010\n");
			tmp = input;
		}
		ft_printf("002\n");
		input = ft_strjoin(tmp, buf);
		if (rs != 0 && rs < BUF_SIZE)
		{
			ft_printf("break2\n");
			break ;
		}
		ft_printf("003\n");
		input[ft_strlen(input) - 4] = '\0';
		free(tmp);
		ft_printf("004\n");
		
	}
	ft_printf("005\n");
	input[ft_strlen(input) - 1] = '\0';
	ft_printf("006\n");
	return (input);
}

void	running_loop(t_vault *vault, char *name)
{
	char	buf[BUF_SIZE + 1];
	int		rs;
	char	*tmp;
	char	*tmp2;
	int		i;

	ft_printf("*%s\n", name);
	ft_printf("[<] ");
	while (1)
	{
		tmp = NULL;
		ft_bzero(buf, BUF_SIZE);
		rs = read(1, buf, BUF_SIZE);
		i = 0;
		while (buf[i] != '\0' && i < BUF_SIZE)
			i++;
		if (rs > BUF_SIZE - 2)
		{
			tmp = overflow_prot(rs, buf);
			tmp2 = tmp;
			tmp = ft_strjoin(tmp, "\r\n");
			free(tmp2);
		}
		else
		{
			buf[i - 1] = '\r';
			buf[i] = '\n';
			tmp = ft_strdup(buf);
		}
		if (parsinterpreter(vault, tmp) == -999)
			break ;
		ft_printf("[<] ");
	}
}