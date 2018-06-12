/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 19:22:35 by galy              #+#    #+#             */
/*   Updated: 2017/02/15 16:38:38 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*check_flag_mod(char *strnbr, t_flags *flag)
{
	if (flag->precision_on == 1)
		strnbr = flag_precision_d_exec(strnbr, flag);
	if (flag->plus != 0 && flag->width == 0)
		strnbr = flag_plus_exec(strnbr, flag);
	if (flag->width != 0 && (flag->precision < flag->width))
		strnbr = flag_width_d_exec(strnbr, flag);
	if (flag->plus != 0 && flag->width != 0)
		strnbr = flag_plus_exec(strnbr, flag);
	if (flag->space != 0)
		strnbr = flag_space_d_exec(strnbr, flag);
	return (strnbr);
}

static int	resprint(char *strnbr, t_flags *flag)
{
	int len;

	strnbr = check_flag_mod(strnbr, flag);
	ft_putbuffer(strnbr);
	len = ft_strlen(strnbr);
	free(strnbr);
	return (len);
}

int			flag_d(va_list ap, t_flags *flag)
{
	char	*strnbr;
	short	sint;
	char	cint;

	if (flag->fl_h == 2)
	{
		cint = va_arg(ap, int);
		strnbr = ft_itoa(cint);
	}
	else if (flag->fl_h == 1)
	{
		sint = va_arg(ap, int);
		strnbr = ft_itoa(sint);
	}
	else if (flag->fl_l == 1)
		strnbr = ft_lltoa(va_arg(ap, long));
	else if (flag->fl_l == 2 || flag->fl_j)
		strnbr = ft_lltoa(va_arg(ap, long long));
	else if (flag->fl_z == 1)
		strnbr = ft_lltoa(va_arg(ap, ssize_t));
	else
		strnbr = ft_imaxtoabase(va_arg(ap, int), BASE_DEC,\
		sizeof(long long) * 8);
	return (resprint(strnbr, flag));
}
