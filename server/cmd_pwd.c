/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_pwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/14 15:50:35 by galy              #+#    #+#             */
/*   Updated: 2018/06/22 18:53:16 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

char	*insert_path(t_vault *vault, char *msg)
{
	char **tab;
	char *tmp;
	char *newstr;

	tab = ft_strsplit(msg, ' ');
	// ft_printf("[%s]\n", vault->cwd);
	int i = ft_strlen(vault->cwd);
	while (vault->cwd[i] != '/' && (&vault->cwd[i] != vault->cwd))
		i--;
	
	tmp = ft_strjoin(tab[0], " ");
	free(tab[0]);
	// tab[0] = ft_strjoin(tmp, vault->cwd + i);
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
		msg = "500 \x0a\x0d";
		sender_sock(vault, msg);
	}
	else if (num == 1)
	{
		msg = "257 \x0a\x0d";
		msg = insert_path(vault, msg);
		sender_sock(vault, msg);
		ft_printf("\n\nCHEMIN RETOURNE ICI [%s]\n\n", msg);
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
		// ft_printf("[%p]size[%d]",buf, i * GETCWD_BUF_SIZE);
		if ((buf = getcwd(buf, i * GETCWD_BUF_SIZE)) == NULL)
		{
			free(buf);
			ft_printf("[%d] [%s]\n", i, buf);
		}
		else
			break ;
		i++;
	}
	ft_printf("[%d] [%s]\n", i, buf);
	return (buf);
}

int		cmd_pwd(t_vault *vault)
{
	if (vault->cwd == NULL)
	{
		ft_printf("COUCOU00[%s]\n", vault->cwd);
		if ((vault->cwd = loop_getcwd()) == NULL)
			pwd_response(vault, -1);
		else
			pwd_response(vault, 1);
	}
	else
	{
		ft_printf("COUCOU01 [%s]\n", vault->cwd);
		pwd_response(vault, 1);
	}
	

	return (0);
}