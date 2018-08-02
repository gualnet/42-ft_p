/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_vault.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 16:22:35 by galy              #+#    #+#             */
/*   Updated: 2018/08/02 15:02:43 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_client.h"

void	free_vault(t_vault *vault)
{
	if (vault == NULL)
		return ;
	if (vault->name != NULL)
		free(vault->name);
	if (vault->passw != NULL)
		free(vault->passw);
	if (vault->s_cwd != NULL)
		free(vault->s_cwd);
	if (vault->s_dir_content != NULL)
		free(vault->s_dir_content);
	if (vault->s_dir_content_name != NULL)
		free(vault->s_dir_content_name);
	if (vault->c_cwd != NULL)
		free(vault->c_cwd);
	if (vault->c_dir_content != NULL)
		free(vault->c_dir_content);
	if (vault->c_dir_content_name != NULL)
		free(vault->c_dir_content_name);
}

void	init_vault(t_vault *vault)
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
