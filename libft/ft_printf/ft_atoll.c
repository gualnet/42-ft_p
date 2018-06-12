/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoll.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 16:22:02 by galy              #+#    #+#             */
/*   Updated: 2017/02/08 18:41:20 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	int				check_sign(const char *nptr, int i)
{
	int ret;

	ret = 0;
	if (nptr[i] == '+' && (nptr[i + 1] != '+' && nptr[i + 1] != '-'))
		return (1);
	if (nptr[i] == '-' && (nptr[i + 1] != '-' && nptr[i + 1] != '+'))
		return (-1);
	return (ret);
}

static long long int	do_it(const char *nptr, int i)
{
	long long int	res;

	res = 0;
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (nptr[i] >= '0' && nptr[i] <= '9')
			res = res * 10 + (nptr[i] - 48);
		i++;
	}
	return (res);
}

long long int			ft_atoll(const char *nptr)
{
	int				i;
	long long int	res;
	int				sign;

	sign = 666;
	res = 0;
	i = -1;
	while (!ft_isdigit(nptr[i++]))
		if (!ft_isascii(nptr[i]) || nptr[i] == 27)
			return (0);
	i = 0;
	while (nptr[i] == 32 || !ft_isprint(nptr[i]))
		i++;
	if (sign == 666 && (nptr[i] == '-' || nptr[i] == '+'))
	{
		sign = check_sign(nptr, i);
		i++;
	}
	res = do_it(nptr, i);
	if (sign < 0)
		return (-res);
	else if (sign > 0)
		return (res);
	else
		return (0);
}
