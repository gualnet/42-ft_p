/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_d_space.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 19:30:22 by galy              #+#    #+#             */
/*   Updated: 2017/02/08 18:41:35 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*flag_space_d_exec(char *str, t_flags *flag)
{
	char	*newstr;

	if (((int)ft_strlen(str) >= flag->precision) && (flag->precision_on == 1))
		return (str);
	if (ft_atoll(str) < 0)
		return (str);
	if (str[0] == '0' && str[1] == '0')
	{
		str[0] = ' ';
		return (str);
	}
	newstr = ft_strjoin(" ", str);
	free(str);
	return (newstr);
}
