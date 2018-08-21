/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_filler_cs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 23:44:53 by galy              #+#    #+#             */
/*   Updated: 2017/02/07 20:31:18 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flag_cmaj_filler(t_flags *flag)
{
	flag->conv_type = 'c';
	flag->fl_l = 1;
	flag->len += 1;
	flag->end = 1;
	flag->sharp = 0;
}

void	flag_cmin_filler(t_flags *flag)
{
	flag->conv_type = 'c';
	flag->len += 1;
	flag->end = 1;
	flag->sharp = 0;
}

void	flag_smaj_filler(t_flags *flag)
{
	flag->conv_type = 's';
	flag->fl_l = 1;
	flag->fl_h = 0;
	flag->len += 1;
	flag->end = 1;
	flag->sharp = 0;
}

void	flag_smin_filler(t_flags *flag)
{
	flag->conv_type = 's';
	flag->len += 1;
	flag->end = 1;
	flag->sharp = 0;
}
