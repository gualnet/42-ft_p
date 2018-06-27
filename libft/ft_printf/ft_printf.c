/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 16:11:34 by galy              #+#    #+#             */
/*   Updated: 2017/02/13 17:59:43 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_printf(const char *format, ...)
{
	int		ret_len;
	va_list	ap;

	va_start(ap, format);
	ret_len = sar(ap, format);
	va_end(ap);
	return (ret_len);
}

int		sar(va_list ap, const char *format)
{
	t_flags	*flag;
	int		ret_len;

	ret_len = 0;
	if ((flag = (t_flags*)ft_memalloc(sizeof(*flag))) == NULL)
		exit(-1);
	flag->start = (char *)format;
	while ((ft_strchr(flag->start, '%')) != NULL)
	{
		if (flag->error == 1)
			return (-1);
		reset_flag(flag);
		ret_len += printer(flag);
		ret_len += optimus(ap, flag);
		flag->start += flag->len;
	}
	ret_len += printer(flag);
	if (flag->error == 1)
		ret_len = -1;
	free(flag);
	return (ret_len);
}

/*
** imprime les caracteres en dehors des flag
*/

int		printer(t_flags *flag)
{
	int		i;

	i = 0;
	flag->decal = -1;
	while (flag->start[i] != '%' && flag->start[i] != '\0')
	{
		ft_putchar(flag->start[i]);
		i++;
	}
	flag->start = flag->start + i;
	return (i);
}

/*
**	transforme mes flags
*/

int		optimus(va_list ap, t_flags *flag)
{
	int		ret_len;

	ret_len = 0;
	flag->end = 0;
	while (flag->end == 0)
		list_flag_filler(flag);
	if (flag->conv_type != 0)
		ret_len = list_flag_exec(ap, flag);
	return (ret_len);
}

void	reset_flag(t_flags *flag)
{
	flag->end = 0;
	flag->conv_type = 0;
	flag->len = 1;
	flag->sharp = 0;
	flag->zero = 0;
	flag->plus = 0;
	flag->minus = 0;
	flag->space = 0;
	flag->width = 0;
	flag->precision = 0;
	flag->precision_on = 0;
	flag->sizemod = NULL;
	flag->decal = 0;
	flag->fl_l = 0;
	flag->fl_h = 0;
	flag->fl_j = 0;
	flag->fl_z = 0;
	flag->maj = 0;
	flag->error = 0;
}
