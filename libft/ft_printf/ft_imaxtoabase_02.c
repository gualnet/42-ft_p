/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_imaxtoabase_02.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/02/06 12:29:43 by galy              #+#    #+#             */
/*   Updated: 2017/02/07 19:51:47 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*str_imaxbase_hexa(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 58 && str[i] <= 63)
			str[i] = str[i] + 39;
		i++;
	}
	return (str);
}

char	*putnegativesign(char *str, int base)
{
	char	*tmp;
	int		i;

	if (base != BASE_BIN)
	{
		tmp = str;
		str = ft_strjoin("-", tmp);
		free(tmp);
	}
	i = 0;
	return (str);
}
