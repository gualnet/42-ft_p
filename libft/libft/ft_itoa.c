/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/18 12:16:47 by galy              #+#    #+#             */
/*   Updated: 2017/01/24 17:10:09 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static	void	nbr_pos(int n, int i, char *str)
{
	char tmp[12];

	while (i >= 0)
	{
		tmp[i] = '0' + (n % 10);
		n = ((n - (n % 10)) / 10);
		i--;
	}
	i = 0;
	while (tmp[i] == '0')
		i++;
	ft_strncpy(str, (((const char *)tmp) + i), 10 - i);
}

static	void	nbr_neg(int n, int i, char *str)
{
	char tmp[12];

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
		ft_strncpy(str, (((const char *)tmp) + (i - 1)), 10 - i + 1);
	}
	else
		ft_strncpy(str, "0", 2);
}

char			*ft_itoa(int n)
{
	char	*str;
	int		i;

	i = 9;
	str = NULL;
	if (NULL == (str = ft_strnew(11)))
		return (NULL);
	if (n > 0)
		nbr_pos(n, i, str);
	else if (n != -2147483648)
		nbr_neg(-n, i, str);
	else if (n == -2147483648)
	{
		nbr_neg((-n - 1), i, str);
		str[10] = str[10] + 1;
	}
	return (str);
}
