/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   store_user.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 18:51:46 by galy              #+#    #+#             */
/*   Updated: 2018/06/14 12:35:42 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

#define START_USR_NAME 5
#define RSP_ERROR 0
#define RSP_VALID 1


void	user_response(t_vault *vault, int num)
{
	char *msg;

	if (num == 1)
		msg = "331 \x0a\x0d";
	else
		msg = "501 \x0a\x0d"; // error in param command
	if (write(vault->cs, msg, ft_strlen(msg) + 1) != \
		(ssize_t)(ft_strlen(msg) + 1))
		ft_printf("[%d]Echec envoi..\n", getpid());
	else
		ft_printf("[%d] sent : [%s]\n", getpid(), msg);
}

int		store_user(t_vault *vault, char *cmd)
{
	int next_state;
	int i;
	
	next_state = 2;
	i = START_USR_NAME;
	if (ft_strlen(cmd) < START_USR_NAME)
	{
		user_response(vault, RSP_ERROR);
		ft_printf("error 01\n");
	}
	vault->name = ft_strdup(cmd + START_USR_NAME);
	
	i = 0;
	while (vault->name[i] != '\x0a')
		i++;
	vault->name[i - 1] = '\0';
	vault->name[i] = '\0';

	if (ft_strlen(vault->name) < (size_t)(i - START_USR_NAME) || \
	ft_strlen(vault->name) == 0)
	{
		user_response(vault, RSP_ERROR);
		ft_printf("error 02\n");
	}

	user_response(vault, RSP_VALID);
	return (next_state);
}