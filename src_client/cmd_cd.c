/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 14:08:05 by galy              #+#    #+#             */
/*   Updated: 2018/07/27 15:32:28 by galy             ###   ########.fr       */
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
		cmd_pwd(vault, ft_strdup("useless"), CMD_NOPRINT);
		ft_printf("[SUCCESS] %s\n", vault->s_cwd);
	}
	else if (code > 400 )
		ft_printf("[FAILURE] \n");
	else
		ft_printf("CODE NON HANDLED\n");
	free(rsp);
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
		if (ft_strstr(lines[i], tmp) != NULL && \
		ft_strstr(lines[i], tmp) != lines[i])
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

char	*build_cmd(char *str)
{
	char	*cmd;
	char	*tmp;

	tmp = ft_strdup(str + 3);
	truncate_end_signs(tmp);
	cmd = ft_strjoin("CWD ", tmp);
	free(tmp);
	tmp = cmd;
	cmd = ft_strjoin(tmp, "\x0a\x0d");
	free(tmp);
	free(str);
	return (cmd);
}

int		cmd_cd(t_vault *vault, char *str)
{
	int		ret;
	char	*cmd;
	char	*rsp;

	// ft_printf("CD STR [%s]\n", str);
	if (vault->s_dir_content_name == NULL)
	{
		cmd_pwd(vault, ft_strdup(str), CMD_NOPRINT);
		cmd_ls(vault, ft_strdup(str), CMD_NOPRINT);
	}
	if (ft_strncmp(str + 3, ".\x0d", 2) == 0)
	{
		ft_printf("[SUCCESS] %s\n", vault->s_cwd);
		return (1);
	}
	if ((ret = verif_dir(vault->s_dir_content, str)) < 0)
	{
		ft_printf("[FAILURE] Error internal process failure, abort command\n");
		return (-1);
	}
	else if (ret == 0)
	{
		ft_printf("[FAILURE] Error in parameters\n");
		return (-1);
	}
	cmd = build_cmd(str);
	if (send(vault->csc, cmd, ft_strlen(cmd), 0) < 0)
		ft_printf("[FAILURE] Error sendind cd commande \n");
	free(cmd);
	if ((rsp = cmd_receiver(vault->csc)) == NULL)
		return (-1);
	handle_cd_rsp(vault, rsp);
	return (1);
}
