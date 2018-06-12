/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/14 18:08:32 by galy              #+#    #+#             */
/*   Updated: 2016/11/21 21:01:00 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static	void	cpy_counter(char const *s1, char const *s2, char *str_dst)
{
	int len;
	int i;

	i = 0;
	len = 0;
	while (s1[i] != '\0')
	{
		str_dst[len] = s1[i];
		i++;
		len++;
	}
	i = 0;
	while (s2[i] != '\0')
	{
		str_dst[len] = s2[i];
		i++;
		len++;
	}
	str_dst[len] = '\0';
}

char			*ft_strjoin(char const *s1, char const *s2)
{
	char	*str_dst;
	int		len;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	len = ft_strlen(s1) + ft_strlen(s2);
	if (!(str_dst = (char *)malloc(sizeof(*str_dst) * (len + 1))))
		return (NULL);
	cpy_counter(s1, s2, str_dst);
	return (str_dst);
}
