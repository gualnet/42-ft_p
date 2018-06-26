/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 16:20:17 by galy              #+#    #+#             */
/*   Updated: 2018/06/26 15:39:13 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

// 501 Erreur de syntaxe dans le paramètres ou arguments.
// 550 Service fichier non traité. Fichier non accessible (ex., fichier non trouvé, accèsrefusé).

void	cwd_cmd_response(t_vault *vault, int status)
{
	char *msg;
	
	msg = "";
	if (status == 1)
	{
		msg = "212 Directory status.\x0a\x0d";
	}
	else if (status == -1)
	{
		msg = "451 Requested action aborted, local error in processing.\x0a\x0d";
	}
	else if (status == -2)
	{
		msg = "501 Syntax error in parameters or arguments\x0a\x0d";
	}
	sender_sock(vault, msg);
}

int		dot_dot(t_vault *vault)
{
	size_t	len;

	len = ft_strlen(vault->cwd);
	while (len != 0)
	{
		if (vault->cwd[len] == '/')
		{
			vault->cwd[len] = '\0';
			break ;
		}
		len--;
	}
	return (0);
}

int		partial_path(t_vault *vault, char *cmd)
{
	char	*tmp;

	tmp = vault->cwd;
	vault->cwd = ft_strjoin(tmp, "/");
	free(tmp);
	tmp = vault->cwd;
	vault->cwd = ft_strjoin(tmp, cmd + 4);
	free(tmp);
	if ((tmp = ft_strchr(vault->cwd, '\r')) != NULL)
	{
		tmp[0] = '\0';
		// ft_printf("=========%s========\n", vault->cwd);
	}
	else
		return (-1);
	return (1);
}

int		goto_new_rep(t_vault *vault, char *cmd)
{
	char	*tmp;

	if (ft_strncmp("CWD ..\r\n", cmd, ft_strlen("CWD ..\r\n")) == 0)
	{
		dot_dot(vault);
		return (1);
	}
	else if (ft_strchr(cmd, '/') == NULL)
	{
		return (partial_path(vault, cmd));
	}
	free(vault->cwd);
	vault->cwd = ft_strdup(cmd + 4);
	tmp = ft_strchr(vault->cwd, '\r');
	if (tmp != NULL)
	{
		tmp[0] = '\0';
		// ft_printf("=========%s========\n", vault->cwd);
	}
	else
		return (-1);
	return (1);
}

int		cmd_cwd(t_vault *vault, char *cmd)
{
	int	ret;

	if (verif_cmd_minimum_len(cmd, ML_CWD) != 1)
	{
		cwd_cmd_response(vault, -2);
		return (-1);
	}
	ret = goto_new_rep(vault, cmd);
	cwd_cmd_response(vault, ret);
	return (0);
}
