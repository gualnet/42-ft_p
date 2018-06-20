/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_user_pass.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 18:51:46 by galy              #+#    #+#             */
/*   Updated: 2018/06/20 18:21:33 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"


void	user_response(t_vault *vault, int num)
{
	char *msg;

	if (num == 1)
		msg = "331 Please specify the password\x0a\x0d";
	else if (num == 2)
		msg = "230 Login successful.. GG\x0a\x0d";
	else
		msg = "501 \x0a\x0d";	// error in param command

	sender_sock(vault, msg);
}

int		cmd_user(t_vault *vault, char *cmd)
{
	int next_state;
	int i;

	next_state = 2;
	i = CMD_SP_LEN;
	if (ft_strlen(cmd) < CMD_SP_LEN)
		user_response(vault, 0);
	vault->name = ft_strdup(cmd + CMD_SP_LEN);
	i = 0;
	while (vault->name[i] != '\x0a')
		i++;
	vault->name[i - 1] = '\0';
	vault->name[i] = '\0';
	if (ft_strlen(vault->name) < (size_t)(i - CMD_SP_LEN) || \
	ft_strlen(vault->name) == 0)
		user_response(vault, 0);
	user_response(vault, 1);
	return (next_state);
}

int		cmd_pass(t_vault *vault, char *cmd)
{
	int next_state;
	int i;
	
	next_state = 2;
	i = CMD_SP_LEN;
	if (ft_strlen(cmd) < CMD_SP_LEN)
		user_response(vault, 0);
	vault->passw = ft_strdup(cmd + CMD_SP_LEN);
	i = 0;
	while (vault->passw[i] != '\x0a')
		i++;
	vault->passw[i - 1] = '\0';
	vault->passw[i] = '\0';
	if (ft_strlen(vault->passw) < (size_t)(i - CMD_SP_LEN) || \
	ft_strlen(vault->passw) == 0)
		user_response(vault, 0);
	user_response(vault, 2);
	return (next_state);
}
