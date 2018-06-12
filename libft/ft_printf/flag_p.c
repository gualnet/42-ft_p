/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_p.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/08 12:14:52 by galy              #+#    #+#             */
/*   Updated: 2017/02/08 19:58:13 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*check_flag_pmod(t_flags *flag, char *xstr)
{
	if (flag->precision_on == 1)
		xstr = flag_precision_p_exec(xstr, flag);
	if (flag->sharp == 1)
		xstr = flag_sharp_p_exec(xstr);
	if (flag->width != 0)
		xstr = flag_width_p_exec(xstr, flag);
	return (xstr);
}

int			flag_p(va_list ap, t_flags *flag)
{
	char			*xstr;
	char			*xstr2;
	int				len;

	if (flag->fl_h == 2)
		xstr2 = ft_ubase_converter(va_arg(ap, unsigned int),\
		BASE_HEX, sizeof(unsigned short) * 8);
	if (flag->fl_h == 1)
		xstr2 = ft_ubase_converter(va_arg(ap, unsigned int),\
		BASE_HEX, sizeof(unsigned short) * 8);
	if (flag->fl_l != 0)
	{
		xstr = ft_ulltoa(va_arg(ap, uintmax_t));
		xstr2 = ft_ubase_converter(ft_atoll(xstr), BASE_HEX,\
		sizeof(unsigned long long) * 8);
		free(xstr);
	}
	else
		xstr2 = ft_ubase_converter(va_arg(ap, unsigned int),\
		BASE_HEX, sizeof(long long) * 8);
	xstr = check_flag_pmod(flag, xstr2);
	ft_putbuffer(xstr);
	len = (int)ft_strlen(xstr);
	free(xstr);
	return (len);
}
