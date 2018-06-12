/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_o.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 17:43:49 by galy              #+#    #+#             */
/*   Updated: 2017/02/08 19:56:58 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*check_flag_omod(char *strnbr, t_flags *flag)
{
	if (flag->precision_on == 1)
		strnbr = flag_precision_d_exec(strnbr, flag);
	if (flag->sharp == 1 && strnbr[0] != '0')
		strnbr = flag_sharp_oexec(strnbr);
	if (flag->width != 0)
		strnbr = flag_width_d_exec(strnbr, flag);
	return (strnbr);
}

int			flag_o(va_list ap, t_flags *flag)
{
	uintmax_t	nbr;
	char		*strnbr;
	char		*strnbrtmp;

	if (flag->fl_h == 2)
		strnbr = ft_ubase_converter(va_arg(ap, unsigned int), BASE_OCT,\
		sizeof(char) * 8);
	else if (flag->fl_h == 1)
		strnbr = ft_ubase_converter(va_arg(ap, unsigned int), BASE_OCT,\
		sizeof(short) * 8);
	else
	{
		strnbrtmp = ft_ulltoa(va_arg(ap, uintmax_t));
		strnbr = ft_ubase_converter(ft_atoll(strnbrtmp), BASE_OCT,\
		sizeof(unsigned long long) * 8);
		free(strnbrtmp);
	}
	strnbr = check_flag_omod(strnbr, flag);
	ft_putbuffer(strnbr);
	nbr = (int)ft_strlen(strnbr);
	free(strnbr);
	return (nbr);
}
