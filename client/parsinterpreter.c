/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsinterpreter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 12:39:59 by galy              #+#    #+#             */
/*   Updated: 2018/07/12 19:30:43 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

char	*force_cmd_toupper(char *str)
{
	int		i;
	char	*tmp;

	tmp = ft_strchr(str, ' ');
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
	// ft_printf("len(%d)\n", ft_strlen(str));
	if (ft_strncmp(str, "PWD", 3) == 0)
		return (cmd_pwd(vault, str, CMD_PRINT));
	if (ft_strncmp(str, "CD", 2) == 0)
		return (cmd_cd(vault, str), CMD_PRINT);
	if (ft_strncmp(str, "LS", 2) == 0)
		return (cmd_list(vault, str, CMD_PRINT));
	if (ft_strncmp(str, "HELP", 4) == 0)
	{
		int i = 0;
		while (i < 4)
		{
			sleep(1);
			ft_putchar('.');
			i++;
		}
		ft_printf("\n\tSOS lol ;)\n");
		return (1);
	}
	
	return (-1);
}

void	parsinterpreter(t_vault *vault, char *str)
{
	// ft_printf("\n=====PARSINTERPRETER=====\n");
	char *tmp;
	tmp = force_cmd_toupper(str);

	str = ft_strtrim(tmp);
	if (str != tmp)
		free(tmp);


	if (cmd_box(vault, str) < 0)
		ft_printf("\n[*] Unvalid commande see \"help\"\n");
	// else
	// 	ft_printf("\n[*] cmd sent\n");

}