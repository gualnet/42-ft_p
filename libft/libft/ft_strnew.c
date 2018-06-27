/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 13:32:23 by galy              #+#    #+#             */
/*   Updated: 2016/11/07 18:23:07 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdlib.h>

char	*ft_strnew(size_t size)
{
	char		*str;
	unsigned	i;

	i = 0;
	str = (char*)malloc(sizeof(*str) * size + 1);
	if (str == NULL)
		return (0);
	while (i < (size))
	{
		str[i] = '\0';
		i++;
	}
	str[i] = '\0';
	return (str);
}
