/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/07 11:01:36 by galy              #+#    #+#             */
/*   Updated: 2016/11/07 13:59:01 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		c;
	int		i;
	char	*str_bis;

	c = ft_strlen(s1);
	if (!(str_bis = (char *)malloc(sizeof(*str_bis) * (c + 1))))
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
