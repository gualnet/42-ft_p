/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vault.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 16:22:35 by galy              #+#    #+#             */
/*   Updated: 2018/07/19 16:31:32 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"ftp_client.h"

void	zero_vault(t_vault *vault)
{
	vault->csc = 0;
	vault->csd = 0;
	vault->cmd_sock = 0;
	vault->dtp_sock = 0;
	vault->name = NULL;
	vault->passw = NULL;
	vault->s_cwd = NULL;
	vault->s_dir_content_name = NULL;
	vault->s_dir_content = NULL;

}

void	init_vault(t_vault *vault)
{
	zero_vault(vault);
}