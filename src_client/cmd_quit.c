/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_quit.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/03 16:07:43 by galy              #+#    #+#             */
/*   Updated: 2018/07/24 13:20:08 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"


void	quit_process(t_vault *vault)
{

	free_vault(vault);




}

int		cmd_quit(t_vault *vault, char *str)
{

	free(str);
	quit_process(vault);

	ft_printf("[*] ftp client : \"GOOD BYE !!!\"");


	return (-999);
}
