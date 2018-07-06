/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 14:08:05 by galy              #+#    #+#             */
/*   Updated: 2018/07/04 16:37:43 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

/*
**	cd -> cwd
*/

void	handle_cd_rsp(char *rsp)
{
	ft_printf("SRV RSP [%s]\n", rsp);
	free(rsp);
}

char	*str_process(char *str)
{
	char	*tmp;
	char	*cmd;
	
	if ((tmp = ft_strdup("CWD ")) == NULL)
		return (NULL);
	if ((cmd = ft_strjoin(tmp, str + 3)) == NULL)
		return (NULL);
	ft_printf("JOIN VERIF [%s]\n", cmd);

	free(str);
	free(tmp);
	return (cmd);
}

int		cmd_cd(t_vault *vault, char *str)
{
	char	*rsp;

	if ((str = str_process(str)) == NULL)
	{
		ft_printf("[*] Error internal process failure, abort command\n");
		return (-1);
	}
	if (send(vault->csc, str, ft_strlen(str), 0) < 0)
		ft_printf("[*] Error sendind cd commande \n");
	free(str);

	rsp = cmd_receiver(vault->csc);
	handle_cd_rsp(rsp);

	return (1);
}
