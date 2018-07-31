/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 16:20:17 by galy              #+#    #+#             */
/*   Updated: 2018/07/12 21:21:57 by galy             ###   ########.fr       */
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
	else if (status == -3)
	{
		msg = "550 Requested action not taken. "
		"File unavailable (e.g., file not found, no access).\x0a\x0d";
	}
	sender_sock(vault, msg);
}

int		dot_dot(t_vault *vault)
{
	size_t	len;
	char	*tmp;

	if ((tmp = ft_strdup(vault->cwd)) == NULL)
		return (-1);
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
	if (ft_strlen(vault->root_wd) >= ft_strlen(vault->cwd))
	{
		free(vault->cwd);
		vault->cwd = tmp;
		return (-3);
	}
	else
		free(tmp);
	return (1);
}

int		partial_path(t_vault *vault, char *cmd)
{
	char	*tmp;

	// ft_printf("00>vault->cwd [%p][%s]\n", vault->cwd, vault->cwd);
	tmp = vault->cwd;
	vault->cwd = ft_strjoin(tmp, "/");
	free(tmp);
	tmp = vault->cwd;
	vault->cwd = ft_strjoin(tmp, cmd + 4);
	free(tmp);
	truncate_end_signs(vault->cwd);
	// ft_printf("-->vault->cwd [%s]\n", vault->cwd);
	return (1);
}

int		goto_new_rep(t_vault *vault, char *cmd)
{
	char	*tmp;

	if (ft_strncmp("CWD ..\x0a\x0d", cmd, ft_strlen("CWD ..\x0a\x0d")) == 0)
		return (dot_dot(vault));
	else if (ft_strchr(cmd, '/') == NULL)
		return (partial_path(vault, cmd));
	free(vault->cwd);
	vault->cwd = ft_strdup(cmd + 4);
	tmp = ft_strchr(vault->cwd, '\r');
	if (tmp != NULL)
		tmp[0] = '\0';
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
	if (vault->cwd == NULL)
	{
		if ((vault->cwd = loop_getcwd()) == NULL)
		{
			cwd_cmd_response(vault, -1);
			return (-1);
		}
	}
	ret = goto_new_rep(vault, cmd);
	cwd_cmd_response(vault, ret);
	return (0);
}
