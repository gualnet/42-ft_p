/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 14:08:05 by galy              #+#    #+#             */
/*   Updated: 2018/07/11 20:42:18 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

/*
**	cd -> cwd
*/

void	handle_cd_rsp(t_vault *vault, char *rsp)
{
	int		code;
	
	// ft_printf("SRV RSP [%s]\n", rsp);
	code = ft_atoi(rsp);
	if (code > 120 && code < 300)
	{
		ft_printf("[*] SUCCESS\n");
		cmd_pwd(vault, ft_strdup("useless"), CMD_NOPRINT);
	}
	else if (code > 400 )
		ft_printf("[*] FAILURE\n");
	else
		ft_printf("CODE NON HANDLED\n");
	free(rsp);
	ft_printf("[>] Working dir : %s\n", vault->cwd);
}

void	truncate_end_signs(char *str)
{
	char	*tmp;

	tmp = NULL;
	if ((tmp = ft_strstr(str, "\x0a\x0d")) != NULL)
	{
		tmp[0] = '\0';
		// ft_printf("trunc 01[%s]\n", str);
	}
	else if ((tmp = ft_strchr(str, '\r')) != NULL)
	{
		tmp[0] = '\0';
		// ft_printf("trunc 02[%s]\n", str);
	}
	else if ((tmp = ft_strchr(str, '\n')) != NULL)
	{
		tmp[0] = '\0';
		// ft_printf("trunc 03[%s]\n", str);
	}
}

int		verif_dir(char **lines, char *str)
{
	char	*tmp;
	char	**inlines;
	int		match;
	int		i;
	int		j;
	
	if (ft_strlen(str) <= 3)
		return (-1);
	
	tmp = ft_strdup(str + 3);
	truncate_end_signs(tmp);
	i = 1;
	j = 0;
	match = 0;
	while (lines[i] != NULL)
	{
		if (ft_strstr(lines[i], tmp) != NULL && ft_strstr(lines[i], tmp) != lines[i])
		{
			inlines = ft_strsplit(lines[i], ' ');
			while (inlines[j] != NULL)
			{
				if (inlines[j][0] == 'd' && inlines[8] != NULL && \
				ft_strcmp(inlines[8], tmp) == 0)
					match = 1;
				j++;
			}
		}
		i++;
	}
	free(tmp);
	return (match);
}

char	*build_cmd(t_vault *vault, char *str)
{
	char	*cmd;
	char	*tmp;
	// size_t	i;

	ft_printf("BB0 [%s]\n", str, vault);
	tmp = ft_strdup(str + 3);
	// if (ft_strstr(tmp, "..") != NULL)
	// {
	// 	free(tmp);
	// 	tmp = ft_strdup(vault->cwd);
	// 	i = ft_strlen(tmp);
	// 	while (&tmp[i] != tmp)
	// 	{
	// 		if (tmp[i] == '/')
	// 		{
	// 			tmp[i] = '\0';
	// 			break ;
	// 		}
	// 		i--;
	// 	}
	// }
	
	ft_printf("BB1 [%s]\n", tmp);
	truncate_end_signs(tmp);
	cmd = ft_strjoin("CWD ", tmp);
	ft_printf("BB2 [%s]\n", cmd);
	free(tmp);
	tmp = cmd;
	cmd = ft_strjoin(tmp, "\x0a\x0d");
	ft_printf("BB3 [%s]\n", cmd);
	free(tmp);
	free(str);
	return (cmd);
}

int		cmd_cd(t_vault *vault, char *str)
{
	char	*cmd;
	char	*rsp;

	if (vault->dir_content_name == NULL)
	{
		ft_printf("001\n");
		cmd_pwd(vault, ft_strdup(str), CMD_NOPRINT);
		ft_printf("002\n");
		cmd_list(vault, ft_strdup(str), CMD_NOPRINT);
	}
	// ft_printf("CD STR [%s]\n", str);
	ft_printf("003\n");
	if (ft_strncmp(str + 3, "..", 2) == 0)
		cmd = NULL;
	else if (verif_dir(vault->dir_content, str) != 1)
	{
		ft_printf("[*] Error internal process failure, abort command\n");
		return (-1);
	}
	ft_printf("004\n");
	cmd = build_cmd(vault, str);
	ft_printf("005 [%s]\n", cmd);
	ft_printf("\033[33mCMD_CD SEND (%d char)[%s]\n\033[0m", ft_strlen(cmd), cmd);
	if (send(vault->csc, cmd, ft_strlen(cmd), 0) < 0)
		ft_printf("[*] Error sendind cd commande \n");
	free(cmd);
	ft_printf("006\n");
	rsp = cmd_receiver(vault->csc);
	ft_printf("007\n");
	handle_cd_rsp(vault, rsp);
	ft_printf("008\n");
	// cmd_list(vault, ft_strdup(str));
	return (1);
}
