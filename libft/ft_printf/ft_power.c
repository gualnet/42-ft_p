/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_power.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/10 13:52:00 by galy              #+#    #+#             */
/*   Updated: 2017/01/10 14:13:34 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

unsigned long	ft_power(int nbr, int power)
{
	unsigned long	res;

	if (power == 0)
		return (1);
	res = nbr;
	power = power - 1;
	while (power-- != 0)
		res = res * nbr;
	return (res);
}
