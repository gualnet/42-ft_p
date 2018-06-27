/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_ls_width.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 12:34:03 by galy              #+#    #+#             */
/*   Updated: 2017/02/07 21:23:10 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static wchar_t	*str_minus_merge(wchar_t *wstr, wchar_t *newstr, t_flags *flag)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (wstr[j] != '\0')
	{
		newstr[i] = wstr[j];
		j++;
		i++;
	}
	j = 0;
	while (j < (flag->width - ft_wstrlen(wstr)))
	{
		newstr[i] = L' ';
		i++;
		j++;
	}
	newstr[i] = '\0';
	return (newstr);
}

static wchar_t	*str_merge(wchar_t *wstr, wchar_t *newstr, int wdtlen,\
	t_flags *flag)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < wdtlen)
	{
		if (flag->zero == 1 && flag->minus == 0)
			newstr[i] = L'0';
		else
			newstr[i] = L' ';
		i++;
	}
	while (wstr[j] != '\0')
	{
		newstr[i] = wstr[j];
		j++;
		i++;
	}
	newstr[i] = '\0';
	return (newstr);
}

wchar_t			*flag_width_ls_exec(wchar_t *wstr, t_flags *flag)
{
	wchar_t *newstr;
	int		wdtlen;

	if (flag->minus == 0)
		wdtlen = flag->width - ft_wstrlen(wstr);
	else
		wdtlen = flag->width - ft_wstrlen(wstr);
	if ((newstr = (wchar_t*)ft_memalloc(sizeof(*newstr) * flag->width + 1))\
	== NULL)
		exit(-1);
	if (flag->minus == 0)
		newstr = str_merge(wstr, newstr, wdtlen, flag);
	else if (flag->minus == 1)
		newstr = str_minus_merge(wstr, newstr, flag);
	free(wstr);
	return (newstr);
}
