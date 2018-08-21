/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_wstrdup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/07 17:59:00 by galy              #+#    #+#             */
/*   Updated: 2017/02/07 18:03:17 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

wchar_t	*ft_wstrdup(wchar_t *s1)
{
	int		c;
	int		i;
	wchar_t	*str_bis;

	c = ft_wstrlen(s1);
	if (!(str_bis = (wchar_t *)malloc(sizeof(*str_bis) * (c + 1))))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		str_bis[i] = s1[i];
		i++;
	}
	str_bis[i] = '\0';
	return (str_bis);
}
