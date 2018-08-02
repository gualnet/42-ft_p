/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   running_loop.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/28 12:07:18 by galy              #+#    #+#             */
/*   Updated: 2018/08/02 15:17:29 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

char	*overflow_prot(int rs, char *buf)
{
	char	*tmp;
	char	*input;

	input = NULL;
	tmp = ft_strdup(buf);
	if (ft_strlen(tmp) >= BUF_SIZE)
		tmp[BUF_SIZE] = '\0';
	if (ft_strlen(tmp) == BUF_SIZE || ft_strlen(tmp) < BUF_SIZE)
		return (tmp);
	while (1)
	{
		ft_bzero(buf, BUF_SIZE);
		rs = read(1, buf, BUF_SIZE);
		if (rs < 1)
			break ;
		if (input != NULL)
			tmp = input;
		input = ft_strjoin(tmp, buf);
		if (rs != 0 && rs < BUF_SIZE)
			break ;
		input[ft_strlen(input) - 4] = '\0';
		free(tmp);
	}
	input[ft_strlen(input) - 1] = '\0';
	return (input);
}

char	*running_loop_2(int rs, char *buf)
{
	int		i;
	char	*tmp;
	char	*tmp2;

	i = 0;
	tmp = NULL;
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
	return (tmp);
}

void	running_loop(t_vault *vault, char *name)
{
	char	buf[BUF_SIZE + 1];
	int		rs;
	char	*tmp;

	ft_printf("*%s\n", name);
	ft_printf("[<] ");
	while (1)
	{
		tmp = NULL;
		ft_bzero(buf, BUF_SIZE);
		rs = read(1, buf, BUF_SIZE);
		tmp = running_loop_2(rs, buf);
		if (parsinterpreter(vault, tmp) == -999)
			break ;
		ft_printf("[<] ");
	}
}
