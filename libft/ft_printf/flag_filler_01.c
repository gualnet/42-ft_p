/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_filler_01.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 21:59:45 by galy              #+#    #+#             */
/*   Updated: 2017/02/07 18:17:45 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flag_sharp_filler(t_flags *flag)
{
	flag->sharp = 1;
	flag->len += 1;
}

void	flag_zero_filler(t_flags *flag)
{
	int nbr;

	nbr = 0;
	flag->len += 1;
	if (flag->minus == 0)
	{
		if ((nbr = ft_atoi(flag->start + flag->len)) != 0)
			flag->width = nbr;
		flag->zero = 1;
	}
	while (ft_isdigit(flag->start[flag->len]))
		flag->len += 1;
}

void	flag_minus_filler(t_flags *flag)
{
	flag->len += 1;
	flag->zero = 0;
	if ((flag->minus = ft_atoi(&flag->start[flag->len])) != 0)
		flag->width = flag->minus;
	flag->minus = 1;
	while (ft_isdigit(flag->start[flag->len]))
		flag->len += 1;
}

void	flag_space_filler(t_flags *flag)
{
	if (flag->plus == 0)
		flag->space = 1;
	flag->len += 1;
}

void	flag_plus_filler(t_flags *flag)
{
	flag->plus = 1;
	flag->space = 0;
	flag->len += 1;
}
