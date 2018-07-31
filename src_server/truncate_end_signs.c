/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   truncate_end_signs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 21:21:44 by galy              #+#    #+#             */
/*   Updated: 2018/07/12 21:22:03 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ftp_server.h"

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