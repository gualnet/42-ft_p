/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_sharp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 19:54:22 by galy              #+#    #+#             */
/*   Updated: 2017/02/08 18:57:38 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*flag_sharp_x_exec(char *str)
{
	char *tmpstr;

	if (ft_atoi(str) == 0)
		return (str);
	tmpstr = ft_strjoin("0x", str);
	free(str);
	return (tmpstr);
}

char	*flag_sharp_p_exec(char *str)
{
	char *tmpstr;

	tmpstr = ft_strjoin("0x", str);
	free(str);
	return (tmpstr);
}

char	*flag_sharp_oexec(char *str)
{
	char *tmpstr;

	if (ft_strcmp(str, "0") == 0)
		return (str);
	tmpstr = ft_strjoin("0", str);
	free(str);
	return (tmpstr);
}
