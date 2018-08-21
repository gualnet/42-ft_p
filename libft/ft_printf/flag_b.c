/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_b.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 10:52:06 by galy              #+#    #+#             */
/*   Updated: 2017/02/08 20:00:40 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		flag_b_filler(t_flags *flag)
{
	flag->conv_type = 'b';
	flag->len += 1;
}

static char	*make_octet(char *str)
{
	int		len;
	char	*tmp;

	len = 1;
	while ((len % 8) != 0)
	{
		len = (int)ft_strlen(str);
		if ((len % 8) == 0)
			break ;
		tmp = str;
		str = ft_strjoin("0", tmp);
		free(tmp);
	}
	return (str);
}

static void	print_by_octet(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (((i % 8) == 0) && (i != 0))
			ft_putchar(' ');
		ft_putchar(str[i]);
		i++;
	}
}

static char	*bin_invert(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '1')
			str[i] = '0';
		else
			str[i] = '1';
		i++;
	}
	tmp = str;
	str = ft_strjoin("11111111", tmp);
	free(tmp);
	return (str);
}

int			flag_b(va_list ap)
{
	char	*str;
	int		nbr;
	int		len;

	nbr = va_arg(ap, int);
	if (nbr < 0)
		nbr += 1;
	str = ft_imaxtoabase(nbr, BASE_BIN, sizeof(int) * 8);
	str = make_octet(str);
	if (nbr < 0)
	{
		str = bin_invert(str);
		ft_putbuffer("1 ");
	}
	print_by_octet(str);
	len = (int)ft_strlen(str);
	free(str);
	return (len);
}
