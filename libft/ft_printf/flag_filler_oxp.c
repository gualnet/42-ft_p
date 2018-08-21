/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_filler_oxp.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 23:44:53 by galy              #+#    #+#             */
/*   Updated: 2017/02/07 20:31:51 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flag_omaj_filler(t_flags *flag)
{
	flag->conv_type = 'o';
	flag->fl_l = 1;
	flag->fl_h = 0;
	flag->len += 1;
	flag->end = 1;
}

void	flag_omin_filler(t_flags *flag)
{
	flag->conv_type = 'o';
	flag->len += 1;
	flag->end = 1;
}

void	flag_xmaj_filler(t_flags *flag)
{
	flag->conv_type = 'x';
	flag->len += 1;
	flag->maj = 1;
	flag->end = 1;
}

void	flag_xmin_filler(t_flags *flag)
{
	flag->conv_type = 'x';
	flag->len += 1;
	flag->end = 1;
}

void	flag_pmin_filler(t_flags *flag)
{
	flag->conv_type = 'p';
	flag->fl_l = 2;
	flag->sharp = 1;
	flag->len += 1;
	flag->end = 1;
}
