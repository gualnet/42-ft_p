/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vault.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 16:22:35 by galy              #+#    #+#             */
/*   Updated: 2018/07/24 13:18:24 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include	"ftp_client.h"

void	free_vault(t_vault *vault)
{
	if (vault == NULL)
		return ;
	
	if (vault->name != NULL)
		free(vault->name);
	if (vault->passw)
		free(vault->passw);
	if (vault->s_cwd)
		free(vault->s_cwd);
	if (vault->s_dir_content)
		free(vault->s_dir_content);
	if (vault->s_dir_content_name)
		free(vault->s_dir_content_name);
	if (vault->c_cwd)
		free(vault->c_cwd);
	if (vault->c_dir_content)
		free(vault->c_dir_content);
	if (vault->c_dir_content_name)
		free(vault->c_dir_content_name);
}

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