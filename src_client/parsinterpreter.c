/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsinterpreter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 12:39:59 by galy              #+#    #+#             */
/*   Updated: 2018/07/27 16:04:44 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

char	*force_cmd_toupper(char *str)
{
	int		i;
	char	*tmp;

	tmp = NULL;
	if ((tmp = ft_strchr(str, ' ')) == NULL)
		tmp = ft_strchr(str, '\t');
	// ft_printf("TMP+[%s]\n", tmp);
	if (tmp == NULL)
	{
		tmp = str + ft_strlen(str);
	}
	// ft_printf("TMP++[%c][%d]\n", tmp);
	i = 0;
	// ft_printf("str[%s]\n", str);
	while ((str + i) < tmp)
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	return (str);
}

int		cmd_box(t_vault *vault, char *str)
{
	// ft_printf("\n=====CMD_BOX=====\n");
	// ft_printf("\n=====[%s]=====\n", str);
	// ft_printf("len(%d)\n", ft_strlen(str));
	if (ft_strncmp(str, "PWD", 3) == 0)
		return (cmd_pwd(vault, str, CMD_PRINT));
	if (ft_strncmp(str, "LS", 2) == 0)
		return (cmd_ls(vault, str, CMD_PRINT));
	if (ft_strncmp(str, "QUIT", 4) == 0)
		return (cmd_quit(vault, str));
	if (ft_strncmp(str, "CD ", 3) == 0 || ft_strncmp(str, "CD\t", 3) == 0)
		return (cmd_cd(vault, str), CMD_PRINT);
	if (ft_strncmp(str, "GET ", 4) == 0 || ft_strncmp(str, "GET\t", 4) == 0)
		return (cmd_get_file(vault, str));
	if (ft_strncmp(str, "PUT ", 4) == 0 || ft_strncmp(str, "PUT\t", 4) == 0)
		return (cmd_put_file(vault, str));

	if (ft_strncmp(str, "HELP", 4) == 0)
	{
		int i = 0;
		while (i < 4)
		{
			sleep(1);
			ft_putchar('.');
			i++;
		}
		ft_printf(" SOS ;)\n");
		return (1);
	}
	return (-888);
}

int		parsinterpreter(t_vault *vault, char *str)
{
	// ft_printf("\n=====PARSINTERPRETER=====\n");
	char	*tmp;
	int		ret;

	ret = 0;
	tmp = force_cmd_toupper(str);

	str = ft_strtrim(tmp);
	if (str != tmp)
		free(tmp);

	ret = cmd_box(vault, str);
	if (ret < 0 && vault->csd > 2)
	{
		ft_printf("bingo close\n");
		close(vault->csd);
		vault->csd = 0;
	}
	if (ret == -888)
		ft_printf("\n[*] Unvalid commande see \"help\"\n");
	return (ret);
}
