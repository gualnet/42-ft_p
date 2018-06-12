/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_s_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 12:33:08 by galy              #+#    #+#             */
/*   Updated: 2017/02/07 21:05:03 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*flag_precision_s_exec(char *str, t_flags *flag)
{
	int i;

	i = 0;
	if (flag->precision == 0)
	{
		if ((str = ft_strdup("")) == NULL)
			exit(-1);
		return (str);
	}
	str = ft_strdup(str);
	while (i < flag->precision && str[i] != '\0')
		i++;
	if (str[i] != '\0')
		str[i] = '\0';
	return (str);
}
