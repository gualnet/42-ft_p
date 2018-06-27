/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_filler_lhjz.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 23:49:29 by galy              #+#    #+#             */
/*   Updated: 2017/02/02 03:33:58 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flag_h_filler(t_flags *flag)
{
	if (flag->start[flag->len + 1] == 'h')
	{
		flag->fl_h = 2;
		flag->len += 2;
	}
	else
	{
		flag->fl_h = 1;
		flag->len += 1;
	}
}

void	flag_l_filler(t_flags *flag)
{
	if (flag->start[flag->len + 1] == 'l')
	{
		flag->fl_l = 2;
		flag->len += 2;
	}
	else
	{
		flag->fl_l = 1;
		flag->len += 1;
	}
}

void	flag_j_filler(t_flags *flag)
{
	flag->fl_j = 1;
	flag->len += 1;
}

void	flag_z_filler(t_flags *flag)
{
	flag->fl_z = 1;
	flag->len += 1;
}
