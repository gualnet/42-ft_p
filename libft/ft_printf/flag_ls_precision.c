/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flag_ls_precision.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/03 12:34:03 by galy              #+#    #+#             */
/*   Updated: 2017/02/07 21:20:02 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

wchar_t	*flag_precision_ls_exec(wchar_t *wstr, t_flags *flag)
{
	int		i;
	int		cptlen;
	wchar_t	*newstr;

	if ((newstr = ft_wstrdup(wstr)) == NULL)
		exit(-1);
	i = 0;
	cptlen = 0;
	while (wstr[i] != '\0')
	{
		if ((cptlen += ft_wcharlen(wstr[i])) > flag->precision)
			break ;
		i++;
	}
	newstr[i] = L'\0';
	return (newstr);
}
