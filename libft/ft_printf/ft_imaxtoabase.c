/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_imaxtoabase.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 17:58:28 by galy              #+#    #+#             */
/*   Updated: 2017/02/08 14:47:37 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*nbr_pos(intmax_t n, int i, int base)
{
	char	tmp[66];
	char	*str;
	int		r;

	ft_bzero(tmp, 66);
	str = NULL;
	if (n != 0)
	{
		while (i >= 0)
		{
			r = n % base;
			tmp[i] = '0' + r;
			n = n / base;
			i--;
		}
	}
	else
		return (ft_strdup("0"));
	i = 0;
	while (tmp[i] == '0')
		i++;
	if ((str = ft_strdup(tmp + i)) == NULL)
		return (NULL);
	return (str);
}

static char	*short_nbr_pos(short n, int i, int base)
{
	char	tmp[66];
	char	*str;
	int		r;

	ft_bzero(tmp, 66);
	str = NULL;
	if (n != 0)
	{
		while (i >= 0)
		{
			r = n % base;
			tmp[i] = '0' + r;
			n = n / base;
			i--;
		}
	}
	else
		return (ft_strdup("0"));
	i = 0;
	while (tmp[i] == '0')
		i++;
	if ((str = ft_strdup(tmp + i)) == NULL)
		return (NULL);
	return (str);
}

static char	*char_nbr_pos(int n, int i, int base)
{
	char	tmp[66];
	char	*str;
	int		r;

	ft_bzero(tmp, 66);
	while (i - 1 >= 0)
	{
		r = n % base;
		tmp[i] = '0' + r;
		n = n / base;
		i--;
	}
	i = 1;
	while (tmp[i] == '0' && i != 8)
		i++;
	if ((str = ft_strdup(tmp + i)) == NULL)
		return (NULL);
	return (str);
}

char		*ft_imaxtoabase(intmax_t nbr, int base, int nbr_bit)
{
	char	*str;
	int		neg;

	neg = 0;
	if (nbr < 0)
	{
		nbr *= -1;
		neg = 1;
	}
	if (nbr_bit <= 8)
		str = char_nbr_pos(nbr, nbr_bit, base);
	else if (nbr_bit > 8 && nbr_bit < 32)
		str = short_nbr_pos(nbr, nbr_bit, base);
	else
	{
		nbr_bit = 64;
		str = nbr_pos(nbr, nbr_bit, base);
	}
	if (base == BASE_HEX)
		str_imaxbase_hexa(str);
	if (neg == 1)
		str = putnegativesign(str, base);
	return (str);
}
