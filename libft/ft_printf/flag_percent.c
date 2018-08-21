/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_percent.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 16:58:00 by galy              #+#    #+#             */
/*   Updated: 2017/02/08 19:58:04 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		flag_percent_filler(t_flags *flag)
{
	flag->conv_type = '%';
	flag->len += 1;
	flag->end = 1;
}

static char	*check_flag_percentmod(char *str, t_flags *flag)
{
	if (flag->width != 0)
		str = flag_width_d_exec(str, flag);
	return (str);
}

int			flag_percent(t_flags *flag)
{
	char	*str;
	int		len;

	str = ft_strnew(1);
	str[0] = '%';
	str = check_flag_percentmod(str, flag);
	ft_putbuffer(str);
	len = ft_strlen(str);
	free(str);
	return (len);
}
