/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_filler_02.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 21:59:45 by galy              #+#    #+#             */
/*   Updated: 2017/02/07 20:31:00 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flag_width_filler(t_flags *flag)
{
	int nbspace;

	nbspace = ft_atoi(&flag->start[flag->len]);
	flag->width = nbspace;
	while (ft_isdigit(flag->start[flag->len]))
		flag->len = flag->len + 1;
}

void	flag_precision_filler(t_flags *flag)
{
	flag->precision_on = 1;
	flag->len += 1;
	if (!ft_isdigit(flag->start[flag->len]) ||\
	(ft_atoi(&flag->start[flag->len]) == 0))
		flag->precision = 0;
	else
		flag->precision = ft_atoi(&flag->start[flag->len]);
	while (ft_isdigit(flag->start[flag->len]))
		flag->len += 1;
	flag->zero = 0;
}
