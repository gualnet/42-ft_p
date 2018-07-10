/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/30 14:08:05 by galy              #+#    #+#             */
/*   Updated: 2018/07/10 19:50:32 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

/*
**	cd -> cwd
*/

void	handle_cd_rsp(char *rsp)
{
	int		code;
	
	ft_printf("SRV RSP [%s]\n", rsp);
	code = ft_atoi(rsp);
	if (code > 199 && code < 300)
		ft_printf("SUCCESS\n");
	else if (code > 199 && code < 300)
		ft_printf("FAILURE\n");
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
		// ft_printf("\nSearch[%d] \'%s\' in \'%s\'\n", i, tmp, lines[i]);
		if (ft_strstr(lines[i], tmp) != NULL && ft_strstr(lines[i], tmp) != lines[i])
		{
			// ft_printf("une occurance\n");
			inlines = ft_strsplit(lines[i], ' ');
			while (inlines[j] != NULL)
			{
				if (inlines[j][0] == 'd' && inlines[8] != NULL && \
				ft_strcmp(inlines[8], tmp) == 0)
				{
					// ft_printf("BINGOoooooo\n");
					match = 1;
				}
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
	cmd = ft_strjoin("CWD ", tmp);
	free(tmp);
	free(str);
	return (cmd);
}

int		cmd_cd(t_vault *vault, char *str)
{
	char	*cmd;
	char	*rsp;

	// ft_printf("001 [%s]\n", vault->dir_content_name);
	if (vault->dir_content_name == NULL)
		cmd_list(vault, ft_strdup(str));
	// ft_printf("001 [%s]\n", vault->dir_content_name);
	
	if (verif_dir(vault->dir_content, str) != 1)
	{
		ft_printf("[*] Error internal process failure, abort command\n");
		return (-1);
	}
	cmd = build_cmd(str);
	if (send(vault->csc, cmd, ft_strlen(cmd), 0) < 0)
		ft_printf("[*] Error sendind cd commande \n");
	free(cmd);

	rsp = cmd_receiver(vault->csc);
	handle_cd_rsp(rsp);

	return (1);
}
