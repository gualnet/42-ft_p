/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_cwd_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 15:35:27 by galy              #+#    #+#             */
/*   Updated: 2018/08/10 15:43:39 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

int		check_path_validity(t_vault *vault, char *req_path)
{
	size_t	i;
	int		cpt;

	i = 0;
	cpt = 0;
	while (req_path[i] != '\0')
	{
		if (req_path[i] == '/')
			cpt++;
		i++;
	}
	if (cpt <= 1)
		return (1);
	i = 0;
	while (vault->root_wd[i] == req_path[i])
		i++;
	if (i < ft_strlen(vault->root_wd))
	{
		cwd_cmd_response(vault, -3);
		return (-1);
	}
	return (1);
}
