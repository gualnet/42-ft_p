/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_cmd_form.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/24 10:17:24 by galy              #+#    #+#             */
/*   Updated: 2018/06/24 20:16:26 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

/*
** cmd_len should be equal to :
** num cmd char + space if it takes an arg + a least 1 char for arg + \r\n
*/

int		verif_cmd_minimum_len(char *cmd, size_t cmd_len)
{
	size_t size;

	if ((size = ft_strlen(cmd)) < cmd_len)
	{
		ft_printf("cmd is oo short to be a valide commande\n");
		return (-1);
	}
	return (1);

}