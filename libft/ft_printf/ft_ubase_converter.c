/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ubase_converter.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/16 17:58:28 by galy              #+#    #+#             */
/*   Updated: 2017/02/08 15:19:27 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*nbr_pos(uintmax_t n, int i, int base)
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

static char	*short_nbr_pos(unsigned short n, int i, int base)
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

static char	*char_nbr_pos(unsigned char n, int i, int base)
{
	char	tmp[10];
	char	*str;
	int		r;

	ft_bzero(tmp, 10);
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

static char	*str_base_hexa(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 58 && str[i] <= 63)
			str[i] = str[i] + 39;
		i++;
	}
	return (str);
}

char		*ft_ubase_converter(uintmax_t nbr, int base, int nbr_bit)
{
	char			*str;

	str = NULL;
	if (nbr_bit <= 8)
		str = char_nbr_pos(nbr, nbr_bit, base);
	else if (nbr_bit >= 9 && nbr_bit <= 32)
		str = short_nbr_pos(nbr, nbr_bit, base);
	else
	{
		nbr_bit = 64;
		str = nbr_pos(nbr, nbr_bit, base);
	}
	if (str == NULL)
		exit(-1);
	if (base == BASE_HEX)
		str_base_hexa(str);
	return (str);
}
