/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 15:50:35 by galy              #+#    #+#             */
/*   Updated: 2018/08/06 17:27:08 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

char	*insert_path(t_vault *vault, char *msg)
{
	char	**tab;
	char	*tmp;
	char	*newstr;

	tab = ft_strsplit(msg, ' ');
	tmp = ft_strjoin(tab[0], " ");
	free(tab[0]);
	tab[0] = ft_strjoin(tmp, vault->cwd);
	newstr = ft_strjoin(tab[0], tab[1]);
	free(tab[1]);
	free(tab);
	free(tmp);
	return (newstr);
}

void	pwd_response(t_vault *vault, int num)
{
	char	*msg;

	msg = "";
	if (num == -1)
	{
		msg = "500 Syntax error, command unrecognized.\x0a\x0d";
		sender_sock(vault, msg);
	}
	else if (num == 1)
	{
		msg = "257 \x0a\x0d";
		msg = insert_path(vault, msg);
		sender_sock(vault, msg);
		free(msg);
	}
}

char	*loop_getcwd(void)
{
	char	*buf;
	int		i;

	i = 1;
	while (i != 10)
	{
		buf = (char*)malloc(i * GETCWD_BUF_SIZE);
		if ((buf = getcwd(buf, i * GETCWD_BUF_SIZE)) == NULL)
			free(buf);
		else
			break ;
		i++;
	}
	return (buf);
}

int		cmd_pwd(t_vault *vault)
{
	if (vault->cwd == NULL)
	{
		if ((vault->cwd = loop_getcwd()) == NULL)
			pwd_response(vault, -1);
		else
			pwd_response(vault, 1);
	}
	else
		pwd_response(vault, 1);
	return (0);
}
