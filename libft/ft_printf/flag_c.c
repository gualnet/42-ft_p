/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_c.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/05 16:37:29 by galy              #+#    #+#             */
/*   Updated: 2017/02/13 20:31:26 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_flag_width_cmod(t_flags *flag)
{
	int i;

	i = 0;
	if (flag->width != i)
	{
		while (i != (flag->width - 1) && flag->minus == 0)
		{
			if (flag->zero == 1)
				ft_putchar('0');
			else
				ft_putchar(' ');
			i++;
		}
	}
	return (i);
}

static int	check_flag_minus_cmod(t_flags *flag)
{
	int i;

	i = 0;
	while (i < (flag->width - 1) && flag->minus == 1)
	{
		ft_putchar(' ');
		i++;
	}
	return (i);
}

int			flag_c(va_list ap, t_flags *flag)
{
	wchar_t	a;
	char	b;
	int		len;
	int		len_inter;

	len = 0;
	len += check_flag_width_cmod(flag);
	if (flag->fl_l == 1)
	{
		a = va_arg(ap, wchar_t);
		len_inter = ft_putwchar(a);
		if (len_inter == -1)
			flag->error = 1;
		len += len_inter;
	}
	else
	{
		b = va_arg(ap, int);
		ft_putchar(b);
		len += 1;
	}
	len += check_flag_minus_cmod(flag);
	return (len);
}
