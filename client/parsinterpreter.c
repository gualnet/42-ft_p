/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsinterpreter.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/29 12:39:59 by galy              #+#    #+#             */
/*   Updated: 2018/07/04 12:42:50 by galy             ###   ########.fr       */
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

int		cmd_box(int sock, char *str)
{
	// ft_printf("\n=====CMD_BOX=====\n");
	// ft_printf("len(%d)\n", ft_strlen(str));
	if (ft_strncmp(str, "PWD", 3) == 0)
		return (cmd_pwd(sock, str));
	if (ft_strncmp(str, "CD", 2) == 0)
		return (cmd_cd(sock, str));
	if (ft_strncmp(str, "LIST", 2) == 0)
		return (cmd_list(sock, str));
	
	return (-1);
}

void	parsinterpreter(int sock, char *str)
{
	// ft_printf("\n=====PARSINTERPRETER=====\n");
	char *tmp;
	tmp = force_cmd_toupper(str);

	str = ft_strtrim(tmp);
	if (str != tmp)
		free(tmp);


	if (cmd_box(sock, str) < 0)
		ft_printf("\n[*] Unvalid commande see \"help\"\n");
	else
		ft_printf("\n[*] cmd sent\n");

}