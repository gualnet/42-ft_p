/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wcharlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 19:42:33 by galy              #+#    #+#             */
/*   Updated: 2017/02/08 18:41:12 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_wcharlen(wchar_t wc)
{
	char	*binstr;
	int		binlen;

	if (wc < 172)
		return (1);
	if ((binstr = ft_ubase_converter(wc, BASE_BIN, 32)) == NULL)
		return (-1);
	binlen = ft_strlen(binstr);
	free(binstr);
	if (binlen >= 8 && binlen <= 11)
		return (2);
	else if (binlen >= 12 && binlen <= 17)
		return (3);
	else if (binlen >= 18 && binlen <= 23)
		return (4);
	return (-1);
}
