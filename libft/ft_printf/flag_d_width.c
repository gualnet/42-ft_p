/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_d_width.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/01 19:30:22 by galy              #+#    #+#             */
/*   Updated: 2017/02/08 18:41:27 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*create_neg_space_str(char *str, t_flags *flag)
{
	int		nbspace;
	int		i;
	char	*strspace;

	nbspace = flag->width - ((int)ft_strlen(str));
	if ((strspace = ft_strnew(nbspace + 1)) == NULL)
		exit(-1);
	if (flag->zero == 1)
		strspace[0] = '-';
	i = 1;
	while (i < nbspace)
	{
		if (i == nbspace - 1 && flag->zero == 0)
			strspace[i] = '-';
		else if (flag->zero == 0)
			strspace[i] = ' ';
		else
			strspace[i] = '0';
		i++;
	}
	return (strspace);
}

static char	*create_space_str(char *str, t_flags *flag)
{
	int		nbspace;
	int		i;
	char	*strspace;

	nbspace = flag->width - (int)ft_strlen(str);
	if ((strspace = ft_strnew(nbspace + 1)) == NULL)
		exit(-1);
	i = 0;
	while (i < nbspace)
	{
		if (flag->zero == 0)
			strspace[i] = ' ';
		else
			strspace[i] = '0';
		i++;
	}
	return (strspace);
}

static char	*join_str(char *str, char *strspace, t_flags *flag)
{
	char *newstr;

	newstr = NULL;
	if (flag->minus == 0)
	{
		if (ft_atoll(str) < 0)
			newstr = ft_strjoin(strspace, str);
		else
			newstr = ft_strjoin(strspace, str);
	}
	else if (flag->minus != 0)
		newstr = ft_strjoin(str, strspace);
	return (newstr);
}

static char	*treat(char *str, t_flags *flag)
{
	long long	posnbr;
	char		*newstr;
	char		*tmpstr;
	char		*strspace;

	posnbr = ft_atoll(str) * -1;
	tmpstr = ft_lltoa(posnbr);
	strspace = create_neg_space_str(tmpstr, flag);
	newstr = join_str(tmpstr, strspace, flag);
	free(tmpstr);
	free(strspace);
	return (newstr);
}

char		*flag_width_d_exec(char *str, t_flags *flag)
{
	char		*newstr;
	char		*strspace;

	strspace = NULL;
	if ((int)ft_strlen(str) >= flag->width)
		return (str);
	if (ft_atoll(str) >= 0)
	{
		strspace = create_space_str(str, flag);
		newstr = join_str(str, strspace, flag);
	}
	else if (ft_atoll(str) < 0 && flag->zero == 0)
	{
		strspace = create_space_str(str, flag);
		newstr = join_str(str, strspace, flag);
	}
	else
		newstr = treat(str, flag);
	free(strspace);
	free(str);
	return (newstr);
}
