/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsinterpreter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 12:39:59 by galy              #+#    #+#             */
/*   Updated: 2018/08/20 17:11:20 by galy             ###   ########.fr       */
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
	if (tmp == NULL)
	{
		tmp = str + ft_strlen(str);
	}
	i = 0;
	while ((str + i) < tmp)
	{
		str[i] = ft_toupper(str[i]);
		i++;
	}
	return (str);
}

int		cmd_box(t_vault *vault, char *str)
{
	if (ft_strncmp(str, "PWD\x0d", 4) == 0)
		return (cmd_pwd(vault, str, CMD_PRINT));
	if (ft_strncmp(str, "LS\x0d", 3) == 0)
		return (cmd_ls(vault, str, CMD_PRINT));
	if (ft_strncmp(str, "QUIT\x0d", 5) == 0)
		return (cmd_quit(vault, str));
	if (ft_strncmp(str, "CD ", 3) == 0 || ft_strncmp(str, "CD\t", 3) == 0)
		return (cmd_cd(vault, str));
	if (ft_strncmp(str, "GET ", 4) == 0 || ft_strncmp(str, "GET\t", 4) == 0)
		return (cmd_get_file(vault, str));
	if (ft_strncmp(str, "PUT ", 4) == 0 || ft_strncmp(str, "PUT\t", 4) == 0)
		return (cmd_put_file(vault, str));
	if (ft_strncmp(str, "MKD ", 4) == 0 || ft_strncmp(str, "MKD\t", 4) == 0)
		return (cmd_mkd(vault, str));
	if (ft_strncmp(str, "RMD ", 4) == 0 || ft_strncmp(str, "RMD\t", 4) == 0)
		return (cmd_rmd(vault, str));
	return (-888);
}

int		parsinterpreter(t_vault *vault, char *str)
{
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
		close(vault->csd);
		vault->csd = 0;
	}
	if (ret == -888)
	{
		free(str);
		ft_printf("\n[*] Unvalid commande see \"help\"\n");
	}
	return (ret);
}
