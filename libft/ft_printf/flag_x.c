/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_x.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 23:12:35 by galy              #+#    #+#             */
/*   Updated: 2017/02/08 19:58:43 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	majx(char *xstr)
{
	int				i;

	i = 0;
	while (xstr[i] != '\0')
	{
		xstr[i] = ft_toupper(xstr[i]);
		i++;
	}
}

static char	*check_flag_xmod(t_flags *flag, char *xstr)
{
	if (flag->precision_on == 1)
		xstr = flag_precision_x_exec(xstr, flag);
	if (flag->width != 0)
		xstr = flag_width_x_exec(xstr, flag);
	if (flag->sharp == 1 && flag->width == 0)
		xstr = flag_sharp_x_exec(xstr);
	if (flag->maj != 0)
		majx(xstr);
	return (xstr);
}

static char	*length_select(va_list ap, t_flags *flag)
{
	char	*xstr;

	if (flag->fl_h == 2)
		xstr = ft_ubase_converter(va_arg(ap, unsigned int),\
		BASE_HEX, sizeof(char) * 8);
	else if (flag->fl_h == 1)
		xstr = ft_ubase_converter(va_arg(ap, unsigned int),\
		BASE_HEX, sizeof(short) * 8);
	else if (flag->fl_l != 0)
		xstr = ft_ubase_converter(va_arg(ap, unsigned long long),\
		BASE_HEX, sizeof(long long) * 8);
	else if (flag->fl_j == 1)
		xstr = ft_ubase_converter(va_arg(ap, uintmax_t),\
		BASE_HEX, sizeof(uintmax_t) * 8);
	else if (flag->fl_z == 1)
		xstr = ft_ubase_converter(va_arg(ap, size_t),\
		BASE_HEX, sizeof(size_t) * 8);
	else
		xstr = ft_ubase_converter(va_arg(ap, unsigned int),\
		BASE_HEX, sizeof(long long) * 8);
	return (xstr);
}

int			flag_x(va_list ap, t_flags *flag)
{
	char	*xstr;
	int		len;

	xstr = length_select(ap, flag);
	xstr = check_flag_xmod(flag, xstr);
	ft_putbuffer(xstr);
	len = (int)ft_strlen(xstr);
	free(xstr);
	return (len);
}
