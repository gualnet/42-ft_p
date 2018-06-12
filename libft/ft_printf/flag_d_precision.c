/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_d_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 19:25:41 by galy              #+#    #+#             */
/*   Updated: 2017/02/08 17:40:32 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

/*
**	La precision donne le nombre minimum de digits a afficher,
**	comble avec des zero
*/

static char	*create_neg_zero_str(char *str, t_flags *flag)
{
	char	*zerostr;
	int		i;
	int		nbrzero;

	nbrzero = 1 + flag->precision - (ft_strlen(str) - 1);
	if (nbrzero <= 0)
	{
		if ((zerostr = ft_strdup("-")) == NULL)
			exit(-1);
		return (zerostr);
	}
	if ((zerostr = ft_strnew(nbrzero + 1)) == NULL)
		exit(-1);
	zerostr[0] = '-';
	i = 1;
	while (i < nbrzero)
	{
		zerostr[i] = '0';
		i++;
	}
	return (zerostr);
}

static char	*create_zero_str(char *str, t_flags *flag)
{
	char	*zerostr;
	int		i;
	int		nbrzero;

	i = 0;
	nbrzero = flag->precision - ft_strlen(str);
	if (nbrzero <= 0)
	{
		if ((zerostr = ft_strdup("")) == NULL)
			exit(-1);
		return (zerostr);
	}
	if ((zerostr = ft_strnew(nbrzero + 1)) == NULL)
		exit(-1);
	while (i < nbrzero)
	{
		zerostr[i] = '0';
		i++;
	}
	return (zerostr);
}

static char	*join_str(char *str, t_flags *flag)
{
	char *newstr;
	char *zerostr;
	char *nbr;

	if (ft_atoll(str) >= 0)
	{
		zerostr = create_zero_str(str, flag);
		nbr = str;
	}
	else
	{
		zerostr = create_neg_zero_str(str, flag);
		nbr = ft_lltoa(-1 * ft_atoll(str));
	}
	if ((newstr = ft_strjoin(zerostr, nbr)) == NULL)
		exit(-1);
	if (nbr != str)
		free(nbr);
	free(zerostr);
	return (newstr);
}

char		*flag_precision_d_exec(char *str, t_flags *flag)
{
	char *tmp;

	if ((ft_atoll(str) == 0) && (flag->precision == 0))
	{
		free(str);
		if ((str = ft_strdup("")) == NULL)
			exit(-1);
	}
	else if (flag->precision != 0)
	{
		tmp = str;
		str = join_str(tmp, flag);
		free(tmp);
	}
	return (str);
}
