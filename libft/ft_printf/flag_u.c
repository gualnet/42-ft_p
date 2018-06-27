/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_u.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 15:47:32 by galy              #+#    #+#             */
/*   Updated: 2017/02/08 19:58:45 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*check_flag_umod(char *strnbr, t_flags *flag)
{
	if (flag->precision_on == 1)
		strnbr = flag_precision_d_exec(strnbr, flag);
	if (flag->width != 0 && (flag->precision < flag->width))
		strnbr = flag_width_d_exec(strnbr, flag);
	return (strnbr);
}

static char	*flag_type_umod(va_list ap, t_flags *flag)
{
	unsigned long long int	llnbr;
	char					*strnbr;

	if (flag->fl_h == 2)
		strnbr = ft_ubase_converter(va_arg(ap, unsigned int),\
		BASE_DEC, sizeof(char) * 8);
	else if (flag->fl_h == 1)
		strnbr = ft_ubase_converter(va_arg(ap, unsigned int),\
		BASE_DEC, sizeof(short) * 8);
	else
	{
		llnbr = va_arg(ap, long long int);
		if (llnbr == 0)
		{
			if ((strnbr = ft_strdup("0")) == NULL)
				exit(-1);
		}
		else
			strnbr = ft_ulltoa(llnbr);
	}
	return (strnbr);
}

int			flag_u(va_list ap, t_flags *flag)
{
	int						len;
	char					*strnbr;

	strnbr = flag_type_umod(ap, flag);
	strnbr = check_flag_umod(strnbr, flag);
	ft_putbuffer(strnbr);
	len = ft_strlen(strnbr);
	free(strnbr);
	return (len);
}
