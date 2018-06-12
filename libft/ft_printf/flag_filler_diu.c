/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_filler_diu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 23:44:53 by galy              #+#    #+#             */
/*   Updated: 2017/02/07 20:31:36 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flag_dmaj_filler(t_flags *flag)
{
	flag->conv_type = 'd';
	flag->fl_l = 1;
	flag->fl_h = 0;
	flag->len += 1;
	flag->end = 1;
	flag->sharp = 0;
}

void	flag_dmin_filler(t_flags *flag)
{
	flag->conv_type = 'd';
	flag->len += 1;
	flag->end = 1;
	flag->sharp = 0;
}

void	flag_imin_filler(t_flags *flag)
{
	flag->conv_type = 'd';
	flag->len += 1;
	flag->end = 1;
	flag->sharp = 0;
}

void	flag_umaj_filler(t_flags *flag)
{
	flag->conv_type = 'u';
	flag->fl_l = 1;
	flag->fl_h = 0;
	flag->len += 1;
	flag->end = 1;
	flag->sharp = 0;
	flag->space = 0;
	flag->plus = 0;
}

void	flag_umin_filler(t_flags *flag)
{
	flag->conv_type = 'u';
	flag->len += 1;
	flag->end = 1;
	flag->sharp = 0;
}
