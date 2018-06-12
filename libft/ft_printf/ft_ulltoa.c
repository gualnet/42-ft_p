/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ulltoa.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 22:07:42 by galy              #+#    #+#             */
/*   Updated: 2017/02/08 15:21:16 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static	void	nbr_pos(unsigned long long n, int i, char *str)
{
	char tmp[23];

	ft_bzero(tmp, 23);
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

static char		*n_is_null(void)
{
	char *str;

	if ((str = ft_strdup("0")) == NULL)
		exit(-1);
	return (str);
}

char			*ft_ulltoa(unsigned long long n)
{
	char	*str;
	int		i;

	i = 22;
	str = NULL;
	if (n == 0)
		return (n_is_null());
	if (NULL == (str = ft_strnew(23)))
		return (NULL);
	nbr_pos(n, i, str);
	return (str);
}
