/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cwd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/20 16:20:17 by galy              #+#    #+#             */
/*   Updated: 2018/07/11 21:27:13 by galy             ###   ########.fr       */
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

int		partial_path(t_vault *vault, char *cmd)
{
	char	*tmp;
	// trouver ou changer pour avoir le bon path enregister dans le vault
	ft_printf("00>vault->cwd [%p][%s]\n", vault->cwd, vault->cwd);
	tmp = vault->cwd;
	vault->cwd = ft_strjoin(tmp, "/");
	free(tmp);
	tmp = vault->cwd;
	vault->cwd = ft_strjoin(tmp, cmd + 4);
	free(tmp);
	// for (int i = 0; vault->cwd[i] != '\0'; i++)
	// 	ft_printf("TEST[%d][%d][%c]\n",i,vault->cwd[i],vault->cwd[i]);
	truncate_end_signs(vault->cwd);
	ft_printf("-->vault->cwd [%s]\n", vault->cwd);
	// for (int i = 0; vault->cwd[i] != '\0'; i++)
	// 	ft_printf("TEST[%d][%d][%c]\n",i,vault->cwd[i],vault->cwd[i]);
	
	return (1);
}

int		goto_new_rep(t_vault *vault, char *cmd)
{
	char	*tmp;

	if (ft_strncmp("CWD ..\x0a\x0d", cmd, ft_strlen("CWD ..\x0a\x0d")) == 0)
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
