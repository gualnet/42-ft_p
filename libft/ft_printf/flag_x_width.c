/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_x_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/02 05:55:51 by galy              #+#    #+#             */
/*   Updated: 2017/02/08 19:03:27 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*create_zero_str(char *str, t_flags *flag)
{
	char	*zerostr;
	int		nbzero;
	int		i;

	if (flag->sharp == 1)
		nbzero = (flag->width - 2) - ft_strlen(str);
	else
		nbzero = flag->width - ft_strlen(str);
	if (nbzero <= 0)
		return (NULL);
	if ((zerostr = ft_strnew(nbzero + 1)) == NULL)
		exit(-1);
	i = 0;
	while (i < nbzero)
	{
		if (flag->zero == 0)
			zerostr[i] = ' ';
		else
			zerostr[i] = '0';
		i++;
	}
	return (zerostr);
}

static char	*multi_case(char *str, char *zerostr, char *newstr, int nbr)
{
	char *tmpstr;

	if (nbr == 1)
	{
		if ((tmpstr = ft_strjoin(zerostr, "0x")) == NULL)
			exit(-1);
		if ((newstr = ft_strjoin(tmpstr, str)) == NULL)
			exit(-1);
	}
	if (nbr == 2)
	{
		if ((tmpstr = ft_strjoin("0x", zerostr)) == NULL)
			exit(-1);
		if ((newstr = ft_strjoin(tmpstr, str)) == NULL)
			exit(-1);
	}
	if (nbr == 3)
	{
		if ((tmpstr = ft_strjoin("0x", str)) == NULL)
			exit(-1);
		if ((newstr = ft_strjoin(tmpstr, zerostr)) == NULL)
			exit(-1);
	}
	free(tmpstr);
	return (newstr);
}

static char	*sharp_case(char *str, char *zerostr, t_flags *flag)
{
	char *newstr;

	newstr = NULL;
	if (flag->minus == 0 && flag->zero == 0)
		newstr = multi_case(str, zerostr, newstr, 1);
	else if (flag->minus == 0 && flag->zero == 1)
		newstr = multi_case(str, zerostr, newstr, 2);
	else if (flag->width > (int)ft_strlen(str))
		newstr = multi_case(str, zerostr, newstr, 3);
	return (newstr);
}

static char	*case_select(char *str, char *zerostr, t_flags *flag)
{
	char *newstr;

	newstr = NULL;
	if (flag->sharp == 0)
	{
		if (flag->minus == 0)
			return (ft_strjoin(zerostr, str));
		else
			return (ft_strjoin(str, zerostr));
	}
	else if (flag->sharp == 1)
	{
		if ((newstr = sharp_case(str, zerostr, flag)) == NULL)
			exit(-1);
	}
	return (newstr);
}

char		*flag_width_x_exec(char *str, t_flags *flag)
{
	char *newstr;
	char *zerostr;

	if ((zerostr = create_zero_str(str, flag)) == NULL)
		return (str);
	if ((newstr = case_select(str, zerostr, flag)) == NULL)
		exit(-1);
	free(zerostr);
	free(str);
	return (newstr);
}
