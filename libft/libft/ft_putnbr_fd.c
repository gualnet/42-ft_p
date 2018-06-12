/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 12:55:37 by galy              #+#    #+#             */
/*   Updated: 2016/11/20 16:31:21 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	void	nbr_min_fd(int fd)
{
	ft_putstr_fd("-2147483648", fd);
}

static	void	in_range_fd(int n, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		n = n * -1;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	if (n < 10)
		ft_putchar_fd(n + 48, fd);
}

void			ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
		nbr_min_fd(fd);
	else if ((n > 2147483647) && (n < -2147483647))
		ft_putstr_fd("number out of range", fd);
	else
		in_range_fd(n, fd);
}
