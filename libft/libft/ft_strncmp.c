/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: galy <galy@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/11/05 13:04:34 by galy              #+#    #+#             */
/*   Updated: 2016/11/20 13:48:09 by galy             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include "libft.h"

static	int		s_len(const char *s1, const char *s2)
{
	int lens1;
	int lens2;

	lens1 = ft_strlen(s1);
	lens2 = ft_strlen(s2);
	if (lens1 <= lens2)
		return (lens2);
	else if (lens1 >= lens2)
		return (lens1);
	return (0);
}

int				ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t i;
	size_t s_long;

	s_long = (size_t)s_len(s1, s2);
	if (s_long < n)
		n = s_long;
	i = 0;
	while (i < n)
	{
		if ((!ft_isascii(s1[i]) || !ft_isascii(s2[i])) && s1[i] != s2[i])
			return (s2[i] - s1[i]);
		if (s1[i] != s2[i])
			return (s1[i] - s2[i]);
		i++;
	}
	return (0);
}
