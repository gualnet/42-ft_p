/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lltoa.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 22:07:42 by galy              #+#    #+#             */
/*   Updated: 2017/02/08 14:52:01 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	nbr_pos(long long n, int i, char *str)
{
	char tmp[23];

	while (i >= 0)
	{
		tmp[i] = '0' + (n % 10);
		n = ((n - (n % 10)) / 10);
		i--;
	}
	i = 0;
	while (tmp[i] == '0')
		i++;
	ft_strncpy(str, (((const char *)tmp) + i), 23 - i);
}

static	void	nbr_neg(long long n, int i, char *str)
{
	char tmp[23];

	if (n != 0)
	{
		while (i >= 0)
		{
			tmp[i] = '0' + (n % 10);
			n = ((n - (n % 10)) / 10);
			i--;
		}
		i = 0;
		while (tmp[i] == '0')
			i++;
		tmp[i - 1] = '-';
		ft_strncpy(str, (((const char *)tmp) + (i - 1)), 23 - i + 1);
	}
	else
		ft_strncpy(str, "0", 2);
}

/*
**	taille max d'un long long = 20 carateres (en comptant de negatif)
*/

char			*ft_lltoa(long long n)
{
	char	*str;
	int		i;

	i = 22;
	str = NULL;
	if (NULL == (str = ft_strnew(23)))
		return (NULL);
	if (n > 0)
		nbr_pos(n, i, str);
	else if (n != (-9223372036854775807 - 1))
		nbr_neg(-n, i, str);
	else if (n == (-9223372036854775807 - 1))
	{
		nbr_neg((-n - 1), i, str);
		str[19] = str[19] + 1;
	}
	return (str);
}
