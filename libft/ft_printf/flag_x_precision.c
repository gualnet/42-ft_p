/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_x_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 05:55:51 by galy              #+#    #+#             */
/*   Updated: 2017/02/08 13:03:59 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

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
	char *zerostr;
	char *newstr;

	zerostr = create_zero_str(str, flag);
	if ((newstr = ft_strjoin(zerostr, str)) == NULL)
		exit(-1);
	free(str);
	free(zerostr);
	return (newstr);
}

char		*flag_precision_x_exec(char *str, t_flags *flag)
{
	if ((ft_strcmp(str, "0") == 0) && (flag->precision == 0))
	{
		free(str);
		if ((str = ft_strdup("")) == NULL)
			exit(-1);
	}
	else
		str = join_str(str, flag);
	return (str);
}
