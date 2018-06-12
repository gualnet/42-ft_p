/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_p_precision.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/19 18:24:38 by galy              #+#    #+#             */
/*   Updated: 2017/02/08 12:10:06 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*first_case(char *str)
{
	free(str);
	if ((str = ft_strdup("")) == NULL)
		exit(-1);
	return (str);
}

char		*flag_precision_p_exec(char *str, t_flags *flag)
{
	char	*tmp;
	char	*zerostr;
	int		zerolen;
	int		i;

	if (flag->precision == 0 && ft_atoi(str) == 0)
		return (first_case(str));
	i = -1;
	zerolen = flag->precision - ft_strlen(str);
	if (zerolen > 0)
	{
		tmp = str;
		if ((zerostr = ft_strnew(zerolen + 1)) == NULL)
			exit(-1);
		while (i++ < zerolen - 1)
			zerostr[i] = '0';
		if ((str = ft_strjoin(zerostr, str)) == NULL)
			exit(-1);
		free(zerostr);
		free(tmp);
		return (str);
	}
	return (str);
}
