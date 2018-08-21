/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_plus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/03 19:17:27 by galy              #+#    #+#             */
/*   Updated: 2017/02/13 11:27:47 by kriz             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*flag_plus_exec(char *str, t_flags *flag)
{
	char	*newstr;

	if (ft_atoll(str) < 0)
		return (str);
	else if (str[0] == '0' && ft_strlen(str) > 1 && flag->precision_on == 0)
	{
		str[0] = '+';
		return (str);
	}
	else
	{
		if ((newstr = ft_strjoin("+", str)) == NULL)
			exit(-1);
	}
	free(str);
	return (newstr);
}
