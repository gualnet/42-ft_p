/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 12:57:10 by galy              #+#    #+#             */
/*   Updated: 2016/11/14 16:03:32 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	nbr_min(void)
{
	ft_putstr("-2147483648");
}

static	void	in_range(int n)
{
	if (n < 0)
	{
		ft_putchar('-');
		n = n * -1;
	}
	if (n >= 10)
	{
		ft_putnbr(n / 10);
		ft_putnbr(n % 10);
	}
	if (n < 10)
		ft_putchar(n + 48);
}

void			ft_putnbr(int n)
{
	if (n == -2147483648)
		nbr_min();
	else if ((n > 2147483647) && (n < -2147483647))
		ft_putstr("number out of range");
	else
		in_range(n);
}
