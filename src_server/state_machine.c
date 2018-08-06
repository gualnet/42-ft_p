/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state_machine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/13 17:37:42 by galy              #+#    #+#             */
/*   Updated: 2018/08/06 19:06:06 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

/*
**	State_machine is useless but already there ¯\(**)/¯
*/

int		state_machine(t_vault *vault, uint state)
{
	char	buff[R_BUFF_SIZE];

	while (state != 999)
	{
		read_sock(vault, buff);
		state = dispatcher(vault, buff);
	}
	return (1);
}
