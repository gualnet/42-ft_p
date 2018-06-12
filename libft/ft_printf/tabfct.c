/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tabfct.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/28 15:14:51 by galy              #+#    #+#             */
/*   Updated: 2017/02/08 17:15:05 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			list_flag_exec(va_list ap, t_flags *flag)
{
	if (flag->conv_type == 'd')
		return (flag_d(ap, flag));
	if (flag->start[flag->len] == 'D')
		return (flag_d(ap, flag));
	if (flag->conv_type == 's')
		return (flag_s(ap, flag));
	if (flag->conv_type == 'S')
		return (flag_s(ap, flag));
	if (flag->conv_type == 'c')
		return (flag_c(ap, flag));
	if (flag->conv_type == 'x')
		return (flag_x(ap, flag));
	if (flag->conv_type == 'u')
		return (flag_u(ap, flag));
	if (flag->conv_type == 'p')
		return (flag_p(ap, flag));
	if (flag->conv_type == 'o')
		return (flag_o(ap, flag));
	if (flag->conv_type == '%')
		return (flag_percent(flag));
	if (flag->conv_type == 'b')
		return (flag_b(ap));
	return (-1);
}

static void	flag_filler_c(t_flags *flag, int i)
{
	if (flag->start[i] == 's')
		flag_smin_filler(flag);
	else if (flag->start[i] == 'x')
		flag_xmin_filler(flag);
	else if (flag->start[i] == 'X')
		flag_xmaj_filler(flag);
	else if (flag->start[i] == 'u')
		flag_umin_filler(flag);
	else if (flag->start[i] == 'U')
		flag_umaj_filler(flag);
	else if (flag->start[i] == 'o')
		flag_omin_filler(flag);
	else if (flag->start[i] == 'O')
		flag_omaj_filler(flag);
	else if (flag->start[i] == 'p')
		flag_pmin_filler(flag);
	else if (flag->start[i] == 'b')
		flag_b_filler(flag);
	else if (i == flag->len)
		flag->end = 1;
}

static void	flag_filler_b(t_flags *flag, int i)
{
	if (flag->start[i] == 'l')
		flag_l_filler(flag);
	else if (flag->start[i] == 'h')
		flag_h_filler(flag);
	else if (flag->start[i] == 'j')
		flag_j_filler(flag);
	else if (flag->start[i] == 'z')
		flag_z_filler(flag);
	else if (flag->start[i] == 'd')
		flag_dmin_filler(flag);
	else if (flag->start[i] == 'D')
		flag_dmaj_filler(flag);
	else if (flag->start[i] == 'i')
		flag_imin_filler(flag);
	else if (flag->start[i] == 'c')
		flag_cmin_filler(flag);
	else if (flag->start[i] == 'C')
		flag_cmaj_filler(flag);
	else if (flag->start[i] == 'S')
		flag_smaj_filler(flag);
	else if (flag->start[i] == '%')
		flag_percent_filler(flag);
}

static void	flag_filler_a(t_flags *flag, int i)
{
	if (flag->start[i] == '#')
		flag_sharp_filler(flag);
	else if (flag->start[i] == '0')
		flag_zero_filler(flag);
	else if (flag->start[i] == '-')
		flag_minus_filler(flag);
	else if (flag->start[i] == ' ')
		flag_space_filler(flag);
	else if (flag->start[i] == '+')
		flag_plus_filler(flag);
	else if (ft_isdigit(flag->start[i]) && flag->start[i] != '0')
		flag_width_filler(flag);
	else if (flag->start[i] == '.')
		flag_precision_filler(flag);
}

/*
**	Dans le cas d'un mauvais/absence de flag de conversion
**	je renvoi end = 1 pour passer a la suite sans prendre en compte
*/

void		list_flag_filler(t_flags *flag)
{
	int		i;

	i = flag->len;
	flag_filler_a(flag, i);
	if (i == flag->len)
		flag_filler_b(flag, i);
	if (i == flag->len)
		flag_filler_c(flag, i);
}
